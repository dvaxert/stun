#include <cassert>
#include <memory>
#include <random>
#include <algorithm>

#include "stun/message.h"
#include "stun/message_builder.h"
#include "stun/serializer.h"

namespace stun {

MessageBuilder& MessageBuilder::WithType(MessageType type) {
  message_.SetType(std::move(type));
  return *this;
}

//------------------------------------------------------------------------------

MessageBuilder& MessageBuilder::WithTransactionId(std::vector<uint8_t> id) {
  message_.SetTransactionId(std::move(id));
  return *this;
}

//------------------------------------------------------------------------------

MessageBuilder& MessageBuilder::WithRandomTransactionId() {
  std::vector<uint8_t> id(16, 0);
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<uint32_t> dist(0x00, 0xFF);

  std::for_each(id.begin(), id.end(), [&](uint8_t& val) { val = dist(rng); });

  message_.SetTransactionId(std::move(id));
  return *this;
}

//------------------------------------------------------------------------------

MessageBuilder& MessageBuilder::WithIntegrity() {
  add_integrity_ = true;
  return *this;
}

//------------------------------------------------------------------------------

Message MessageBuilder::Build() {
  assert(CheckMessageIsCorrect());
  if (add_integrity_) {
    Serializer s{};
    s& message_;

    auto integrity = std::make_shared<MessageIntegrity>(s.Data());
    message_.AddAttribute(integrity);
  }

  return std::move(message_);
}

//------------------------------------------------------------------------------

MessageBuilder::MessageBuilder() : message_(), add_integrity_(false) {}

//------------------------------------------------------------------------------

bool MessageBuilder::CheckMessageIsCorrect() const {
  if ((message_.Type() == MessageType::ErrorType) ||
      (message_.TransactionId() == std::vector<uint8_t>(16, 0)))
    return false;

  switch (message_.Type()) {
    case MessageType::BindingRequest: {
      const auto invalid_attributes = {
          AttributeType::MappedAddress,  AttributeType::SourceAddress,
          AttributeType::ChangedAddress, AttributeType::Password,
          AttributeType::ErrorCode,      AttributeType::UnknownAttributes,
          AttributeType::ReflectedFrom};

      for (const auto attr : invalid_attributes) {
        if (message_.HasAttribute(attr)) {
          return false;
        }
      }
      break;
    }
    case MessageType::BindingResponse: {
      const auto invalid_attributes = {
          AttributeType::ResponseAddress, AttributeType::ChangeRequest,
          AttributeType::Username,        AttributeType::Password,
          AttributeType::ErrorCode,       AttributeType::UnknownAttributes};

      const auto necessary_attributes = {AttributeType::MappedAddress,
                                         AttributeType::SourceAddress,
                                         AttributeType::ChangedAddress};

      for (const auto attr : invalid_attributes) {
        if (message_.HasAttribute(attr)) {
          return false;
        }
      }
      for (const auto attr : necessary_attributes) {
        if (!message_.HasAttribute(attr)) {
          return false;
        }
      }
      break;
    }
    case MessageType::SharedSecretRequest: {
      if (message_.AllAtributes().size() != 0) {
        return false;
      }
      break;
    }
    case MessageType::SharedSecretResponse: {
      const auto invalid_attributes = {
          AttributeType::MappedAddress,  AttributeType::ResponseAddress,
          AttributeType::ChangeRequest,  AttributeType::SourceAddress,
          AttributeType::ChangedAddress, AttributeType::MessageIntegrity,
          AttributeType::ErrorCode,      AttributeType::UnknownAttributes,
          AttributeType::ReflectedFrom};

      const auto necessary_attributes = {AttributeType::Username,
                                         AttributeType::Password};

      for (const auto attr : invalid_attributes) {
        if (message_.HasAttribute(attr)) {
          return false;
        }
      }
      for (const auto attr : necessary_attributes) {
        if (!message_.HasAttribute(attr)) {
          return false;
        }
      }
      break;
    }
    case MessageType::BindingErrorResponse:
      [[fallthrough]];
    case MessageType::SharedSecretErrorResponse: {
      const auto invalid_attributes = {
          AttributeType::MappedAddress,  AttributeType::ResponseAddress,
          AttributeType::ChangeRequest,  AttributeType::SourceAddress,
          AttributeType::ChangedAddress, AttributeType::Username,
          AttributeType::Password,       AttributeType::MessageIntegrity,
          AttributeType::ReflectedFrom};

      const auto necessary_attributes = {AttributeType::ErrorCode};

      if (!message_.HasAttribute(AttributeType::ErrorCode)) {
        return false;
      }

      for (const auto attr : invalid_attributes) {
        if (message_.HasAttribute(attr)) {
          return false;
        }
      }
      break;
    }
    default:
      break;
  }
  return true;
}

}  // namespace stun
