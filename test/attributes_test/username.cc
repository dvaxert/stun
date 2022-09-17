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

  std::vector<uint8_t> check = {0x00, 0x06, 0x00, 0x0c, 'O', 't',  'h',  'e',
                                'r',  'U',  's',  'e',  'r', 0x00, 0x00, 0x00};

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(UsernameTest, deserialize) {
  auto attribute = Username();

  std::vector<uint8_t> data = {0x00, 0x0c, 'O', 't',  'h',  'e',
                                'r',  'U',  's',  'e',  'r', 0x00, 0x00, 0x00};

  Deserializer d(data);
  attribute.Deserialize(d);

  ASSERT_EQ(attribute.Value(), "OtherUser");
  ASSERT_FALSE(d.HasData());
}
