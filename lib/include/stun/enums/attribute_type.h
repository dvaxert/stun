#ifndef STUN_LIB_INCLUDE_STUN_ENUMS_ATTRIBUTE_TYPE_H_
#define STUN_LIB_INCLUDE_STUN_ENUMS_ATTRIBUTE_TYPE_H_

#include <cstdint>

namespace stun {

enum class AttributeType : uint16_t {
  MappedAddress = 0x0001,
  ResponseAddress = 0x0002,
  ChangeRequest = 0x0003,
  SourceAddress = 0x0004,
  ChangedAddress = 0x0005,
  Username = 0x0006,
  Password = 0x0007,
  MessageIntegrity = 0x0008,
  ErrorCode = 0x0009,
  UnknownAttributes = 0x000a,
  ReflectedFrom = 0x000b
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ENUMS_ATTRIBUTE_TYPE_H_
