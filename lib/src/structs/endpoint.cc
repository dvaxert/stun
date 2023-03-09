#include <sstream>

#include "stun/structs/endpoint.h"

namespace stun {

Endpoint::Endpoint() : host(IpAddress()), service(0) {}

//------------------------------------------------------------------------------

Endpoint::Endpoint(std::string h, std::string s) : host(std::move(h)), service(std::move(s)) {}

//------------------------------------------------------------------------------

Endpoint::Endpoint(std::string h, uint16_t p) : host(std::move(h)), service(std::move(p)) {}

//------------------------------------------------------------------------------

Endpoint::Endpoint(IpAddress a, uint16_t p) : host(std::move(a)), service(std::move(p)) {}

//------------------------------------------------------------------------------

Endpoint::Endpoint(const Endpoint& other) : host(other.host), service(other.service) {}

//------------------------------------------------------------------------------

Endpoint::Endpoint(Endpoint&& other) : host(), service() {
  std::swap(host, other.host);
  std::swap(service, other.service);
}

//------------------------------------------------------------------------------

Endpoint& Endpoint::operator=(const Endpoint& other) {
  if (this != &other) {
    host = other.host;
    service = other.service;
  }
  return *this;
}

//------------------------------------------------------------------------------

Endpoint& Endpoint::operator=(Endpoint&& other) {
  if (this != &other) {
    std::swap(host, other.host);
    std::swap(service, other.service);
  }
  return *this;
}

//------------------------------------------------------------------------------

std::string Endpoint::ToString() const {
  std::ostringstream s{};
  s << *this;
  std::string result = s.str();
  return result;
}

//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& stream, const Endpoint& endpoint) {
  if (endpoint.service.index() == typeid(std::string).hash_code()) {
    stream << std::get<std::string>(endpoint.service) << ':';
  }

  if (endpoint.host.index() == typeid(std::string).hash_code()) {
    stream << std::get<std::string>(endpoint.host);
  } else {
    stream << std::get<IpAddress>(endpoint.host);
  }

  if (endpoint.service.index() == typeid(uint16_t).hash_code()) {
    stream << ':' << std::get<uint16_t>(endpoint.service);
  }

  return stream;
}

}  // namespace stun
