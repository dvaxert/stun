#include <gtest/gtest.h>
#include <stun/attributes/username.h>
#include <stun/serializer.h>
#include <testing_utils/convert.h>

using namespace stun;

//------------------------------------------------------------------------------

TEST(UsernameTest, create) {
  std::string testing_username = "SomeUser1";
  auto attribute = Username(testing_username);

  ASSERT_EQ(attribute.Type(), AttributeType::Username);
  ASSERT_EQ(attribute.Value(), testing_username);
}

//------------------------------------------------------------------------------

TEST(UsernameTest, serialize) {
  std::string testing_username = "OtherUser";
  auto attribute = Username(testing_username);
  Serializer s{};

  s& attribute;

  auto align = (4 - testing_username.size() % 4);
  auto length_bytes = tests::ToBigEndianBytes(
      static_cast<uint16_t>(testing_username.size() + align));

  std::vector<uint8_t> check = {0x00, 0x06};
  check.insert(check.end(), length_bytes.begin(), length_bytes.end());
  check.insert(check.end(), testing_username.begin(), testing_username.end());
  check.insert(check.end(), align, 0x00);

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}
