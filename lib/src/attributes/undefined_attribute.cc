#include <stdexcept>

#include "stun/attributes/undefined_attribute.h"

namespace stun {

UndefinedAttribute::UndefinedAttribute(uint16_t code, std::vector<uint8_t> data)
    : code_(std::move(code)), data_(std::move(data)) {}

//------------------------------------------------------------------------------

AttributeType UndefinedAttribute::Type() const {
  return static_cast<AttributeType>(code_);
}

//------------------------------------------------------------------------------

std::vector<uint8_t> UndefinedAttribute::Data() const { return data_; }

//------------------------------------------------------------------------------

void UndefinedAttribute::Serialize(Serializer& s) const {
  s& Type() & DataLength() & Data() & std::vector<uint8_t>(AlignSize(), 0);
}

//------------------------------------------------------------------------------

void UndefinedAttribute::Deserialize(Deserializer& d) {
  auto length = d.Get<uint16_t>();
  data_ = d.GetArray<uint8_t>(length);
}

//------------------------------------------------------------------------------

uint16_t UndefinedAttribute::DataLength() const { return data_.size(); }

//------------------------------------------------------------------------------

size_t UndefinedAttribute::AlignSize() const {
  auto align = data_.size() % 4;

  if (align != 0) {
    return 4 - align;
  }
  return 0;
}

}  // namespace stun
