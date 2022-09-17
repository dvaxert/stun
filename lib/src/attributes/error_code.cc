#include <stdexcept>

#include "stun/attributes/error_code.h"
#include "stun/utils/to_integral.h"

constexpr auto bad_request_msg =
    "The request was malformed.  The client should not "
    "retry the request without modification from the previous attempt.";

constexpr auto unauthorized_msg =
    "The Binding Request did not contain a MESSAGE-INTEGRITY attribute.";

constexpr auto unknown_attribute_msg =
    "The server did not understand a mandatory attribute in the request.";

constexpr auto stale_credentials_msg =
    "The Binding Request did contain a MESSAGE-INTEGRITY attribute, but "
    "it used a shared secret that has expired.The client should obtain a "
    "new shared secret and try again.";

constexpr auto integrity_check_failure_msg =
    "The Binding Request contained a MESSAGE-INTEGRITY attribute, but the HMAC "
    "failed verification.This could be a sign of a potential attack, or client "
    "implementation error.";

constexpr auto missing_username_msg =
    "The Binding Request contained a MESSAGE-INTEGRITY attribute, but not a "
    "USERNAME attribute.  Both must be present for integrity checks.";

constexpr auto use_tls_msg =
    "The Shared Secret request has to be sent over TLS, but was not received "
    "over TLS.";

constexpr auto server_error_msg =
    "The server has suffered a temporary error. The client should try again.";

constexpr auto global_failure_msg =
    "The server is refusing to fulfill the request. The client should not "
    "retry.";

//------------------------------------------------------------------------------

namespace stun {

ErrorCode::ErrorCode(PredefinedError error)
    : code_(utils::to_integral(error)), message_() {
  switch (error) {
    case PredefinedError::BadRequest: {
      message_ = bad_request_msg;
      break;
    }
    case PredefinedError::Unauthorized: {
      message_ = unauthorized_msg;
      break;
    }
    case PredefinedError::UnknownAttribute: {
      message_ = unknown_attribute_msg;
      break;
    }
    case PredefinedError::StaleCredentials: {
      message_ = stale_credentials_msg;
      break;
    }
    case PredefinedError::IntegrityCheckFailure: {
      message_ = integrity_check_failure_msg;
      break;
    }
    case PredefinedError::MissingUsername: {
      message_ = missing_username_msg;
      break;
    }
    case PredefinedError::UseTLS: {
      message_ = use_tls_msg;
      break;
    }
    case PredefinedError::ServerError: {
      message_ = server_error_msg;
      break;
    }
    case PredefinedError::GlobalFailure: {
      message_ = global_failure_msg;
      break;
    }
    default: {
      throw std::logic_error("Unknown PredefinedError code");
    }
  }
}

//------------------------------------------------------------------------------

ErrorCode::ErrorCode(uint32_t code, std::string message)
    : code_(std::move(code)), message_(std::move(message)) {}

//------------------------------------------------------------------------------

uint32_t ErrorCode::Code() const { return code_; }

//------------------------------------------------------------------------------

std::string ErrorCode::Message() const { return message_; }

//------------------------------------------------------------------------------

void ErrorCode::Serialize(Serializer& s) const {
  uint8_t error_class = Code() / 100;
  uint8_t error_number = Code() % 100;

  s& utils::to_integral(Type()) & DataLength() & uint16_t(0x0000) &
      error_class& error_number& Message() &
      std::vector<uint8_t>(AlignSize(), 0);
}

//------------------------------------------------------------------------------

void ErrorCode::Deserialize(Deserializer& d) {
  auto length = d.Get<uint16_t>();
  if (length < 4) throw std::runtime_error("Incorrect attribute");

  d.Pop(2);

  code_ = d.Get<uint8_t>() * 100 + d.Get<uint8_t>();
  message_ = d.GetString(length - 4);
}

//------------------------------------------------------------------------------

size_t ErrorCode::AlignSize() const { return 4 - message_.size() % 4; }

//------------------------------------------------------------------------------

AttributeType ErrorCode::Type() const { return AttributeType::ErrorCode; }

//------------------------------------------------------------------------------

uint16_t ErrorCode::DataLength() const {
  return 4 + message_.size() + AlignSize();
}

}  // namespace stun
