#include <fmt/format.h>

#include <stdexcept>

#include "stun/attributes/message_integrity.h"
#include "stun/utils/sha1.h"
#include "stun/utils/to_integral.h"
#include "stun/utils/to_string.h"

namespace stun {

MessageIntegrity::MessageIntegrity(const std::vector<uint8_t>& raw_data)
    : hmac1_key_(20, 0) {
  SHA1(reinterpret_cast<char*>(hmac1_key_.data()),
       reinterpret_cast<const char*>(raw_data.data()), raw_data.size());
}

//------------------------------------------------------------------------------

AttributeType MessageIntegrity::Type() const {
  return AttributeType::MessageIntegrity;
}

//------------------------------------------------------------------------------

uint16_t MessageIntegrity::DataLength() const { return 60; }

//------------------------------------------------------------------------------

std::vector<uint8_t> MessageIntegrity::Value() const { return hmac1_key_; }

//------------------------------------------------------------------------------

void MessageIntegrity::Serialize(Serializer& s) const {
  s& utils::to_integral(Type()) & DataLength() & Value() &
      std::vector<uint8_t>(40, 0);
}

//------------------------------------------------------------------------------

void MessageIntegrity::Deserialize(Deserializer& d) {
  auto length = d.Get<uint16_t>();
  if (length != DataLength()) throw std::runtime_error("Incorrect attribute");

  hmac1_key_ = d.GetArray<uint8_t>(20);
  d.Pop(40);
}

//------------------------------------------------------------------------------

std::string MessageIntegrity::ToString() const {
  return fmt::format("[MessageIntegrity: {0}]",
                     stun::utils::ToHexString(hmac1_key_));
}

}  // namespace stun
