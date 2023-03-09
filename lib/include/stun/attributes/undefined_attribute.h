#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_UNDEFINED_ATTRIBUTE_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_UNDEFINED_ATTRIBUTE_H_

#include "stun/interface/iattribute.h"

namespace stun {

class UndefinedAttribute final : public IAttribute {
 public:
  UndefinedAttribute() = default;
  UndefinedAttribute(uint16_t code, std::vector<uint8_t> data = {});

  AttributeType Type() const override;
  std::vector<uint8_t> Data() const;

  void Serialize(Serializer& s) const;
  void Deserialize(Deserializer& d);

  virtual std::string ToString() const;

 private:
  uint16_t DataLength() const;
  size_t AlignSize() const;

  uint16_t code_;
  std::vector<uint8_t> data_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_UNDEFINED_ATTRIBUTE_H_
