#ifndef STUN_LIB_INCLUDE_STUN_ENUMS_PROTOCOL_TYPE_H_
#define STUN_LIB_INCLUDE_STUN_ENUMS_PROTOCOL_TYPE_H_

#include <cstdint>
#include <ostream>

namespace stun {

enum class ProtocolType : uint8_t { Udp, Tcp, TcpTls };

std::ostream& operator<<(std::ostream& s, ProtocolType t);

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ENUMS_PROTOCOL_TYPE_H_
