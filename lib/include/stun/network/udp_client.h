#ifndef STUN_LIB_INCLUDE_STUN_NETWORK_UDP_CLIENT_H_
#define STUN_LIB_INCLUDE_STUN_NETWORK_UDP_CLIENT_H_

#include "stun/interface/iweb_client.h"
#include "stun/types.h"

namespace stun {

class UdpClient : public IWebClient {
 public:
  UdpClient();
  UdpClient(const std::string_view local_address, const uint16_t local_port);
  ~UdpClient() override;

  ProtocolType Type() const;

  void Connect(const std::string_view host, const std::string_view service) override;
  void Connect(const std::string_view host, const uint16_t port) override;
  void Connect(const IpAddress& address, const uint16_t port) override;
  void Connect(const Endpoint& endpoint) override;

  void Disconnect() override;

  std::vector<Endpoint> ResolveHost(const std::string_view host, const std::string_view service) override;
  std::vector<Endpoint> ResolveHost(const std::string_view host, const uint16_t port) override;
  std::vector<Endpoint> ResolveHost(const IpAddress& address, const uint16_t port) override;
  std::vector<Endpoint> ResolveHost(const Endpoint& endpoint) override;

  bool CanResolveHost(const std::string_view host, const std::string_view service) override;
  bool CanResolveHost(const std::string_view host, const uint16_t port) override;
  bool CanResolveHost(const IpAddress& address, const uint16_t port) override;
  bool CanResolveHost(const Endpoint& endpoint) override;

  void Send(const std::vector<uint8_t>& raw_data) override;
  void Send(const std::string_view str) override;

  std::vector<uint8_t> Reseive(const uint64_t timeout_ms = 2000) override;

  Endpoint RemoteEndpoint() const override;
  Endpoint LocalEndpoint() const override;

  bool Connected() const override;

 private:
  class Pimpl;
  std::unique_ptr<Pimpl> pimpl_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_NETWORK_UDP_CLIENT_H_
