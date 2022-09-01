#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_MAPPED_ADDRESS_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_MAPPED_ADDRESS_H_

#include "stun/attributes/address_attribute.h"

namespace stun {

class MappedAddress final : public AddressAttribute {
 public:
  using AddressAttribute::AddressAttribute;
  ~MappedAddress() override = default;

  inline AttributeType Type() const override {
    return AttributeType::MappedAddress;
  }
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_MAPPED_ADDRESS_H_
