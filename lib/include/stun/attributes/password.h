#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_PASSWORD_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_PASSWORD_H_

#include <string>

#include "stun/interface/iattribute.h"

namespace stun {

class Password final : public IAttribute {
 public:
  Password() = default;
  explicit Password(std::string password);
  ~Password() override = default;

  AttributeType Type() const override;
  std::string Value() const;

  void Serialize(Serializer& s) const override;
  void Deserialize(Deserializer& d) override;

  virtual std::string ToString() const;

 private:
  uint16_t DataLength() const override;
  size_t AlignSize() const;

  std::string password_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_PASSWORD_H_
