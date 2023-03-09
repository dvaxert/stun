#ifndef STUN_LIB_INCLUDE_STUN_UTILS_LOCAL_ADDRESS_H_
#define STUN_LIB_INCLUDE_STUN_UTILS_LOCAL_ADDRESS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "stun/enums/ip_address_type.h"
#include "stun/structs/internet_adapter.h"

namespace stun {
namespace utils {

std::vector<InternetAdapter> GetLocalAdapters(IpAddressType type);

}  // namespace utils
}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_UTILS_LOCAL_ADDRESS_H_
