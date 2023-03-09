#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_USERNAME_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_USERNAME_H_

#include <string>

#include "stun/interface/iattribute.h"

namespace stun {

class Username final : public IAttribute {
 public:
  Username() = default;
  explicit Username(std::string name);
  ~Username() override = default;

  AttributeType Type() const override;
  std::string Value() const;

  void Serialize(Serializer& s) const override;
  void Deserialize(Deserializer& d) override;

  virtual std::string ToString() const;

 private:
  size_t AlignSize() const;
  uint16_t DataLength() const override;

  std::string name_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_USERNAME_H_
