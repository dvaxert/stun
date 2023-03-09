#ifndef STUN_LIB_INCLUDE_STUN_ENUMS_NAT_TYPE_H_
#define STUN_LIB_INCLUDE_STUN_ENUMS_NAT_TYPE_H_

#include <cstdint>

namespace stun {

enum class NATType : uint8_t {
    None,
    FullCone,
    RestrictedCone,
    PortRestrictedCone,
    Symmetric
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ENUMS_NAT_TYPE_H_
