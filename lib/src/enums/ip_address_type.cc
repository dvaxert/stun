#include "stun/enums/ip_address_type.h"

namespace stun {

std::ostream& operator<<(std::ostream& s, IpAddressType t) {
  switch (t) {
    case IpAddressType::NoSpecified:
      s << "no specified";
      break;
    case IpAddressType::v4:
      s << "v4";
      break;
    case IpAddressType::v6:
      s << "v6";
      break;
  }
  return s;
}

}  // namespace stun
