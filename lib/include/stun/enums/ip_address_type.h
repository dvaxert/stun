#ifndef STUN_LIB_INCLUDE_STUN_ENUMS_IP_ADDRESS_TYPE_H_
#define STUN_LIB_INCLUDE_STUN_ENUMS_IP_ADDRESS_TYPE_H_

#include <cstdint>
#include <ostream>

namespace stun {

enum class IpAddressType : uint8_t { NoSpecified = 0, v4, v6 };

std::ostream& operator<<(std::ostream& s, IpAddressType t);

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ENUMS_IP_ADDRESS_TYPE_H_
