#ifndef STUN_LIB_INCLUDE_STUN_STRUCTS_INTERNET_ADAPTER_H_
#define STUN_LIB_INCLUDE_STUN_STRUCTS_INTERNET_ADAPTER_H_

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

namespace stun {

struct InternetAdapter {
  std::string name;
  std::vector<std::string> address;
};

std::ostream& operator<<(std::ostream& stream, const InternetAdapter& adapter);

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_STRUCTS_INTERNET_ADAPTER_H_
