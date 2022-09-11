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
