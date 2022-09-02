#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_UNKNOWN_ATTRIBUTES_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_UNKNOWN_ATTRIBUTES_H_

#include "stun/interface/iattribute.h"

namespace stun {

class UnknownAttributes final : public IAttribute {
 public:
  UnknownAttributes() = default;

  template <class... Args>
  UnknownAttributes(Args&&... args)
      : UnknownAttributes({std::forward<Args>(args)...}) {}

  UnknownAttributes(std::initializer_list<AttributeType> attributes);
  ~UnknownAttributes() override = default;

  AttributeType Type() const override;
  std::vector<AttributeType> Data() const;

  void Add(const AttributeType attr);
  bool IsContain(const AttributeType attr);

  void Serialize(ISerializer& s) const override;

 private:
  bool IsNeedAlign() const;
  uint16_t DataLength() const override;

  std::vector<AttributeType> attributes_;
};

}  // namespace stun

#endif  // WORMHOLE_INCLUDE_WORMHOLE_MESSAGES_ATTRIBUTES_UNKNOWN_ATTRIBUTES_H_
