#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_ADDRESS_ATTRIBUTE_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_ADDRESS_ATTRIBUTE_H_

#include <string>

#include "stun/interface/iattribute.h"
#include "stun/utils/to_integral.h"

namespace stun {

class AddressAttribute : IAttribute {
 public:
  AddressAttribute(uint32_t address, uint16_t port);
  AddressAttribute(std::string address, uint16_t port);

  virtual uint8_t Family() const;
  virtual uint16_t Port() const;
  virtual uint32_t Address() const;

  void Serialize(ISerializer& s) const override;

 protected:
  virtual uint16_t DataLength() const override;

  uint16_t port_;
  uint32_t address_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_ADDRESS_ATTRIBUTE_H_
