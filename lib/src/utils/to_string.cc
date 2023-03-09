#include <cassert>
#include <iomanip>
#include <sstream>

#include "stun/utils/to_string.h"

namespace stun {
namespace utils {

std::string ToString(AttributeType type) {
  switch (type) {
    case AttributeType::ChangedAddress:
      return "ChangedAddress";
    case AttributeType::ChangeRequest:
      return "ChangeRequest";
    case AttributeType::ErrorCode:
      return "ErrorCode";
    case AttributeType::MappedAddress:
      return "MappedAddress";
    case AttributeType::MessageIntegrity:
      return "MessageIntegrity";
    case AttributeType::Password:
      return "Password";
    case AttributeType::ReflectedFrom:
      return "ReflectedFrom";
    case AttributeType::ResponseAddress:
      return "ResponseAddress";
    case AttributeType::SourceAddress:
      return "SourceAddress";
    case AttributeType::UnknownAttributes:
      return "UnknownAttributes";
    case AttributeType::Username:
      return "Username";
    default:
      return "Unknown attribute type";
  }
}

//------------------------------------------------------------------------------

std::string ToString(MessageType type) {
  switch (type) {
    case MessageType::BindingErrorResponse:
      return "BindingErrorResponse";
    case MessageType::BindingRequest:
      return "BindingRequest";
    case MessageType::BindingResponse:
      return "BindingResponse";
    case MessageType::SharedSecretErrorResponse:
      return "SharedSecretErrorResponse";
    case MessageType::SharedSecretRequest:
      return "SharedSecretRequest";
    case MessageType::SharedSecretResponse:
      return "SharedSecretResponse";
    default:
      return "Unknown message type";
  }
}

//------------------------------------------------------------------------------

std::string ToHexString(std::vector<uint8_t> data) {
  std::ostringstream buffer{};

  for (auto value : data) {
    buffer << std::hex << static_cast<int>(value);
  }

  return buffer.str();
}

}  // namespace utils
}  // namespace stun
