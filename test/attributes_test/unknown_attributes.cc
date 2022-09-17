#include <gtest/gtest.h>
#include <stun/attributes/unknown_attributes.h>
#include <stun/serializer.h>

using namespace stun;

//------------------------------------------------------------------------------

TEST(UnknownAttributesTest, create) {
  auto attribute = UnknownAttributes();

  ASSERT_EQ(attribute.Type(), AttributeType::UnknownAttributes);
  ASSERT_EQ(attribute.Data().size(), 0);
}

//------------------------------------------------------------------------------

TEST(UnknownAttributesTest, create_initializer_list) {
  auto attribute = UnknownAttributes{AttributeType::ChangedAddress,
                                     AttributeType::ErrorCode};

  ASSERT_EQ(attribute.Type(), AttributeType::UnknownAttributes);
  ASSERT_EQ(attribute.Data().size(), 2);
  ASSERT_TRUE(attribute.IsContain(AttributeType::ChangedAddress));
  ASSERT_TRUE(attribute.IsContain(AttributeType::ErrorCode));
}

//------------------------------------------------------------------------------

TEST(UnknownAttributesTest, add) {
  auto attribute = UnknownAttributes();

  attribute.Add(AttributeType::MappedAddress);

  ASSERT_EQ(attribute.Type(), AttributeType::UnknownAttributes);
  ASSERT_EQ(attribute.Data().size(), 1);
  ASSERT_TRUE(attribute.IsContain(AttributeType::MappedAddress));
}

//------------------------------------------------------------------------------

TEST(UnknownAttributesTest, add_many_values) {
  auto attribute = UnknownAttributes();

  attribute.Add(AttributeType::MappedAddress);
  attribute.Add(AttributeType::ReflectedFrom);
  attribute.Add(AttributeType::SourceAddress);
  attribute.Add(AttributeType::Password);

  ASSERT_EQ(attribute.Type(), AttributeType::UnknownAttributes);
  ASSERT_EQ(attribute.Data().size(), 4);
  ASSERT_TRUE(attribute.IsContain(AttributeType::MappedAddress));
  ASSERT_TRUE(attribute.IsContain(AttributeType::ReflectedFrom));
  ASSERT_TRUE(attribute.IsContain(AttributeType::SourceAddress));
  ASSERT_TRUE(attribute.IsContain(AttributeType::Password));
}

//------------------------------------------------------------------------------

TEST(UnknownAttributesTest, serialize_no_data) {
  auto attribute = UnknownAttributes();
  Serializer s{};

  s& attribute;

  std::vector<uint8_t> check = {0x00, 0x0A, 0x00, 0x00};

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(UnknownAttributesTest, serialize_one_value) {
  auto attribute = UnknownAttributes{AttributeType::ChangedAddress};
  Serializer s{};

  s& attribute;

  std::vector<uint8_t> check = {0x00, 0x0A, 0x00, 0x04, 0x00, 0x05, 0x00, 0x05};

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(UnknownAttributesTest, serialize_two_value) {
  auto attribute = UnknownAttributes{AttributeType::ChangedAddress,
                                     AttributeType::ChangeRequest};
  Serializer s{};

  s& attribute;

  std::vector<uint8_t> check = {0x00, 0x0A, 0x00, 0x04, 0x00, 0x05, 0x00, 0x03};

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(UnknownAttributesTest, serialize_three_value) {
  auto attribute =
      UnknownAttributes{AttributeType::ChangedAddress,
                        AttributeType::ChangeRequest, AttributeType::ErrorCode};
  Serializer s{};

  s& attribute;

  std::vector<uint8_t> check = {0x00, 0x0A, 0x00, 0x08, 0x00, 0x05,
                                0x00, 0x03, 0x00, 0x09, 0x00, 0x09};

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(UnknownAttributesTest, deserialize_two_value) {
  auto attribute = UnknownAttributes{};

  std::vector<uint8_t> data = {0x00, 0x04, 0x00, 0x05, 0x00, 0x03};

  Deserializer d(data);
  attribute.Deserialize(d);

  std::vector<AttributeType> check = {AttributeType::ChangedAddress,
                                      AttributeType::ChangeRequest};

  ASSERT_EQ(attribute.Data(), check);
  ASSERT_TRUE(attribute.IsContain(AttributeType::ChangedAddress));
  ASSERT_TRUE(attribute.IsContain(AttributeType::ChangeRequest));
  ASSERT_FALSE(d.HasData());
}

//------------------------------------------------------------------------------

TEST(UnknownAttributesTest, deserialize_three_value) {
  auto attribute = UnknownAttributes{};

  std::vector<uint8_t> data = {0x00, 0x08, 0x00, 0x05, 0x00,
                               0x03, 0x00, 0x09, 0x00, 0x09};

  Deserializer d(data);
  attribute.Deserialize(d);

  std::vector<AttributeType> check = {AttributeType::ChangedAddress,
                                      AttributeType::ChangeRequest,
                                      AttributeType::ErrorCode};

  ASSERT_EQ(attribute.Data(), check);
  ASSERT_TRUE(attribute.IsContain(AttributeType::ChangedAddress));
  ASSERT_TRUE(attribute.IsContain(AttributeType::ChangeRequest));
  ASSERT_TRUE(attribute.IsContain(AttributeType::ErrorCode));
  ASSERT_FALSE(d.HasData());
}
