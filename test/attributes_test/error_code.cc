#include <gtest/gtest.h>
#include <stun/attributes/error_code.h>
#include <stun/serializer.h>
#include <stun/deserializer.h>
#include <testing_utils/error_code_data.h>
#include <testing_utils/random.h>

using namespace stun;
using namespace tests;

TEST(ErrorCodeTest, create_predefined_bad_request) {
  auto predefined = ErrorCode(ErrorCode::PredefinedError::BadRequest);

  ASSERT_EQ(predefined.Code(), BadRequestCode);
  ASSERT_EQ(predefined.Message(), BadRequestMsg);
}

//------------------------------------------------------------------------------

TEST(ErrorCodeTest, create_predefined_global_failure) {
  auto predefined = ErrorCode(ErrorCode::PredefinedError::GlobalFailure);

  ASSERT_EQ(predefined.Code(), GlobalFailureCode);
  ASSERT_EQ(predefined.Message(), GlobalFailureMsg);
}

//------------------------------------------------------------------------------

TEST(ErrorCodeTest, create_predefined_integrity_check_failure) {
  auto predefined =
      ErrorCode(ErrorCode::PredefinedError::IntegrityCheckFailure);

  ASSERT_EQ(predefined.Code(), IntegrityCheckFailureCode);
  ASSERT_EQ(predefined.Message(), IntegrityCheckFailureMsg);
}

//------------------------------------------------------------------------------

TEST(ErrorCodeTest, create_predefined_missing_username) {
  auto predefined = ErrorCode(ErrorCode::PredefinedError::MissingUsername);

  ASSERT_EQ(predefined.Code(), MissingUsernameCode);
  ASSERT_EQ(predefined.Message(), MissingUsernameMsg);
}

//------------------------------------------------------------------------------

TEST(ErrorCodeTest, create_predefined_server_error) {
  auto predefined = ErrorCode(ErrorCode::PredefinedError::ServerError);

  ASSERT_EQ(predefined.Code(), ServerErrorCode);
  ASSERT_EQ(predefined.Message(), ServerErrorMsg);
}

//------------------------------------------------------------------------------

TEST(ErrorCodeTest, create_predefined_stale_credentials) {
  auto predefined = ErrorCode(ErrorCode::PredefinedError::StaleCredentials);

  ASSERT_EQ(predefined.Code(), StaleCredentialsCode);
  ASSERT_EQ(predefined.Message(), StaleCredentialsMsg);
}

//------------------------------------------------------------------------------

TEST(ErrorCodeTest, create_predefined_unauthorized) {
  auto predefined = ErrorCode(ErrorCode::PredefinedError::Unauthorized);

  ASSERT_EQ(predefined.Code(), UnauthorizedCode);
  ASSERT_EQ(predefined.Message(), UnauthorizedMsg);
}

//------------------------------------------------------------------------------

TEST(ErrorCodeTest, create_predefined_unknown_attribute) {
  auto predefined = ErrorCode(ErrorCode::PredefinedError::UnknownAttribute);

  ASSERT_EQ(predefined.Code(), UnknownAttributeCode);
  ASSERT_EQ(predefined.Message(), UnknownAttributeMsg);
}

//------------------------------------------------------------------------------

TEST(ErrorCodeTest, create_predefined_use_tls) {
  auto predefined = ErrorCode(ErrorCode::PredefinedError::UseTLS);

  ASSERT_EQ(predefined.Code(), UseTLSCode);
  ASSERT_EQ(predefined.Message(), UseTLSMsg);
}

//------------------------------------------------------------------------------

TEST(ErrorCodeTest, create_some_error) {
  const auto testing_code = uint32_t(115);
  const auto testing_msg = std::string("some message");
  auto error = ErrorCode(testing_code, testing_msg);

  ASSERT_EQ(error.Code(), testing_code);
  ASSERT_EQ(error.Message(), testing_msg);
}

//------------------------------------------------------------------------------

TEST(ErrorCodeTest, serialize) {
  const auto testing_code = tests::GenerateRandomValue<uint16_t>(100, 699);
  const auto testing_msg = std::string("some error message");
  auto error = ErrorCode(testing_code, testing_msg);
  Serializer s{};

  const auto error_class = uint8_t(testing_code / 100);
  const auto error_number = uint8_t(testing_code % 100);

  s& error;

  std::vector<uint8_t> check = {0x00, 0x09, 0x00,        0x04,
                                0x00, 0x00, error_class, error_number};

  for (auto ch : testing_msg) {
    check[3] += 1;
    check.emplace_back(uint8_t(ch));
  }

  if ((check.size() % 4) != 0) {
    const auto add_size = uint8_t(4 - check.size() % 4);
    check.insert(check.end(), add_size, 0);
    check[3] += add_size;
  }

  ASSERT_EQ(error.Code(), testing_code);
  ASSERT_EQ(error.Message(), testing_msg);
  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(ErrorCodeTest, deserialize) {
  auto error = ErrorCode();

  std::vector<uint8_t> data = {0x00, 0x10, 0x00, 0x00, 0x03, 0x17,
                               'T',  'e',  's',  't',  'i',  'n',
                               'g',  'E',  'r',  'r',  'o',  'r'};
  Deserializer d(data);
  error.Deserialize(d);

  ASSERT_EQ(error.Code(), 323);
  ASSERT_EQ(error.Message(), "TestingError");
  ASSERT_FALSE(d.HasData());
}
