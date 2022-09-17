#include "stun/attributes/username.h"
#include "stun/utils/to_integral.h"

namespace stun {

Username::Username(std::string name) : name_(std::move(name)) {}

//------------------------------------------------------------------------------

AttributeType Username::Type() const { return AttributeType::Username; }

//------------------------------------------------------------------------------

uint16_t Username::DataLength() const { return name_.size() + AlignSize(); }

//------------------------------------------------------------------------------

std::string Username::Value() const { return name_; }

//------------------------------------------------------------------------------

void Username::Serialize(Serializer& s) const {
  s& utils::to_integral(Type()) & DataLength() & Value() &
      std::vector<uint8_t>(AlignSize(), 0);
}

//------------------------------------------------------------------------------

void Username::Deserialize(Deserializer& d) {
  auto length = d.Get<uint16_t>();
  name_ = d.GetString(length);
}

//------------------------------------------------------------------------------

size_t Username::AlignSize() const {
  auto align = name_.size() % 4;

  if (align != 0) {
    return 4 - align;
  }
  return 0;
}

}  // namespace stun
