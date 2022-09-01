#ifndef STUN_TEST_TESTING_UTILS_INCLUDE_TESTING_UTILS_RANDOM_H_
#define STUN_TEST_TESTING_UTILS_INCLUDE_TESTING_UTILS_RANDOM_H_

#include <limits>
#include <random>
#include <string>

namespace tests {

template <class Type>
Type GenerateRandomValue(size_t min = Type(), size_t max = ~Type()) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<size_t> dist(min, max);

  return Type(dist(rng));
}

//------------------------------------------------------------------------------

std::string GenerateRandomAddress();

}  // namespace tests

#endif  // STUN_TEST_TESTING_UTILS_INCLUDE_TESTING_UTILS_RANDOM_H_
