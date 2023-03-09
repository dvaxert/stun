#ifndef STUN_LIB_INCLUDE_STUN_INTERFACE_IWEB_CLIENT_H_
#define STUN_LIB_INCLUDE_STUN_INTERFACE_IWEB_CLIENT_H_

#include <cstdint>
#include <string_view>
#include <vector>

#include "stun/enums/protocol_type.h"
#include "stun/structs/endpoint.h"
#include "stun/types.h"

namespace stun {

class IWebClient {
 public:
  virtual ~IWebClient() = default;

  virtual ProtocolType Type() const = 0;

  virtual void Connect(const std::string_view host, const std::string_view service) = 0;
  virtual void Connect(const std::string_view host, const uint16_t port) = 0;
  virtual void Connect(const IpAddress& address, const uint16_t port) = 0;
  virtual void Connect(const Endpoint& endpoint) = 0;

  virtual void Disconnect() = 0;

  virtual std::vector<Endpoint> ResolveHost(const std::string_view host, const std::string_view service) = 0;
  virtual std::vector<Endpoint> ResolveHost(const std::string_view host, const uint16_t port) = 0;
  virtual std::vector<Endpoint> ResolveHost(const IpAddress& address, const uint16_t port) = 0;
  virtual std::vector<Endpoint> ResolveHost(const Endpoint& endpoint) = 0;

  virtual bool CanResolveHost(const std::string_view host, const std::string_view service) = 0;
  virtual bool CanResolveHost(const std::string_view host, const uint16_t port) = 0;
  virtual bool CanResolveHost(const IpAddress& address, const uint16_t port) = 0;
  virtual bool CanResolveHost(const Endpoint& endpoint) = 0;

  virtual void Send(const std::vector<uint8_t>& raw_data) = 0;
  virtual void Send(const std::string_view str) = 0;

  virtual std::vector<uint8_t> Reseive(const uint64_t timeout_ms) = 0;

  virtual Endpoint RemoteEndpoint() const = 0;
  virtual Endpoint LocalEndpoint() const = 0;

  virtual bool Connected() const = 0;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_INTERFACE_IWEB_CLIENT_H_
