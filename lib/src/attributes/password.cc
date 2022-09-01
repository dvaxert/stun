#include "stun/attributes/password.h"
#include "stun/utils/to_integral.h"

namespace stun {

Password::Password(std::string password) : password_(std::move(password)) {}

//------------------------------------------------------------------------------

stun::AttributeType Password::Type() const { return AttributeType::Password; }

//------------------------------------------------------------------------------

uint16_t Password::DataLength() const { return password_.size() + AlignSize(); }

//------------------------------------------------------------------------------

std::string Password::Value() const { return password_; }

//------------------------------------------------------------------------------

void Password::Serialize(ISerializer& s) const {
  s& utils::to_integral(Type()) & DataLength() & Value() &
      std::vector<uint8_t>(AlignSize(), 0);
}

//------------------------------------------------------------------------------

size_t Password::AlignSize() const { return 4 - password_.size() % 4; }

}  // namespace stun
