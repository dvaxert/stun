#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_MESSAGE_INTEGRITY_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_MESSAGE_INTEGRITY_H_

#include "stun/interface/iattribute.h"

namespace stun {

class MessageIntegrity final : public IAttribute {
 public:
  MessageIntegrity() = default;
  MessageIntegrity(const std::vector<uint8_t>& raw_data);
  ~MessageIntegrity() override = default;

  AttributeType Type() const override;
  std::vector<uint8_t> Value() const;

  void Serialize(Serializer& s) const override;
  void Deserialize(Deserializer& d) override;

 private:
  uint16_t DataLength() const override;

  std::vector<uint8_t> hmac1_key_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_MESSAGE_INTEGRITY_H_
