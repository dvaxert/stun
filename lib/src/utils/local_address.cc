#include <algorithm>
#include <boost/asio/ip/address.hpp>
#include <functional>

#include "stun/log_utils.h"
#include "stun/structs/internet_adapter.h"
#include "stun/utils/local_address.h"

namespace stun {
namespace utils {

std::vector<InternetAdapter> get_local_adapters();

std::vector<InternetAdapter> GetLocalAdapters(IpAddressType type) {
  std::vector<InternetAdapter> result;

  auto adapters = get_local_adapters();

  std::function<bool(const boost::asio::ip::address &)> check;

  switch (type) {
    case IpAddressType::NoSpecified: {
      check = [](const boost::asio::ip::address &) { return true; };
      break;
    }
    case IpAddressType::v4: {
      check = [](const boost::asio::ip::address &a) { return a.is_v4(); };
      break;
    }
    case IpAddressType::v6: {
      check = [](const boost::asio::ip::address &a) { return a.is_v6(); };
      break;
    }
  }

  for (const auto &adapter : adapters) {
    std::vector<std::string> needed_addresses{};

    for (const auto &str_addr : adapter.address) {
      auto address = boost::asio::ip::address::from_string(str_addr);

      if (check(address) && !address.is_loopback()) {
        needed_addresses.push_back(str_addr);
      }
    }

    if (!needed_addresses.empty()) {
      result.push_back(InternetAdapter{adapter.name, needed_addresses});
    }
  }
  return result;
}

//------------------------------------------------------------------------------

#if defined(_WIN32)
#undef UNICODE
#include <iphlpapi.h>
#include <winsock2.h>
#include <ws2ipdef.h>

#pragma warning(disable : 6387)

std::string AddressToString(const SOCKET_ADDRESS &Address) {
  auto family = Address.lpSockaddr->sa_family;
  std::string result;

  if (family != AF_INET && family != AF_INET6) {
    throw std::runtime_error("Incorrect address family");
  }

  if (family == AF_INET) {
    result = std::string(INET_ADDRSTRLEN, 0);
    sockaddr_in *si = (sockaddr_in *)(Address.lpSockaddr);
    const auto ok =
        inet_ntop(family, &(si->sin_addr), result.data(), result.size());

    if (!ok) {
      throw std::runtime_error("Failed to convert the address to a string");
    }
  } else /*if (family == AF_INET6)*/ {
    result = std::string(INET6_ADDRSTRLEN, 0);
    sockaddr_in6 *si = (sockaddr_in6 *)(Address.lpSockaddr);

    const auto ok =
        inet_ntop(family, &(si->sin6_addr), result.data(), result.size());

    if (!ok) {
      throw std::runtime_error("Failed to convert the address to a string");
    }
  }

  return result;
}

//------------------------------------------------------------------------------

std::vector<InternetAdapter> get_local_adapters() {
  std::vector<InternetAdapter> result;

  // Set the flags to pass to GetAdaptersAddresses
  ULONG flags = GAA_FLAG_INCLUDE_PREFIX | GAA_FLAG_SKIP_ANYCAST |
                GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST |
                GAA_FLAG_SKIP_DNS_SERVER;

  DWORD outBufLen = 1 << 19;  // 512KB
  auto buffer = std::make_unique<char[]>(outBufLen);
  PIP_ADAPTER_ADDRESSES pAddresses =
      reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.get());

  auto dwRetVal =
      GetAdaptersAddresses(AF_UNSPEC, flags, NULL, pAddresses, &outBufLen);

  if (dwRetVal != NO_ERROR) {
    LPTSTR lpMsgBuf = nullptr;
    auto size = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        // Default language
        lpMsgBuf, 0, NULL);

    std::string result(lpMsgBuf, lpMsgBuf + size);
    LocalFree(lpMsgBuf);
    throw std::runtime_error(result);
  }

  auto pCurrAddresses = pAddresses;
  while (pCurrAddresses) {
    const auto description = pCurrAddresses->Description;
    const auto description_size = wcslen(description);
    std::string name(description, description + description_size);
    std::vector<std::string> address{};

    auto pUnicast = pCurrAddresses->FirstUnicastAddress;

    if (!pUnicast) continue;

    while (pUnicast != nullptr) {
      try {
        auto tmp_addr = AddressToString(pUnicast->Address);
        address.emplace_back(tmp_addr);
      } catch (std::exception &ex) {
        LOG_ERROR(fmt::format(
            "Error when converting address of interface {}. Error message: {}",
            name, ex.what()));
      }
      pUnicast = pUnicast->Next;
    }

    result.emplace_back(InternetAdapter{name, address});
    pCurrAddresses = pCurrAddresses->Next;
  }

  return result;
}

//------------------------------------------------------------------------------

#elif defined(__APPLE__) || defined(__linux__)
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <sys/types.h>

boost::asio::ip::address_v6 sinaddr_to_asio(sockaddr_in6 *addr) {
  boost::asio::ip::address_v6::bytes_type buf;
  memcpy(buf.data(), addr->sin6_addr.s6_addr, sizeof(addr->sin6_addr));
  return boost::asio::ip::make_address_v6(buf, addr->sin6_scope_id);
}

//------------------------------------------------------------------------------

std::vector<boost::asio::ip::address> get_local_interfaces() {
  std::vector<boost::asio::ip::address> res;
  ifaddrs *ifs;
  if (getifaddrs(&ifs)) {
    return res;
  }
  for (auto addr = ifs; addr != nullptr; addr = addr->ifa_next) {
    // No address? Skip.
    if (addr->ifa_addr == nullptr) continue;

    // Interface isn't active? Skip.
    if (!(addr->ifa_flags & IFF_UP)) continue;

    if (addr->ifa_addr->sa_family == AF_INET) {
      res.push_back(boost::asio::ip::make_address_v4(ntohl(
          reinterpret_cast<sockaddr_in *>(addr->ifa_addr)->sin_addr.s_addr)));
    } else if (addr->ifa_addr->sa_family == AF_INET6) {
      res.push_back(
          sinaddr_to_asio(reinterpret_cast<sockaddr_in6 *>(addr->ifa_addr)));
    } else
      continue;
  }
  freeifaddrs(ifs);
  return res;
}
#else
#error "..."
#endif

}  // namespace utils
}  // namespace stun
