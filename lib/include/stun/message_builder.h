#ifndef STUN_LIB_INCLUDE_STUN_MESSAGE_BUILDER_H_
#define STUN_LIB_INCLUDE_STUN_MESSAGE_BUILDER_H_
#include <memory>
#include <vector>

#include "stun/message.h"

namespace stun {

class MessageBuilder final {
 public:
  MessageBuilder& WithType(MessageType type);
  MessageBuilder& WithTransactionId(std::vector<uint8_t> id);
  MessageBuilder& WithRandomTransactionId();

  template <class Attr, class... Args>
  MessageBuilder& WithAttribute(Args&&... args) {
    Message.AddAttribute(
        std::make_shared<Attribute>(std::forward<Args>(args)...));
  }

 protected:
  friend Message;
  MessageBuilder();

  Message message_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_MESSAGE_BUILDER_H_
