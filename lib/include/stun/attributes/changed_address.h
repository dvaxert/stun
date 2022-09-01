#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_CHANGED_ADDRESS_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_CHANGED_ADDRESS_H_

#include "stun/attributes/address_attribute.h"

namespace stun {

class ChangedAddress final : public AddressAttribute {
 public:
  using AddressAttribute::AddressAttribute;
  ~ChangedAddress() override = default;

  inline AttributeType Type() const override {
    return AttributeType::ChangedAddress;
  }
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_CHANGED_ADDRESS_H_
