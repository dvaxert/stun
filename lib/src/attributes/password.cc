#include <fmt/format.h>

#include "stun/attributes/password.h"
#include "stun/utils/to_integral.h"

namespace stun {

Password::Password(std::string password) : password_(std::move(password)) {}

//------------------------------------------------------------------------------

AttributeType Password::Type() const { return AttributeType::Password; }

//------------------------------------------------------------------------------

uint16_t Password::DataLength() const { return password_.size() + AlignSize(); }

//------------------------------------------------------------------------------

std::string Password::Value() const { return password_; }

//------------------------------------------------------------------------------

void Password::Serialize(Serializer& s) const {
  s& utils::to_integral(Type()) & DataLength() & Value() &
      std::vector<uint8_t>(AlignSize(), 0);
}

//------------------------------------------------------------------------------

void Password::Deserialize(Deserializer& d) {
  auto length = d.Get<uint16_t>();
  password_ = d.GetString(length);
}

//------------------------------------------------------------------------------

std::string Password::ToString() const {
  return fmt::format("[Password: {0}]", password_);
}

//------------------------------------------------------------------------------

size_t Password::AlignSize() const {
  auto align = password_.size() % 4;

  if (align != 0) {
    return 4 - align;
  }
  return 0;
}

}  // namespace stun
