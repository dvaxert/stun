#include "stun/structs/internet_adapter.h"

namespace stun {

std::ostream& operator<<(std::ostream& stream, const InternetAdapter& adapter) {
  stream << adapter.name;

  if (!adapter.address.empty()) {
    for (const auto& addr : adapter.address) {
      stream << ' ' << addr;
    }
  } else {
    stream << "No address";
  }

  return stream;
}

}  // namespace stun
