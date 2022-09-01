#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_REFLECTED_FROM_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_REFLECTED_FROM_H_

#include "stun/attributes/address_attribute.h"

namespace stun {

class ReflectedFrom final : public AddressAttribute {
 public:
  using AddressAttribute::AddressAttribute;
  ~ReflectedFrom() override = default;

  inline AttributeType Type() const override {
    return AttributeType::ReflectedFrom;
  }
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_REFLECTED_FROM_H_
