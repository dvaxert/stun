#ifndef STUN_TEST_TESTING_UTILS_INCLUDE_TESTING_UTILS_ADDRESS_H_
#define STUN_TEST_TESTING_UTILS_INCLUDE_TESTING_UTILS_ADDRESS_H_

#include <cstdint>
#include <string>

namespace tests {

uint32_t AddressToUint(const std::string_view address);

}  // namespace tests

#endif  // STUN_TEST_TESTING_UTILS_INCLUDE_TESTING_UTILS_ADDRESS_H_
