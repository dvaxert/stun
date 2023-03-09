#include <fmt/format.h>

#include <algorithm>
#include <cassert>
#include <numeric>
#include <stdexcept>

#include "stun/attributes.h"
#include "stun/deserializer.h"
#include "stun/message.h"
#include "stun/message_builder.h"
#include "stun/serializer.h"
#include "stun/utils/to_integral.h"
#include "stun/utils/to_string.h"

namespace stun {

MessageType Message::Type() const { return type_; }

//------------------------------------------------------------------------------

MessageBuilder Message::New() { return MessageBuilder{}; }

//------------------------------------------------------------------------------

std::shared_ptr<IAttribute> AttributeFromRaw(Deserializer& d) {
  auto type = d.Get<uint16_t>();
  std::shared_ptr<IAttribute> result;

  switch (static_cast<AttributeType>(type)) {
    case AttributeType::ChangedAddress:
      result = std::make_shared<ChangedAddress>();
      break;
    case AttributeType::ChangeRequest:
      result = std::make_shared<ChangeRequest>();
      break;
    case AttributeType::ErrorCode:
      result = std::make_shared<ErrorCode>();
      break;
    case AttributeType::MappedAddress:
      result = std::make_shared<MappedAddress>();
      break;
    case AttributeType::MessageIntegrity:
      result = std::make_shared<MessageIntegrity>();
      break;
    case AttributeType::Password:
      result = std::make_shared<Password>();
      break;
    case AttributeType::ReflectedFrom:
      result = std::make_shared<ReflectedFrom>();
      break;
    case AttributeType::ResponseAddress:
      result = std::make_shared<ResponseAddress>();
      break;
    case AttributeType::SourceAddress:
      result = std::make_shared<SourceAddress>();
      break;
    case AttributeType::UnknownAttributes:
      result = std::make_shared<UnknownAttributes>();
      break;
    case AttributeType::Username:
      result = std::make_shared<Username>();
      break;
    default:
      result = std::make_shared<UndefinedAttribute>(type);
      break;
  }
  result->Deserialize(d);

  return result;
}

//------------------------------------------------------------------------------

Message Message::FromRaw(std::vector<uint8_t> raw_data) {
  Deserializer d(std::move(raw_data));
  Message result{};
  result.SetType(static_cast<MessageType>(d.Get<uint16_t>()));
  d.Pop(2);
  result.SetTransactionId(d.GetArray<uint8_t>(16));

  while (d.HasData()) {
    result.AddAttribute(AttributeFromRaw(d));
  }

  return result;
}

//------------------------------------------------------------------------------

Message::~Message() {
  assert(type_ != MessageType::ErrorType);
  assert(transaction_id_.size() == 16);
  assert(transaction_id_ != std::vector<uint8_t>(16, 0));
}

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
  if (attributes_.size() == 0) {
    return false;
  }

  return Attribute(type) != nullptr;
}

//------------------------------------------------------------------------------

std::shared_ptr<IAttribute> Message::Attribute(AttributeType type) const {
  if (attributes_.size() == 0) {
    return nullptr;
  }

  auto it = std::find_if(attributes_.begin(), attributes_.end(),
                         [type](auto val) { return val->Type() == type; });

  if (it != attributes_.end()) {
    return *it;
  }

  return nullptr;
}

//------------------------------------------------------------------------------

std::vector<std::shared_ptr<IAttribute>> Message::AllAtributes() const {
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
  // if (HasAttribute(attribute->Type())) {
  //   throw std::logic_error("The attribute is already exists.");
  // }

  attributes_.emplace_back(attribute);
}

//------------------------------------------------------------------------------

void Message::Serialize(Serializer& s) const {
  s& utils::to_integral(Type()) & Length() & TransactionId();
  for (auto attr : attributes_) {
    s& attr;
  }
}

//------------------------------------------------------------------------------

std::vector<uint8_t> Message::ToBytes() const {
  Serializer s{};
  s.Serialize(*this);
  return s.Data();
}

//------------------------------------------------------------------------------

std::string Message::ToString() const {
  std::string attributes{};
  for (auto attr : attributes_) {
    attributes += "\t\t" + attr->ToString() + '\n';
  }

  return fmt::format(
      "Message:\n"
      "\tType: {0}\n"
      "\tTransaction id: {1}\n"
      "\tAttributes: \n{2}",
      stun::utils::ToString(type_), stun::utils::ToHexString(transaction_id_),
      attributes);
}

//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& s, const Message& msg) {
  s << msg.ToString();
  return s;
}

//------------------------------------------------------------------------------

Message::Message()
    : type_(MessageType::ErrorType), transaction_id_(), attributes_() {}

}  // namespace stun
