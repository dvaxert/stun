#include "stun/attributes/unknown_attributes.h"
#include "stun/utils/to_integral.h"

namespace stun {

void UnknownAttributes::Serialize(ISerializer& s) const {
  s& utils::to_integral(Type()) & DataLength();
  for (auto attribute : attributes_) {
    s& utils::to_integral(attribute);
  }

  if (IsNeedAlign()) {
    s& utils::to_integral(*attributes_.rbegin());
  }
}

//------------------------------------------------------------------------------

bool UnknownAttributes::IsNeedAlign() const {
  return (attributes_.size() % 2) != 0;
}

//------------------------------------------------------------------------------

void UnknownAttributes::Add(const AttributeType attr) {
  attributes_.emplace_back(attr);
}

//------------------------------------------------------------------------------

bool UnknownAttributes::IsContain(const AttributeType attr) {
  return attributes_.end() !=
         std::find(attributes_.begin(), attributes_.end(), attr);
}

//------------------------------------------------------------------------------

UnknownAttributes::UnknownAttributes(
    std::initializer_list<AttributeType> attributes)
    : attributes_(std::move(attributes)) {}

//------------------------------------------------------------------------------

AttributeType UnknownAttributes::Type() const {
  return AttributeType::UnknownAttributes;
}

//------------------------------------------------------------------------------

uint16_t UnknownAttributes::DataLength() const {
  uint16_t length = attributes_.size() * 2;

  if (IsNeedAlign()) length += 2;

  return length;
}

//------------------------------------------------------------------------------

std::vector<AttributeType> UnknownAttributes::Data() const {
  return attributes_;
}

}  // namespace stun
