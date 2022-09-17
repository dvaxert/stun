#include <gtest/gtest.h>
#include <stun/deserializer.h>
#include <stun/serializer.h>
#include <testing_utils/convert.h>
#include <testing_utils/random.h>

#include <boost/endian/arithmetic.hpp>
#include <boost/endian/conversion.hpp>

//------------------------------------------------------------------------------

TEST(DeserializerTest, get_uint8_t) {
  std::vector<uint8_t> testing_data = {0x03, 0xAF, 0x33, 0xEE};
  auto d = stun::Deserializer{testing_data};

  ASSERT_EQ(d.Get<uint8_t>(), uint8_t(0x03));
  ASSERT_EQ(d.Get<uint8_t>(), uint8_t(0xAF));
  ASSERT_EQ(d.Get<uint8_t>(), uint8_t(0x33));
  ASSERT_EQ(d.Get<uint8_t>(), uint8_t(0xEE));
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, get_uint16_t) {
  std::vector<uint8_t> testing_data = {0x03, 0xAF, 0x33, 0xEE,
                                       0x00, 0x15, 0xFF, 0x00};
  auto d = stun::Deserializer{testing_data};

  ASSERT_EQ(d.Get<uint16_t>(), uint16_t(0x03AF));
  ASSERT_EQ(d.Get<uint16_t>(), uint16_t(0x33EE));
  ASSERT_EQ(d.Get<uint16_t>(), uint16_t(0x0015));
  ASSERT_EQ(d.Get<uint16_t>(), uint16_t(0xFF00));
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, get_uint32_t) {
  std::vector<uint8_t> testing_data = {0x03, 0xAF, 0x33, 0xEE, 0x00, 0x15,
                                       0xFF, 0x00, 0x38, 0xA4, 0xE1, 0x3F,
                                       0xAA, 0x51, 0x70, 0x11};
  auto d = stun::Deserializer{testing_data};

  ASSERT_EQ(d.Get<uint32_t>(), uint32_t(0x03AF33EE));
  ASSERT_EQ(d.Get<uint32_t>(), uint32_t(0x0015FF00));
  ASSERT_EQ(d.Get<uint32_t>(), uint32_t(0x38A4E13F));
  ASSERT_EQ(d.Get<uint32_t>(), uint32_t(0xAA517011));
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, get_uint64_t) {
  std::vector<uint8_t> testing_data = {
      0x03, 0xAF, 0x33, 0xEE, 0x00, 0x15, 0xFF, 0x00, 0x38, 0xA4, 0xE1,
      0x3F, 0xAA, 0x51, 0x70, 0x11, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
      0x06, 0x07, 0xF0, 0xE0, 0xD0, 0xC0, 0xB0, 0xA0, 0x90, 0x80};
  auto d = stun::Deserializer{testing_data};

  ASSERT_EQ(d.Get<uint64_t>(), uint64_t(0x03AF33EE0015FF00));
  ASSERT_EQ(d.Get<uint64_t>(), uint64_t(0x38A4E13FAA517011));
  ASSERT_EQ(d.Get<uint64_t>(), uint64_t(0x0001020304050607));
  ASSERT_EQ(d.Get<uint64_t>(), uint64_t(0xF0E0D0C0B0A09080));
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, peek_uint8_t) {
  std::vector<uint8_t> testing_data = {0x03, 0xAF, 0x33, 0xEE};
  auto d = stun::Deserializer{testing_data};

  ASSERT_EQ(d.Peek<uint8_t>(), uint8_t(0x03));
  ASSERT_EQ(d.Get<uint8_t>(), uint8_t(0x03));
  ASSERT_EQ(d.Get<uint8_t>(), uint8_t(0xAF));
  ASSERT_EQ(d.Peek<uint8_t>(), uint8_t(0x33));
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, peek_uint16_t) {
  std::vector<uint8_t> testing_data = {0x03, 0xAF, 0x33, 0xEE,
                                       0x00, 0x15, 0xFF, 0x00};
  auto d = stun::Deserializer{testing_data};

  ASSERT_EQ(d.Peek<uint16_t>(), uint16_t(0x03AF));
  ASSERT_EQ(d.Get<uint16_t>(), uint16_t(0x03AF));
  ASSERT_EQ(d.Get<uint16_t>(), uint16_t(0x33EE));
  ASSERT_EQ(d.Peek<uint16_t>(), uint16_t(0x0015));
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, peek_uint32_t) {
  std::vector<uint8_t> testing_data = {0x03, 0xAF, 0x33, 0xEE, 0x00, 0x15,
                                       0xFF, 0x00, 0x38, 0xA4, 0xE1, 0x3F,
                                       0xAA, 0x51, 0x70, 0x11};
  auto d = stun::Deserializer{testing_data};

  ASSERT_EQ(d.Peek<uint32_t>(), uint32_t(0x03AF33EE));
  ASSERT_EQ(d.Get<uint32_t>(), uint32_t(0x03AF33EE));
  ASSERT_EQ(d.Get<uint32_t>(), uint32_t(0x0015FF00));
  ASSERT_EQ(d.Peek<uint32_t>(), uint32_t(0x38A4E13F));
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, peek_uint64_t) {
  std::vector<uint8_t> testing_data = {
      0x03, 0xAF, 0x33, 0xEE, 0x00, 0x15, 0xFF, 0x00, 0x38, 0xA4, 0xE1,
      0x3F, 0xAA, 0x51, 0x70, 0x11, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
      0x06, 0x07, 0xF0, 0xE0, 0xD0, 0xC0, 0xB0, 0xA0, 0x90, 0x80};
  auto d = stun::Deserializer{testing_data};

  ASSERT_EQ(d.Peek<uint64_t>(), uint64_t(0x03AF33EE0015FF00));
  ASSERT_EQ(d.Get<uint64_t>(), uint64_t(0x03AF33EE0015FF00));
  ASSERT_EQ(d.Get<uint64_t>(), uint64_t(0x38A4E13FAA517011));
  ASSERT_EQ(d.Peek<uint64_t>(), uint64_t(0x0001020304050607));
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, throw_on_data_end) {
  std::vector<uint8_t> testing_data = {0x03, 0xAF, 0x33, 0xEE};
  auto d = stun::Deserializer{testing_data};

  ASSERT_EQ(d.Get<uint8_t>(), uint8_t(0x03));
  ASSERT_EQ(d.Get<uint8_t>(), uint8_t(0xAF));
  ASSERT_EQ(d.Get<uint8_t>(), uint8_t(0x33));
  ASSERT_EQ(d.Get<uint8_t>(), uint8_t(0xEE));
  ASSERT_ANY_THROW(d.Get<uint8_t>());
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, deserialize_string) {
  std::vector<uint8_t> testing_data = {'S', 'o', 'm', 'e',  ' ',  't',
                                       'e', 'x', 't', '\0', '\0', '\0'};
  auto d = stun::Deserializer{testing_data};

  ASSERT_EQ(d.GetString(12), std::string("Some text"));
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, throw_on_deserialize_string) {
  std::vector<uint8_t> testing_data = {'S', 'o', 'm', 'e',  ' ',  't',
                                       'e', 'x', 't', '\0', '\0', '\0'};
  auto d = stun::Deserializer{testing_data};

  ASSERT_ANY_THROW(d.GetString(13));
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, deserialize_array_uint8) {
  std::vector<uint8_t> testing_data = {0x00, 0x01, 0x02, 0x03};
  auto d = stun::Deserializer{testing_data};

  auto arr = d.GetArray<uint8_t>(4);

  ASSERT_EQ(arr.size(), 4);
  ASSERT_EQ(arr[0], 0);
  ASSERT_EQ(arr[1], 1);
  ASSERT_EQ(arr[2], 2);
  ASSERT_EQ(arr[3], 3);
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, deserialize_array_uint16) {
  std::vector<uint8_t> testing_data = {0x01, 0x00, 0x02, 0x01,
                                       0x03, 0x02, 0x04, 0x03};
  auto d = stun::Deserializer{testing_data};

  auto arr = d.GetArray<uint16_t>(4);

  ASSERT_EQ(arr.size(), 4);
  ASSERT_EQ(arr[0], 0x0100);
  ASSERT_EQ(arr[1], 0x0201);
  ASSERT_EQ(arr[2], 0x0302);
  ASSERT_EQ(arr[3], 0x0403);
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, deserialize_array_uint32) {
  std::vector<uint8_t> testing_data = {0x01, 0x00, 0x02, 0x01,
                                       0x03, 0x02, 0x04, 0x03};
  auto d = stun::Deserializer{testing_data};

  auto arr = d.GetArray<uint32_t>(2);

  ASSERT_EQ(arr.size(), 2);
  ASSERT_EQ(arr[0], 0x01000201);
  ASSERT_EQ(arr[1], 0x03020403);
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, deserialize_array_uint64) {
  std::vector<uint8_t> testing_data = {0x01, 0x00, 0x02, 0x01, 0x03, 0x02,
                                       0x04, 0x03, 0x05, 0x0A, 0xFF, 0xE4,
                                       0x11, 0x33, 0x91, 0xD6};
  auto d = stun::Deserializer{testing_data};

  auto arr = d.GetArray<uint64_t>(2);

  ASSERT_EQ(arr.size(), 2);
  ASSERT_EQ(arr[0], 0x0100020103020403);
  ASSERT_EQ(arr[1], 0x050AFFE4113391D6);
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, pop) {
  std::vector<uint8_t> testing_data = {0x01, 0x00, 0x02, 0x01};
  auto d = stun::Deserializer{testing_data};

  d.Pop(1);
  ASSERT_EQ(d.Get<uint8_t>(), 0x00);
  d.Pop(1);
  ASSERT_EQ(d.Get<uint8_t>(), 0x01);
  ASSERT_ANY_THROW(d.Pop(1));
}

//------------------------------------------------------------------------------

TEST(DeserializerTest, has_data) {
  std::vector<uint8_t> testing_data = {0x01};
  auto d = stun::Deserializer{testing_data};

  ASSERT_TRUE(d.HasData());
  d.Pop(1);
  ASSERT_FALSE(d.HasData());
}
