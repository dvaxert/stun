#include <algorithm>
#include <numeric>
#include <stdexcept>

#include "stun/message.h"
#include "stun/serializer.h"
#include "stun/utils/to_integral.h"

namespace stun {

MessageType stun::Message::Type() const { return type_; }

//------------------------------------------------------------------------------

uint16_t Message::Length() const {
  return std::accumulate(attributes_.begin(), attributes_.end(), 0,
                         [](uint16_t len, std::shared_ptr<IAttribute> val) {
                           return len + val->Length();
                         });
}

//------------------------------------------------------------------------------

std::vector<uint8_t> Message::TransactionId() const { return transaction_id_; }

//------------------------------------------------------------------------------

bool Message::HasAttribute(AttributeType type) const {
  return Attribute(type) != nullptr;
}

//------------------------------------------------------------------------------

std::shared_ptr<stun::IAttribute> Message::Attribute(AttributeType type) const {
  return *std::find_if(attributes_.begin(), attributes_.end(),
                       [type](auto val) { return val->Type() == type; });
}

//------------------------------------------------------------------------------

std::vector<std::shared_ptr<stun::IAttribute>> Message::AllAtributes() const {
  return attributes_;
}

//------------------------------------------------------------------------------

void Message::SetType(const MessageType type) { type_ = type; }

//------------------------------------------------------------------------------

void Message::SetTransactionId(std::vector<uint8_t> id) {
  transaction_id_ = std::move(id);
}

//------------------------------------------------------------------------------

void Message::AddAttribute(const std::shared_ptr<IAttribute> attribute) {
  if (HasAttribute(attribute->Type())) {
    throw std::logic_error("The attribute is already exists.");
  }

  attributes_.emplace_back(attribute);
}

//------------------------------------------------------------------------------

void Message::Serialize(ISerializer& s) const {
  s& utils::to_integral(Type()) & Length();
  for (auto attr : attributes_) s& attr;
}

}  // namespace stun
