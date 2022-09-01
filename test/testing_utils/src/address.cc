#include <array>

#include "testing_utils/address.h"
#include "testing_utils/convert.h"

namespace tests {

uint32_t AddressToUint(const std::string_view address) {
  uint32_t result{};
  std::array<char, 4> buf{};
  size_t pos = 0, counter = 24;

  for (const auto ch : address) {
    if (ch == '.') {
      result |= StringTo<uint8_t>(buf.data()) << counter;
      counter -= 8;
      pos = 0;
      buf = std::array<char, 4>{};
    } else {
      buf[pos] = ch;
      ++pos;
    }
  }
  result |= StringTo<uint8_t>(buf.data()) << counter;

  return result;
}

}  // namespace tests
