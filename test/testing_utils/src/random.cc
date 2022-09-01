#include <sstream>

#include "testing_utils/random.h"

namespace tests {

std::string GenerateRandomAddress() {
  std::ostringstream result{};
  for (auto i = 0; i < 4; ++i) {
    auto val = GenerateRandomValue<uint32_t>(0, 255);
    result << val;

    if (i < 3) {
      result << '.';
    }
  }
  return result.str();
}

}  // namespace tests
