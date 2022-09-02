#ifndef STUN_LIB_INCLUDE_STUN_MESSAGE_BUILDER_H_
#define STUN_LIB_INCLUDE_STUN_MESSAGE_BUILDER_H_

#include <memory>
#include <vector>

#include "attributes/message_integrity.h"
#include "stun/message.h"

namespace stun {

class MessageBuilder final {
 public:
  MessageBuilder& WithType(MessageType type);
  MessageBuilder& WithTransactionId(std::vector<uint8_t> id);
  MessageBuilder& WithRandomTransactionId();
  MessageBuilder& WithIntegrity();
  Message Build();

  template <class Attribute, class... Args>
  MessageBuilder& WithAttribute(Args&&... args);

  MessageBuilder(const MessageBuilder&) = delete;
  MessageBuilder(MessageBuilder&&) = delete;
  MessageBuilder& operator=(const MessageBuilder&) = delete;
  MessageBuilder& operator=(MessageBuilder&&) = delete;

 protected:
  friend Message;
  MessageBuilder();

  bool CheckMessageIsCorrect() const;

  Message message_;
  bool add_integrity_;
};

//------------------------------------------------------------------------------

template <class Attribute, class... Args>
MessageBuilder& MessageBuilder::WithAttribute(Args&&... args) {
  static_assert(!std::is_same_v<Attribute, MessageIntegrity>);

  message_.AddAttribute(
      std::make_shared<Attribute>(std::forward<Args>(args)...));
  return *this;
}

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_MESSAGE_BUILDER_H_
