#ifndef STUN_LIB_INCLUDE_STUN_CLIENT_H_
#define STUN_LIB_INCLUDE_STUN_CLIENT_H_

#include <cstdint>
#include <optional>
#include <string>

#include "stun/enums/ip_address_type.h"
#include "stun/enums/nat_type.h"
#include "stun/enums/protocol_type.h"
#include "stun/interface/iweb_client.h"
#include "stun/message.h"
#include "stun/utils/fast_pimpl.h"
#include "stun/utils/local_address.h"

namespace stun {

class StunClient {
 public:
  StunClient();
  ~StunClient();

  /**
   * @brief Returns list of available local ip addresses
   *
   * @param type What type of addresses should be displayed
   * @return The InternetAdapter structure that stores the interface names and
   *         available addresses
   */
  static std::vector<InternetAdapter> GetLocalAdapters(IpAddressType type);

  /**
   * @brief Checking server availability
   *
   * @param address STUN server address
   * @param port STUN server port
   * @param protocol The protocol for which the inspection will be carried out
   * @param local_address Address of the interface from which the connection
   *                      will be made
   * @param local_port Port from which the connection will be made
   * @return true if the server is available
   */
  bool DiscoverServer(const std::string_view host, const std::string_view service, const std::string_view local_address,
                      const uint16_t local_port, const ProtocolType protocol = ProtocolType::Udp);

  /**
   * @brief Test the type of NAT the client is behind
   *
   * @param address STUN server address
   * @param port STUN server port
   * @return Type of NAT
   */
  NATType TestNATType(const std::string_view host, const std::string_view service);

  /**
   * @brief Test #1 according to rfc 3489
   *
   * @param address STUN server address
   * @param port STUN server port
   * @return Type of NAT
   */
  bool Test_1(const std::string_view host, const std::string_view service);

  /**
   * @brief Test the type of NAT the client is behind
   *
   * @param address STUN server address
   * @param port STUN server port
   * @return Type of NAT
   */
  bool Test_2(const std::string_view host, const std::string_view service);

  /**
   * @brief Test the type of NAT the client is behind
   *
   * @param address STUN server address
   * @param port STUN server port
   * @return Type of NAT
   */
  bool Test_3(const std::string_view host, const std::string_view service);

  /**
   * @brief Check the lifetime of the allocated port on NAT
   *
   * @param address STUN server address
   * @param port STUN server port
   * @return millisecond count
   */
  size_t TestLifetime(const std::string_view host, const std::string_view service);

  /**
   * @brief Send STUN message to the specified server
   *
   * @param address STUN server address
   * @param port STUN server port
   * @param msg Message to be sent
   * @param timeout_ms Waiting time for a response from the server
   * @return Server response
   */
  std::optional<Message> Send(const std::string_view host, const std::string_view service, const Message& msg,
                              const size_t timeout_ms = 1000);

 private:
  class Pimpl;
  // utils::FastPimpl<Pimpl, 8, 8> pimpl_;  //! TODO Delete me
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_CLIENT_H_
