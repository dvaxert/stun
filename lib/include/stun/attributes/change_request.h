#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_CHANGE_REQUEST_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_CHANGE_REQUEST_H_

#include "stun/interface/iattribute.h"

namespace stun {

class ChangeRequest final : public IAttribute {
 public:
  ChangeRequest(bool change_ip, bool change_port);
  ~ChangeRequest() override = default;

  AttributeType Type() const override;

  bool ChangeIp() const;
  bool ChangePort() const;

  void Serialize(ISerializer& s) const override;

 private:
  uint16_t DataLength() const override;

  bool change_ip_;
  bool change_port_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_CHANGE_REQUEST_H_
