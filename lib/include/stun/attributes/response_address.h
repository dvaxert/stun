#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_RESPONSE_ADDRESS_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_RESPONSE_ADDRESS_H_

#include "stun/attributes/address_attribute.h"

namespace stun {

class ResponseAddress final : public AddressAttribute {
 public:
  using AddressAttribute::AddressAttribute;
  ~ResponseAddress() override = default;

  inline AttributeType Type() const override {
    return AttributeType::ResponseAddress;
  }
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_RESPONSE_ADDRESS_H_
