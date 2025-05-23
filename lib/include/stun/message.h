#ifndef STUN_LIB_INCLUDE_STUN_INTERFACE_IMESSAGE_H_
#define STUN_LIB_INCLUDE_STUN_INTERFACE_IMESSAGE_H_

#include <cstdint>
#include <memory>
#include <ostream>
#include <vector>

#include "stun/enums/message_type.h"
#include "stun/interface/iattribute.h"

namespace stun {

class MessageBuilder;

class Message {
 public:
  static MessageBuilder New();
  static Message FromRaw(std::vector<uint8_t> raw_data);
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

  void Serialize(Serializer& s) const;

  std::vector<uint8_t> ToBytes() const;
  std::string ToString() const;

 protected:
  friend MessageBuilder;
  Message();

  MessageType type_;
  std::vector<uint8_t> transaction_id_;
  std::vector<std::shared_ptr<IAttribute>> attributes_;
};

std::ostream& operator<<(std::ostream& s, const Message& msg);

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_INTERFACE_IMESSAGE_H_
