#include <fmt/format.h>

#include <algorithm>

#include "stun/attributes/unknown_attributes.h"
#include "stun/utils/to_integral.h"
#include "stun/utils/to_string.h"

namespace stun {

void UnknownAttributes::Serialize(Serializer& s) const {
  s& utils::to_integral(Type()) & DataLength();
  for (auto attribute : attributes_) {
    s& utils::to_integral(attribute);
  }

  if (IsNeedAlign()) {
    s& utils::to_integral(*attributes_.rbegin());
  }
}

//------------------------------------------------------------------------------

void UnknownAttributes::Deserialize(Deserializer& d) {
  auto length = d.Get<uint16_t>();
  attributes_ = d.GetArray<AttributeType>(length / 2);

  if (attributes_.size() > 1) {
    if (*attributes_.rbegin() == *(attributes_.rbegin() + 1)) {
      attributes_.pop_back();
    }
  }
}

//------------------------------------------------------------------------------

std::string UnknownAttributes::ToString() const {
  std::string attributes{};

  for (auto attr : attributes_) {
    attributes += stun::utils::ToString(attr) + ", ";
  }
  attributes.pop_back();
  attributes.pop_back();

  return fmt::format("[UndefinedAttributes: {0}]", attributes);
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
