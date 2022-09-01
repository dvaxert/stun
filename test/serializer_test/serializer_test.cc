#if _MSC_VER
#pragma warning(disable : 4319)
#pragma warning(disable : 4244)
#endif

#include <gtest/gtest.h>
#include <stun/serializer.h>
#include <testing_utils/convert.h>
#include <testing_utils/random.h>

#include <boost/endian/arithmetic.hpp>
#include <boost/endian/conversion.hpp>

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_uint8_t) {
  auto serializer = stun::Serializer{};
  serializer& uint8_t(0x30);

  std::vector<uint8_t> check{0x30};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_many_uint8_t) {
  auto serializer = stun::Serializer{};

  serializer& uint8_t(0x44) & uint8_t(0x33) & uint8_t(0x22) & uint8_t(0x11) &
      uint8_t(0x00);

  std::vector<uint8_t> check{0x44, 0x33, 0x22, 0x11, 0x00};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_uint16_t) {
  auto serializer = stun::Serializer{};

  serializer& uint16_t(0x3018);

  std::vector<uint8_t> check{0x30, 0x18};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_many_uint16_t) {
  auto serializer = stun::Serializer{};

  serializer& uint16_t(0x3018) & uint16_t(0x1337) & uint16_t(0x1234) &
      uint16_t(0x0101);

  std::vector<uint8_t> check{0x30, 0x18, 0x13, 0x37, 0x12, 0x34, 0x01, 0x01};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_uint32_t) {
  auto serializer = stun::Serializer{};

  serializer& uint32_t(0x44332211);

  std::vector<uint8_t> check{0x44, 0x33, 0x22, 0x11};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_many_uint32_t) {
  auto serializer = stun::Serializer{};

  serializer& uint32_t(0x44332211) & uint32_t(0x55667788);

  std::vector<uint8_t> check{0x44, 0x33, 0x22, 0x11, 0x55, 0x66, 0x77, 0x88};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_uint64_t) {
  auto serializer = stun::Serializer{};

  serializer& uint64_t(0x8877665544332211);

  std::vector<uint8_t> check{0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_many_uint64_t) {
  auto serializer = stun::Serializer{};

  serializer& uint64_t(0x8877665544332211) & uint64_t(0x1532970372035836);

  std::vector<uint8_t> check{0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11,
                             0x15, 0x32, 0x97, 0x03, 0x72, 0x03, 0x58, 0x36};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_mix_uint8_t_uint16_t) {
  auto serializer = stun::Serializer{};

  serializer& uint8_t(0x03) & uint16_t(0x15F9) & uint8_t(0x76) &
      uint16_t(0xA07E) & uint16_t(0xF310);

  std::vector<uint8_t> check{0x03, 0x15, 0xF9, 0x76, 0xA0, 0x7E, 0xF3, 0x10};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_mix_uint8_t_uint32_t) {
  auto serializer = stun::Serializer{};

  serializer& uint32_t(0xB4A367F2) & uint8_t(0x03) & uint8_t(0x76) &
      uint32_t(0x15F9A07E);

  std::vector<uint8_t> check{0xB4, 0xA3, 0x67, 0xF2, 0x03,
                             0x76, 0x15, 0xF9, 0xA0, 0x7E};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_mix_uint8_t_uint64_t) {
  auto serializer = stun::Serializer{};

  serializer& uint8_t(0x16) & uint64_t(0xB4A367F20D610A81) & uint8_t(0xFF);

  std::vector<uint8_t> check{0x16, 0xB4, 0xA3, 0x67, 0xF2,
                             0x0D, 0x61, 0x0A, 0x81, 0xFF};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_mix_uint16_t_uint32_t) {
  auto serializer = stun::Serializer{};

  serializer& uint16_t(0xF2C0) & uint16_t(0xA042) & uint32_t(0x63A9FE70) &
      uint32_t(0x35172EEA);

  std::vector<uint8_t> check{0xF2, 0xC0, 0xA0, 0x42, 0x63, 0xA9,
                             0xFE, 0x70, 0x35, 0x17, 0x2E, 0xEA};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_mix_uint16_t_uint64_t) {
  auto serializer = stun::Serializer{};

  serializer& uint16_t(0x2FA0) & uint64_t(0x6313E72EA5A9FE70) &
      uint16_t(0x42C0);

  std::vector<uint8_t> check{0x2F, 0xA0, 0x63, 0x13, 0xE7, 0x2E,
                             0xA5, 0xA9, 0xFE, 0x70, 0x42, 0xC0};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_mix_uint32_t_uint64_t) {
  auto serializer = stun::Serializer{};

  serializer& uint64_t(0x49A73FE860C6D396) & uint32_t(0x92AE8590) &
      uint32_t(0xFEDCBA98);

  std::vector<uint8_t> check{0x49, 0xA7, 0x3F, 0xE8, 0x60, 0xC6, 0xD3, 0x96,
                             0x92, 0xAE, 0x85, 0x90, 0xFE, 0xDC, 0xBA, 0x98};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_mix_all) {
  auto serializer = stun::Serializer{};

  serializer& uint16_t(0xF7E5) & uint64_t(0x1133557799AACCEE) & uint8_t(0xFF) &
      uint32_t(0x22446688);

  std::vector<uint8_t> check{0xF7, 0xE5, 0x11, 0x33, 0x55, 0x77, 0x99, 0xAA,
                             0xCC, 0xEE, 0xFF, 0x22, 0x44, 0x66, 0x88};

  ASSERT_EQ(check, serializer.Data());
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_align_1_to_8) {
  auto serializer = stun::Serializer{};

  serializer& uint8_t(0xFF);
  serializer.AlignData(8);

  std::vector<uint8_t> check(8, 0x00);
  check[0] = 0xFF;

  auto serialized = serializer.Data();
  ASSERT_EQ(serialized.size(), check.size());
  ASSERT_EQ(serialized, check);
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_align_4_to_32) {
  auto serializer = stun::Serializer{};

  serializer& uint32_t(0xFFFFFFFF);
  serializer.AlignData(32);

  std::vector<uint8_t> check(4, 0xFF);
  check.insert(check.end(), 28, 0x00);

  auto serialized = serializer.Data();
  ASSERT_EQ(serialized.size(), check.size());
  ASSERT_EQ(serialized, check);
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_align_4_to_4) {
  auto serializer = stun::Serializer{};

  serializer& uint32_t(0xFFFFFFFF);
  serializer.AlignData(4);

  std::vector<uint8_t> check(4, 0xFF);

  auto serialized = serializer.Data();
  ASSERT_EQ(serialized.size(), check.size());
  ASSERT_EQ(serialized, check);
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_align_5_to_3) {
  auto serializer = stun::Serializer{};

  serializer& uint32_t(0xFFFFFFFF) & uint8_t(0xFF);
  serializer.AlignData(3);

  std::vector<uint8_t> check(5, 0xFF);
  check.emplace_back(0x00);

  auto serialized = serializer.Data();
  ASSERT_EQ(serialized.size(), check.size());
  ASSERT_EQ(serialized, check);
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_100_random_values_uint8_t) {
  for (auto i = 0; i < 100; ++i) {
    auto serializer = stun::Serializer{};
    auto value = tests::GenerateRandomValue<uint8_t>();

    serializer& value;
    auto check = tests::ToBigEndianBytes(value);

    ASSERT_EQ(check, serializer.Data());
  }
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_100_random_values_uint16_t) {
  for (auto i = 0; i < 100; ++i) {
    auto serializer = stun::Serializer{};
    auto value = tests::GenerateRandomValue<uint16_t>();

    serializer& value;
    auto check = tests::ToBigEndianBytes(value);

    ASSERT_EQ(check, serializer.Data());
  }
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_100_random_values_uint32_t) {
  for (auto i = 0; i < 100; ++i) {
    auto serializer = stun::Serializer{};
    auto value = tests::GenerateRandomValue<uint32_t>();

    serializer& value;
    auto check = tests::ToBigEndianBytes(value);

    ASSERT_EQ(check, serializer.Data());
  }
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_100_random_values_uint64_t) {
  for (auto i = 0; i < 100; ++i) {
    auto serializer = stun::Serializer{};
    auto value = tests::GenerateRandomValue<uint64_t>();

    serializer& value;
    auto check = tests::ToBigEndianBytes(value);

    ASSERT_EQ(check, serializer.Data());
  }
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_100_random_align_uint8_t) {
  for (auto i = 0; i < 100; ++i) {
    auto serializer = stun::Serializer{};
    auto value = tests::GenerateRandomValue<uint8_t>();
    auto align = tests::GenerateRandomValue<size_t>(1, 255);

    serializer& value;
    serializer.AlignData(align);

    auto result = serializer.Data();
    ASSERT_EQ(result.size() % align, 0);
    ASSERT_GE(result.size(), align);

    if (result.size() > align) {
      ASSERT_GE(result.size() / align, 2);
    }
  }
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_100_random_align_uint16_t) {
  for (auto i = 0; i < 100; ++i) {
    auto serializer = stun::Serializer{};
    auto value = tests::GenerateRandomValue<uint16_t>();
    auto align = tests::GenerateRandomValue<size_t>(1, 255);

    serializer& value;
    serializer.AlignData(align);

    auto result = serializer.Data();
    ASSERT_EQ(result.size() % align, 0);
    ASSERT_GE(result.size(), align);

    if (result.size() > align) {
      ASSERT_GE(result.size() / align, 2);
    }
  }
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_100_random_align_uint32_t) {
  for (auto i = 0; i < 100; ++i) {
    auto serializer = stun::Serializer{};
    auto value = tests::GenerateRandomValue<uint32_t>();
    auto align = tests::GenerateRandomValue<size_t>(1, 255);

    serializer& value;
    serializer.AlignData(align);

    auto result = serializer.Data();
    ASSERT_EQ(result.size() % align, 0);
    ASSERT_GE(result.size(), align);

    if (result.size() > align) {
      ASSERT_GE(result.size() / align, 2);
    }
  }
}

//------------------------------------------------------------------------------

TEST(SerializerTest, serialize_100_random_align_uint64_t) {
  for (auto i = 0; i < 100; ++i) {
    auto serializer = stun::Serializer{};
    auto value = tests::GenerateRandomValue<uint64_t>();
    auto align = tests::GenerateRandomValue<size_t>(1, 255);

    serializer& value;
    serializer.AlignData(align);

    auto result = serializer.Data();
    ASSERT_EQ(result.size() % align, 0);
    ASSERT_GE(result.size(), align);

    if (result.size() > align) {
      ASSERT_GE(result.size() / align, 2);
    }
  }
}
