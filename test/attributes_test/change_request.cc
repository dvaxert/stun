#include <gtest/gtest.h>
#include <stun/attributes/change_request.h>
#include <stun/serializer.h>
#include <stun/deserializer.h>

using namespace stun;

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, create_no_changes) {
  auto attribute = ChangeRequest(false, false);

  ASSERT_FALSE(attribute.ChangeIp());
  ASSERT_FALSE(attribute.ChangePort());
}

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, create_change_port) {
  auto attribute = ChangeRequest(false, true);

  ASSERT_FALSE(attribute.ChangeIp());
  ASSERT_TRUE(attribute.ChangePort());
}

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, create_change_address) {
  auto attribute = ChangeRequest(true, false);

  ASSERT_TRUE(attribute.ChangeIp());
  ASSERT_FALSE(attribute.ChangePort());
}

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, create_change_all) {
  auto attribute = ChangeRequest(true, true);

  ASSERT_TRUE(attribute.ChangeIp());
  ASSERT_TRUE(attribute.ChangePort());
}

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, create_no_changes_serialize) {
  auto attribute = ChangeRequest(false, false);
  Serializer s{};

  std::vector<uint8_t> check{0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00};

  s& attribute;
  auto serialized = s.Data();
  ASSERT_EQ(serialized.size(), check.size());
  ASSERT_EQ(serialized, check);
}

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, create_change_port_serialize) {
  auto attribute = ChangeRequest(false, true);
  Serializer s{};

  std::vector<uint8_t> check{0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02};

  s& attribute;
  auto serialized = s.Data();
  ASSERT_EQ(serialized.size(), check.size());
  ASSERT_EQ(serialized, check);
}

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, create_change_address_serialize) {
  auto attribute = ChangeRequest(true, false);
  Serializer s{};

  std::vector<uint8_t> check{0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04};

  s& attribute;
  auto serialized = s.Data();
  ASSERT_EQ(serialized.size(), check.size());
  ASSERT_EQ(serialized, check);
}

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, create_change_all_serialize) {
  auto attribute = ChangeRequest(true, true);
  Serializer s{};

  std::vector<uint8_t> check{0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x06};

  s& attribute;
  auto serialized = s.Data();
  ASSERT_EQ(serialized.size(), check.size());
  ASSERT_EQ(serialized, check);
}

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, deserialize_change_all) {
  auto attribute = ChangeRequest();

  std::vector<uint8_t> data{0x00, 0x04, 0x00, 0x00, 0x00, 0x06};

  Deserializer d(data);
  attribute.Deserialize(d);
  ASSERT_TRUE(attribute.ChangeIp());
  ASSERT_TRUE(attribute.ChangePort());
  ASSERT_FALSE(d.HasData());
}

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, deserialize_change_address) {
  auto attribute = ChangeRequest();

  std::vector<uint8_t> data{0x00, 0x04, 0x00, 0x00, 0x00, 0x04};

  Deserializer d(data);
  attribute.Deserialize(d);
  ASSERT_TRUE(attribute.ChangeIp());
  ASSERT_FALSE(attribute.ChangePort());
  ASSERT_FALSE(d.HasData());
}

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, deserialize_change_port) {
  auto attribute = ChangeRequest();

  std::vector<uint8_t> data{0x00, 0x04, 0x00, 0x00, 0x00, 0x02};

  Deserializer d(data);
  attribute.Deserialize(d);
  ASSERT_FALSE(attribute.ChangeIp());
  ASSERT_TRUE(attribute.ChangePort());
  ASSERT_FALSE(d.HasData());
}

//------------------------------------------------------------------------------

TEST(ChangeRequestTest, deserialize_no_change) {
  auto attribute = ChangeRequest();

  std::vector<uint8_t> data{0x00, 0x04, 0x00, 0x00, 0x00, 0x00};

  Deserializer d(data);
  attribute.Deserialize(d);
  ASSERT_FALSE(attribute.ChangeIp());
  ASSERT_FALSE(attribute.ChangePort());
  ASSERT_FALSE(d.HasData());
}
