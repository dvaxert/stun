#include <stdexcept>

#include "stun/attributes/change_request.h"
#include "stun/utils/to_integral.h"

namespace stun {

ChangeRequest::ChangeRequest(bool change_ip, bool change_port)
    : change_ip_(std::move(change_ip)), change_port_(std::move(change_port)) {}

//------------------------------------------------------------------------------

bool ChangeRequest::ChangeIp() const { return change_ip_; }

//------------------------------------------------------------------------------

bool ChangeRequest::ChangePort() const { return change_port_; }

//------------------------------------------------------------------------------

void ChangeRequest::Serialize(Serializer& s) const {
  uint32_t flags = ChangeIp() << 2 | ChangePort() << 1;

  s& utils::to_integral(Type()) & DataLength() & flags;
}

//------------------------------------------------------------------------------

void ChangeRequest::Deserialize(Deserializer& d) {
  auto length = d.Get<uint16_t>();
  if (length != DataLength()) throw std::runtime_error("Incorrect attribute");

  auto data = d.Get<uint32_t>();

  change_ip_ = data & 4;
  change_port_ = data & 2;
}

//------------------------------------------------------------------------------

AttributeType ChangeRequest::Type() const {
  return AttributeType::ChangeRequest;
}

//------------------------------------------------------------------------------

uint16_t ChangeRequest::DataLength() const { return 4; }

}  // namespace stun
