#include <boost/asio.hpp>

#include "stun/attributes.h"
#include "stun/client.h"
#include "stun/log_utils.h"
#include "stun/message.h"
#include "stun/message_builder.h"
#include "stun/utils/local_address.h"
#include "stun/utils/to_string.h"

namespace stun {

class StunClient::Pimpl {
 public:
  Pimpl();
  ~Pimpl();

  std::vector<std::string> LocalInterfaces();

  bool DiscoverServer(const std::string_view host, const std::string_view service);

  NATType TestNATType(const std::string_view host, const std::string_view service);

 private:
  /**
   * @brief Checking if the address from which the request was made matches the
   * local address
   *
   * @param host Stun server
   * @param service Stun server port
   * @return true The address from which the request came to the server is the
   * same as the local address
   * @return false Address not same
   */
  bool TestAddressMatch(const std::string_view host, const std::string_view service);

  /**
   * @brief Check if the address from which requests come to the server changes
   * between requests
   *
   * @param host Stun server
   * @param service Stun server port
   * @return true The address does not change
   * @return false The address is changing
   */
  bool TestAddressChange(const std::string_view host, const std::string_view service);

  // std::unique_ptr<details::UdpClient> udp_;
};

//------------------------------------------------------------------------------

StunClient::Pimpl::Pimpl() /* : udp_(new details::UdpClient())*/ {}

//------------------------------------------------------------------------------

StunClient::Pimpl::~Pimpl() {}

//------------------------------------------------------------------------------

std::vector<std::string> StunClient::Pimpl::LocalInterfaces() { return {}; }

//------------------------------------------------------------------------------

bool StunClient::Pimpl::DiscoverServer(const std::string_view host, const std::string_view service) {
  TRACE_LOG();
  // return udp_->ResolveHost(host, service);
  return false;
}

//------------------------------------------------------------------------------

NATType StunClient::Pimpl::TestNATType(const std::string_view host, const std::string_view service) {
  TRACE_LOG();
  if (TestAddressMatch(host, service)) {
    return NATType::None;
  }
  if (TestAddressChange(host, service)) {
    return NATType::FullCone;
  }

  return NATType::FullCone;
}

//------------------------------------------------------------------------------

bool StunClient::Pimpl::TestAddressMatch(const std::string_view host, const std::string_view service) {
  /*TRACE_LOG();
  try {
    auto [client_address, client_port] = udp_->GetLocalAddress();
    LOG_DEBUG(fmt::format("Testing for local address {}:{}", client_address,
                          client_port));

    const auto msg = Message::New()
                         .WithType(MessageType::BindingRequest)
                         .WithRandomTransactionId()
                         .WithAttribute<ChangeRequest>(false, false)
                         .WithIntegrity()
                         .Build();

    LOG_DEBUG(fmt::format("Send {}", msg.ToString()));
    udp_->Send(host, service, msg.ToBytes());
    const auto res = udp_->Reseive();

    if (res.empty()) {
      return false;
    }

    const auto res_msg = Message::FromRaw(res);
    LOG_DEBUG(fmt::format("Reseived {}", res_msg.ToString()));

    auto attr = res_msg.Attribute(AttributeType::MappedAddress);

    if (!attr) {
      return false;
    }

    if (attr->Type() == AttributeType::MappedAddress) {
      auto casted = std::dynamic_pointer_cast<MappedAddress>(attr);

      if (client_address != "0.0.0.0") {
        if ((casted->Address() == client_address) &&
            (casted->Port() == client_port)) {
          return true;
        }
      } else {
        const auto local_interfaces = LocalInterfaces();

        for (const auto& address : local_interfaces) {
          if ((casted->Address() == address) &&
              (casted->Port() == client_port)) {
            return true;
          }
        }
      }
    }

  } catch (std::exception& ex) {
    LOG_ERROR(fmt::format("TestAddressMatch error {}", ex.what()));
    return false;
  }
  */
  return false;
}

//------------------------------------------------------------------------------

bool StunClient::Pimpl::TestAddressChange(const std::string_view host, const std::string_view service) {
  /* TRACE_LOG();
  auto [client_address, client_port] = udp_->GetLocalAddress();
  LOG_DEBUG(fmt::format("Testing for local address {}:{}", client_address,
                        client_port));

  const auto msg = Message::New()
                       .WithType(MessageType::BindingRequest)
                       .WithRandomTransactionId()
                       .WithAttribute<ChangeRequest>(false, false)
                       .WithIntegrity()
                       .Build();

  LOG_DEBUG(fmt::format("Send 1 {}", msg.ToString()));
  udp_->Send(host, service, msg.ToBytes());
  const auto res = udp_->Reseive();

  if (res.empty()) {
    return false;
  }

  const auto res_msg = Message::FromRaw(res);
  LOG_DEBUG(fmt::format("Reseived {}", res_msg.ToString()));

  auto attr1 = res_msg.Attribute(AttributeType::MappedAddress);

  if (!attr1) {
    return false;
  }

  std::this_thread::sleep_for(std::chrono::seconds(5));

  LOG_DEBUG(fmt::format("Send 2 {}", msg.ToString()));
  udp_->Send(host, service, msg.ToBytes());
  const auto res2 = udp_->Reseive();

  if (res2.empty()) {
    return false;
  }

  const auto res_msg2 = Message::FromRaw(res2);
  LOG_DEBUG(fmt::format("Reseived {}", res_msg2.ToString()));

  auto attr2 = res_msg2.Attribute(AttributeType::MappedAddress);

  if (!attr2) {
    return false;
  }
  */
  return true;
}

//------------------------------------------------------------------------------

StunClient::StunClient() /*:  pimpl_()*/ { TRACE_LOG(); }

//------------------------------------------------------------------------------

StunClient::~StunClient() { TRACE_LOG(); }

//------------------------------------------------------------------------------

std::vector<InternetAdapter> StunClient::GetLocalAdapters(IpAddressType type) {
  TRACE_LOG_P(type);
  return stun::utils::GetLocalAdapters(type);
}

//------------------------------------------------------------------------------

bool StunClient::DiscoverServer(const std::string_view host, const std::string_view service,
                                const std::string_view local_address, const uint16_t local_port,
                                const ProtocolType protocol) {
  /* TRACE_LOG_P(host, service, local_address, local_port, protocol);
  try {
    auto client = details::UdpClient(
        local_address, local_port);  // TODO нужно сделать под разные клиенты
    return client.ResolveHost(host, service);
  } catch (std::exception& ex) {
    LOG_ERROR(fmt::format("DiscoverServer error {}", ex.what()));
    return false;
  }*/
  return false;
}

//------------------------------------------------------------------------------

NATType StunClient::TestNATType(const std::string_view host, const std::string_view service) {
  TRACE_LOG_P(host, service);
  // return pimpl_->TestNATType(host, service);
  return {};
}

//------------------------------------------------------------------------------
//                     +--------+
//                     |  Test  |
//                     |   I    |
//                     +--------+
//                          |
//                          |
//                          V
//                         /\              /\
//                      N /  \ Y          /  \ Y             +--------+
//       UDP     <-------/Resp\--------->/ IP \------------->|  Test  |
//       Blocked         \ ?  /          \Same/              |   II   |
//                        \  /            \? /               +--------+
//                         \/              \/                    |
//                                          | N                  |
//                                          |                    V
//                                          V                    /\
//                                      +--------+  Sym.      N /  \
//                                      |  Test  |  UDP    <---/Resp\
//                                      |   II   |  Firewall   \ ?  /
//                                      +--------+              \  /
//                                          |                    \/
//                                          V                     |Y
//               /\                         /\                    |
// Symmetric  N /  \       +--------+   N  /  \                   V
//   NAT  <--- / IP \<-----|  Test  |<--- /Resp\               Open
//             \Same/      |   I    |     \ ?  /               Internet
//              \? /       +--------+      \  /
//               \/                         \/
//               |                           |Y
//               |                           |
//               |                           V
//               |                           Full
//               |                           Cone
//               V              /\
//           +--------+        /  \ Y
//           |  Test  |------>/Resp\---->Restricted
//           |   III  |       \ ?  /
//           +--------+        \  /
//                              \/
//                               |N
//                               |       Port
//                               +------>Restricted

//              Figure 2: Flow for type discovery process

bool StunClient::Test_1(const std::string_view host, const std::string_view service) {
  TRACE_LOG_P(host, service);
  // auto client = details::UdpClient();
  return {};
  /*
  TRACE_LOG_P(host, service);

  auto client = details::UdpClient();

  const auto msg = Message::New()
                       .WithType(MessageType::BindingRequest)
                       .WithRandomTransactionId()
                       .WithAttribute<ChangeRequest>(false, false)
                       .WithIntegrity()
                       .Build();

  LOG_DEBUG(fmt::format("Send {}", msg.ToString()));
  client.Send(host, service, msg.ToBytes());
  const auto res = client.Reseive();

  if (res.empty()) {
    throw std::runtime_error("No response from server");
  }

  return Message::FromRaw(res);*/
}

//------------------------------------------------------------------------------

bool StunClient::Test_2(const std::string_view host, const std::string_view service) {
  TRACE_LOG_P(host, service);
  // auto client = details::UdpClient();
  return {};
}

//------------------------------------------------------------------------------

bool StunClient::Test_3(const std::string_view host, const std::string_view service) {
  TRACE_LOG_P(host, service);
  // auto client = details::UdpClient();
  return {};
}

//------------------------------------------------------------------------------

size_t StunClient::TestLifetime(const std::string_view host, const std::string_view service) {
  TRACE_LOG_P(host, service);
  return 0;  // TODO
}

//------------------------------------------------------------------------------

std::optional<Message> StunClient::Send(const std::string_view host, const std::string_view service, const Message& msg,
                                        const size_t timeout_ms) {
  TRACE_LOG_P(host, service, msg, timeout_ms);
  return std::nullopt;  // TODO
}
}  // namespace stun
