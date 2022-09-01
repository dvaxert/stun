#ifndef STUN_LIB_INCLUDE_STUN_INTERFACE_IMESSAGE_H_
#define STUN_LIB_INCLUDE_STUN_INTERFACE_IMESSAGE_H_

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include "stun/enums/message_type.h"
#include "stun/interface/iattribute.h"

namespace stun {

class MessageBuilder;

class Message {
 public:
  static MessageBuilder Builder();
  ~Message();

  MessageType Type() const;
  uint16_t Length() const;
  std::vector<uint8_t> TransactionId() const;

  bool HasAttribute(AttributeType type) const;
  std::shared_ptr<IAttribute> Attribute(AttributeType type) const;
  std::vector<std::shared_ptr<IAttribute>> AllAtributes() const;

  void SetType(const MessageType type);
  void SetTransactionId(std::vector<uint8_t> id);
  void AddAttribute(std::shared_ptr<IAttribute> attribute);

  void Serialize(ISerializer& s) const;

 protected:
  friend MessageBuilder;
  Message();

  MessageType type_;
  std::vector<uint8_t> transaction_id_;
  std::vector<std::shared_ptr<IAttribute>> attributes_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_INTERFACE_IMESSAGE_H_
