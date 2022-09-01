#ifndef STUN_TEST_TESTING_UTILS_INCLUDE_TESTING_UTILS_CONVERT_H_
#define STUN_TEST_TESTING_UTILS_INCLUDE_TESTING_UTILS_CONVERT_H_

#include <boost/endian/conversion.hpp>
#include <string>
#include <vector>

namespace tests {

template <class Type>
Type StringTo(const std::string_view value) {
  Type result = 0;
  for (const auto ch : value) {
    result *= 10;
    result += ch - 48;
  }
  return result;
}

//------------------------------------------------------------------------------

template <class Type>
std::vector<uint8_t> ToBigEndianBytes(Type value) {
  std::vector<uint8_t> result(sizeof(value), 0x00);

  Type be_value = boost::endian::native_to_big(value);

  std::memcpy(result.data(), &be_value, sizeof(be_value));

  return result;
}

}  // namespace tests

#endif  // STUN_TEST_TESTING_UTILS_INCLUDE_TESTING_UTILS_CONVERT_H_
