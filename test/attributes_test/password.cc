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

  std::vector<uint8_t> check = {0x00, 0x07, 0x00, 0x10, 'O',  't', 'h',
                                'e',  'r',  'P',  'a',  's',  's', 'w',
                                'o',  'r',  'd',  0x00, 0x00, 0x00};

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(PasswordTest, deserialize) {
  auto attribute = Password();

  std::vector<uint8_t> data = {0x00, 0x10, 'O', 't',  'h',  'e',
                               'r',  'P',  'a', 's',  's',  'w',
                               'o',  'r',  'd', 0x00, 0x00, 0x00};

  Deserializer d(data);
  attribute.Deserialize(d);

  ASSERT_EQ(attribute.Value(), "OtherPassword");
  ASSERT_FALSE(d.HasData());
}
