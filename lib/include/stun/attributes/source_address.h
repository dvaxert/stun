#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_SOURCE_ADDRESS_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_SOURCE_ADDRESS_H_

#include "stun/attributes/address_attribute.h"

namespace stun {

class SourceAddress final : public AddressAttribute {
 public:
  using AddressAttribute::AddressAttribute;
  ~SourceAddress() override = default;

  inline AttributeType Type() const override {
    return AttributeType::SourceAddress;
  }
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_SOURCE_ADDRESS_H_
