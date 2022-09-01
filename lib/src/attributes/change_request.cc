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

void ChangeRequest::Serialize(ISerializer& s) const {
  constexpr uint16_t length = 0x0004;
  uint32_t flags = ChangeIp() << 2 | ChangePort() << 1;

  s& utils::to_integral(Type()) & DataLength() & flags;
}

//------------------------------------------------------------------------------

AttributeType ChangeRequest::Type() const {
  return AttributeType::ChangeRequest;
}

//------------------------------------------------------------------------------

uint16_t ChangeRequest::DataLength() const { return 4; }

}  // namespace stun
