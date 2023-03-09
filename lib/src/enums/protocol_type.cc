#include "stun/enums/protocol_type.h"

namespace stun {
    
std::ostream& operator<<(std::ostream& s, ProtocolType t) {
  switch (t) {
    case ProtocolType::Udp:
      s << "udp";
      break;
    case ProtocolType::Tcp:
      s << "tcp";
      break;
    case ProtocolType::TcpTls:
      s << "tcp with tls";
      break;
  }
  return s;
}

}