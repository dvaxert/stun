#ifndef STUN_LIB_INCLUDE_STUN_DETAILS_LOG_LEVEL_H_
#define STUN_LIB_INCLUDE_STUN_DETAILS_LOG_LEVEL_H_

#include <cstdint>

namespace stun {
namespace details {

enum class LogLevel : uint8_t { Trace, Debug, Info, Warning, Error, Fatal };

} // namespace details
} // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_DETAILS_LOG_LEVEL_H_
