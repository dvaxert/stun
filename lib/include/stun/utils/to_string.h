#ifndef STUN_LIB_INCLUDE_STUN_UTILS_TO_STRING_H_
#define STUN_LIB_INCLUDE_STUN_UTILS_TO_STRING_H_

#include <cstdint>
#include <string>
#include <vector>

#include "stun/enums/attribute_type.h"
#include "stun/enums/message_type.h"

namespace stun {
namespace utils {

std::string ToString(AttributeType type);
std::string ToString(MessageType type);
std::string ToHexString(std::vector<uint8_t> data);

}  // namespace utils
}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_UTILS_TO_STRING_H_
