#include <gtest/gtest.h>
#include <stun/attributes/password.h>
#include <stun/serializer.h>
#include <testing_utils/convert.h>

using namespace stun;

//------------------------------------------------------------------------------

TEST(PasswordTest, create) {
  std::string testing_pass = "SomePa$$w0rD";
  auto attribute = Password(testing_pass);

  ASSERT_EQ(attribute.Type(), AttributeType::Password);
  ASSERT_EQ(attribute.Value(), testing_pass);
}

//------------------------------------------------------------------------------

TEST(PasswordTest, serialize) {
  std::string testing_pass = "OtherPassword";
  auto attribute = Password(testing_pass);
  Serializer s{};

  s& attribute;

  auto align = (4 - testing_pass.size() % 4);
  auto length_bytes = tests::ToBigEndianBytes(
      static_cast<uint16_t>(testing_pass.size() + align));

  std::vector<uint8_t> check = {0x00, 0x07};
  check.insert(check.end(), length_bytes.begin(), length_bytes.end());
  check.insert(check.end(), testing_pass.begin(), testing_pass.end());
  check.insert(check.end(), align, 0x00);

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}
