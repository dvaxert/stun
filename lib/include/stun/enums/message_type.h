#ifndef STUN_LIB_INCLUDE_STUN_ENUMS_MESSAGE_TYPE_H_
#define STUN_LIB_INCLUDE_STUN_ENUMS_MESSAGE_TYPE_H_

#include <cstdint>

namespace stun {

enum class MessageType : uint16_t {
  ErrorType = 0x0000,
  BindingRequest = 0x0001,
  BindingResponse = 0x0101,
  BindingErrorResponse = 0x0111,
  SharedSecretRequest = 0x0002,
  SharedSecretResponse = 0x0102,
  SharedSecretErrorResponse = 0x0112
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ENUMS_MESSAGE_TYPE_H_
