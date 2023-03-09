#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_CHANGE_REQUEST_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_CHANGE_REQUEST_H_

#include "stun/interface/iattribute.h"

namespace stun {

class ChangeRequest final : public IAttribute {
 public:
  ChangeRequest() = default;
  ChangeRequest(bool change_ip, bool change_port);
  ~ChangeRequest() override = default;

  AttributeType Type() const override;

  bool ChangeIp() const;
  bool ChangePort() const;

  void Serialize(Serializer& s) const override;
  void Deserialize(Deserializer& d) override;

  virtual std::string ToString() const;

 private:
  uint16_t DataLength() const override;

  bool change_ip_;
  bool change_port_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_CHANGE_REQUEST_H_
