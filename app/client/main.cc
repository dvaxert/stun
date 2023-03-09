// #include <boost/algorithm/string.hpp>
//
// #include "stun/client.h"
// #include "stun/log_utils.h"
//
// constexpr std::string_view server = "stun.12connect.com";
// constexpr std::string_view service = "3478";
//
// int main() {
//   SET_LOG_LEVEL(Trace);
//   auto client = stun::StunClient();
//   client.TestNATType(server, service);
//
//   auto adapters = client.GetLocalAdapters(stun::IpAddressType::All);
//
//   for (const auto& adapter : adapters) {
//     LOG_INFO(fmt::format("name: {}", adapter.name));
//     for (const auto& addr : adapter.address) {
//       LOG_INFO(fmt::format("address: {}", addr));
//     }
//   }
//
//   // auto res = client.DiscoverServer(server, service, "192.168.3.3", 54321);
//   // if (res) {
//   //   LOG_INFO("ok");
//   // } else {
//   //   LOG_ERROR("NE OK");
//   // }
//
//   return 0;
// }
/*
[I] name: ProtonVPN Tunnel
[I] address: fe80::1123:c782:75a8:a017
[I] address: 169.254.160.23
[I] name: Realtek Gaming GbE Family Controller
[I] address: fe80::c97a:4271:9f18:3d81
[I] address: 192.168.3.3
[I] name: TAP-ProtonVPN Windows Adapter V9
[I] address: fe80::8404:f2a4:f998:69ab
[I] address: 169.254.105.171
[I] name: Bluetooth Device (Personal Area Network)
[I] address: fe80::a1d7:480f:bb10:846f
[I] address: 169.254.132.111
*/

#include <stun/network/udp_client.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

std::vector<uint8_t> str_to_vec(std::string str) {
  std::vector<uint8_t> result{};
  result.reserve(str.size());

  for (const auto ch : str) {
    result.emplace_back(ch);
  }

  return result;
}

std::string vec_to_str(std::vector<uint8_t> vec) {
  std::string result{};
  result.reserve(vec.size());

  for (const auto ch : vec) {
    result.push_back(ch);
  }

  return result;
}

int main() {
  std::shared_ptr<stun::IWebClient> client = std::make_shared<stun::UdpClient>();

  std::this_thread::sleep_for(std::chrono::seconds(1));

  client->Connect("127.0.0.1", "64815");
  std::cout << "local:" << client->LocalEndpoint() << std::endl;
  std::cout << "remote:" << client->RemoteEndpoint() << std::endl;

  client->Send(str_to_vec("qweqweqweqwe"));

  try {
    auto res = client->Reseive(100000);
    std::cout << vec_to_str(res) << std::endl;
  } catch (...) {
    std::cout << "err" << std::endl;
  }

  client->Send(str_to_vec("asdasdasdasd"));

  try {
    auto res = client->Reseive(100000);
    std::cout << vec_to_str(res) << std::endl;
  } catch (...) {
    std::cout << "err" << std::endl;
  }

  return 0;
}
