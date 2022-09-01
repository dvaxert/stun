#ifndef STUN_LIB_INCLUDE_STUN_UTILS_TO_INTEGRAL_H_
#define STUN_LIB_INCLUDE_STUN_UTILS_TO_INTEGRAL_H_

#include <type_traits>

namespace stun {
namespace utils {

template <typename TEnum>
constexpr auto to_integral(TEnum value) {
  return static_cast<typename std::underlying_type_t<TEnum>>(value);
}

}  // namespace utils
}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_UTILS_TO_INTEGRAL_H_
