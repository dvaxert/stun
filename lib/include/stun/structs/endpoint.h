#ifndef STUN_LIB_INCLUDE_STUN_STRUCTS_ENDPOINT_H_
#define STUN_LIB_INCLUDE_STUN_STRUCTS_ENDPOINT_H_

#include <cstdint>
#include <variant>

#include "stun/types.h"

namespace stun {

struct Endpoint {
  Endpoint();
  Endpoint(std::string host, std::string service);
  Endpoint(std::string host, uint16_t port);
  Endpoint(IpAddress address, uint16_t port);
  Endpoint(const Endpoint& other);
  Endpoint(Endpoint&& other);
  Endpoint& operator=(const Endpoint& other);
  Endpoint& operator=(Endpoint&& other);

  std::string ToString() const;

  std::variant<std::string, IpAddress> host;
  std::variant<std::string, uint16_t> service;
};

std::ostream& operator<<(std::ostream& stream, const Endpoint& endpoint);

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_STRUCTS_ENDPOINT_H_
