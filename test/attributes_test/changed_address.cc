#include <gtest/gtest.h>
#include <stun/attributes/changed_address.h>
#include <stun/serializer.h>
#include <testing_utils/address.h>
#include <testing_utils/convert.h>
#include <testing_utils/random.h>

using namespace stun;

//------------------------------------------------------------------------------

TEST(ChangedAddressTest, create_from_string) {
  auto testing_address = tests::GenerateRandomAddress();
  auto testing_port = tests::GenerateRandomValue<uint16_t>();

  auto attribute = ChangedAddress(testing_address, testing_port);

  ASSERT_EQ(attribute.Address(), tests::AddressToUint(testing_address));
  ASSERT_EQ(attribute.Port(), testing_port);
  ASSERT_EQ(attribute.Family(), uint8_t(0x01));
  ASSERT_EQ(attribute.Type(), AttributeType::ChangedAddress);
}

//------------------------------------------------------------------------------

TEST(ChangedAddressTest, create_from_int) {
  auto testing_address = tests::GenerateRandomValue<uint32_t>();
  auto testing_port = tests::GenerateRandomValue<uint16_t>();

  auto attribute = ChangedAddress(testing_address, testing_port);

  ASSERT_EQ(attribute.Address(), testing_address);
  ASSERT_EQ(attribute.Port(), testing_port);
  ASSERT_EQ(attribute.Family(), uint8_t(0x01));
  ASSERT_EQ(attribute.Type(), AttributeType::ChangedAddress);
}

//------------------------------------------------------------------------------

TEST(ChangedAddressTest, serialize_from_string) {
  auto testing_address = tests::GenerateRandomAddress();
  auto testing_port = tests::GenerateRandomValue<uint16_t>();

  auto attribute = ChangedAddress(testing_address, testing_port);
  Serializer s{};

  s& attribute;

  auto address_bytes =
      tests::ToBigEndianBytes(tests::AddressToUint(testing_address));
  auto port_bytes = tests::ToBigEndianBytes(testing_port);

  std::vector<uint8_t> check = {0x00, 0x05, 0x00, 0x08, 0x00, 0x01};
  check.insert(check.end(), port_bytes.begin(), port_bytes.end());
  check.insert(check.end(), address_bytes.begin(), address_bytes.end());

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(ChangedAddressTest, serialize_from_int) {
  auto testing_address = tests::GenerateRandomValue<uint32_t>();
  auto testing_port = tests::GenerateRandomValue<uint16_t>();

  auto attribute = ChangedAddress(testing_address, testing_port);
  Serializer s{};

  s& attribute;

  auto address_bytes = tests::ToBigEndianBytes(testing_address);
  auto port_bytes = tests::ToBigEndianBytes(testing_port);

  std::vector<uint8_t> check = {0x00, 0x05, 0x00, 0x08, 0x00, 0x01};
  check.insert(check.end(), port_bytes.begin(), port_bytes.end());
  check.insert(check.end(), address_bytes.begin(), address_bytes.end());

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}
