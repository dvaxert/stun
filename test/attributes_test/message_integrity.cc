#include <gtest/gtest.h>
#include <stun/attributes/message_integrity.h>
#include <stun/serializer.h>
#include <stun/deserializer.h>
#include <testing_utils/address.h>
#include <testing_utils/convert.h>
#include <testing_utils/random.h>

using namespace stun;

//------------------------------------------------------------------------------

TEST(MessageIntegrityTest, create_no_data) {
  const std::vector<uint8_t> data{};
  auto attribute = MessageIntegrity(data);

  const std::vector<uint8_t> check{0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b,
                                   0x0d, 0x32, 0x55, 0xbf, 0xef, 0x95, 0x60,
                                   0x18, 0x90, 0xaf, 0xd8, 0x07, 0x09};

  ASSERT_EQ(attribute.Type(), AttributeType::MessageIntegrity);
  ASSERT_EQ(attribute.Value().size(), check.size());
  ASSERT_EQ(attribute.Value(), check);
}

//------------------------------------------------------------------------------

TEST(MessageIntegrityTest, create_with_data) {
  const std::vector<uint8_t> data{50, 55, 52, 54, 50, 54};
  auto attribute = MessageIntegrity(data);

  const std::vector<uint8_t> check{0xf9, 0xb0, 0x0b, 0xdc, 0x5e, 0x63, 0x9b,
                                   0x07, 0xd4, 0xd5, 0xe8, 0xec, 0x0a, 0x93,
                                   0x6c, 0x28, 0x09, 0xad, 0xf4, 0xef};

  ASSERT_EQ(attribute.Type(), AttributeType::MessageIntegrity);
  ASSERT_EQ(attribute.Value().size(), check.size());
  ASSERT_EQ(attribute.Value(), check);
}

//------------------------------------------------------------------------------

TEST(MessageIntegrityTest, serialize_no_data) {
  auto attribute = MessageIntegrity(std::vector<uint8_t>());
  Serializer s{};

  std::vector<uint8_t> check{0x00, 0x08, 0x00, 0x3C, 0xda, 0x39, 0xa3, 0xee,
                             0x5e, 0x6b, 0x4b, 0x0d, 0x32, 0x55, 0xbf, 0xef,
                             0x95, 0x60, 0x18, 0x90, 0xaf, 0xd8, 0x07, 0x09};

  check.insert(check.end(), 40, 0);

  s& attribute;

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(MessageIntegrityTest, serialize_with_data) {
  const std::vector<uint8_t> data{'s', 'o', 'm', 'e', '_', 'd', 'a', 't', 'a'};
  auto attribute = MessageIntegrity(data);
  Serializer s{};

  std::vector<uint8_t> check{0x00, 0x08, 0x00, 0x3C, 0x2e, 0xb4, 0x84, 0xcf,
                             0x4b, 0x77, 0xe4, 0x1f, 0x20, 0xc4, 0x80, 0xf3,
                             0xf8, 0x3e, 0xe9, 0x46, 0x89, 0xb7, 0x8c, 0xab};

  check.insert(check.end(), 40, 0);

  s& attribute;

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(MessageIntegrityTest, deserialize) {
  auto attribute = MessageIntegrity();

  std::vector<uint8_t> data = {0x00, 0x3C, 0x2e, 0xb4, 0x84, 0xcf, 0x4b, 0x77,
                               0xe4, 0x1f, 0x20, 0xc4, 0x80, 0xf3, 0xf8, 0x3e,
                               0xe9, 0x46, 0x89, 0xb7, 0x8c, 0xab};
  data.insert(data.end(), 40, 0);

  Deserializer d(data);
  attribute.Deserialize(d);

  std::vector<uint8_t> check{0x2e, 0xb4, 0x84, 0xcf, 0x4b, 0x77, 0xe4,
                             0x1f, 0x20, 0xc4, 0x80, 0xf3, 0xf8, 0x3e,
                             0xe9, 0x46, 0x89, 0xb7, 0x8c, 0xab};

  ASSERT_EQ(attribute.Value(), check);
  ASSERT_FALSE(d.HasData());
}
