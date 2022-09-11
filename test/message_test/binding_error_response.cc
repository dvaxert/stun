#include <gtest/gtest.h>
#include <stun/attributes/error_code.h>
#include <stun/attributes/unknown_attributes.h>
#include <stun/message.h>
#include <stun/message_builder.h>
#include <stun/serializer.h>
#include <testing_utils/error_code_data.h>

using namespace stun;

TEST(BindingErrorResponseTest, create_default) {
  auto message =
      Message::New()
          .WithType(MessageType::BindingErrorResponse)
          .WithRandomTransactionId()
          .WithAttribute<ErrorCode>(ErrorCode::PredefinedError::BadRequest)
          .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingErrorResponse);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 1);
  ASSERT_TRUE(message.HasAttribute(AttributeType::ErrorCode));
}

//------------------------------------------------------------------------------

TEST(BindingErrorResponseTest, create_with_all_attributes) {
  auto message =
      Message::New()
          .WithType(MessageType::BindingErrorResponse)
          .WithRandomTransactionId()
          .WithAttribute<ErrorCode>(
              ErrorCode::PredefinedError::UnknownAttribute)
          .WithAttribute<UnknownAttributes>(AttributeType::ChangedAddress,
                                            AttributeType::MappedAddress)
          .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingErrorResponse);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 2);
  ASSERT_TRUE(message.HasAttribute(AttributeType::ErrorCode));
  ASSERT_TRUE(message.HasAttribute(AttributeType::UnknownAttributes));
}

//------------------------------------------------------------------------------

TEST(BindingErrorResponseTest, create_with_transaction_id) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message =
      Message::New()
          .WithType(MessageType::BindingErrorResponse)
          .WithTransactionId(id)
          .WithAttribute<ErrorCode>(ErrorCode::PredefinedError::BadRequest)
          .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingErrorResponse);
  ASSERT_EQ(message.TransactionId(), id);
  ASSERT_EQ(message.AllAtributes().size(), 1);
  ASSERT_TRUE(message.HasAttribute(AttributeType::ErrorCode));
}

//------------------------------------------------------------------------------

TEST(BindingErrorResponseTest, serialize) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message =
      Message::New()
          .WithType(MessageType::BindingErrorResponse)
          .WithTransactionId(id)
          .WithAttribute<ErrorCode>(ErrorCode::PredefinedError::BadRequest)
          .Build();
  Serializer s{};
  s& message;

  std::vector<uint8_t> error_code_attribute = {0x00, 0x09, 0x00, 0x78,
                                               0x00, 0x00, 0x04, 0x00};
  error_code_attribute.insert(error_code_attribute.end(),
                              tests::BadRequestMsg.begin(),
                              tests::BadRequestMsg.end());
  error_code_attribute.emplace_back(0);

  std::vector<uint8_t> check = {0x01, 0x11, 0x00, 0x7c, 0x00, 0x01, 0x02,
                                0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
                                0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
  check.insert(check.end(), error_code_attribute.begin(),
               error_code_attribute.end());

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(BindingErrorResponseTest, serialize_with_unknown_attributes) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message =
      Message::New()
          .WithType(MessageType::BindingErrorResponse)
          .WithTransactionId(id)
          .WithAttribute<ErrorCode>(
              ErrorCode::PredefinedError::UnknownAttribute)
          .WithAttribute<UnknownAttributes>(AttributeType::ChangedAddress,
                                            AttributeType::MappedAddress)
          .Build();
  Serializer s{};
  s& message;

  std::vector<uint8_t> error_code_attribute = {0x00, 0x09, 0x00, 0x48,
                                               0x00, 0x00, 0x04, 0x14};
  error_code_attribute.insert(error_code_attribute.end(),
                              tests::UnknownAttributeMsg.begin(),
                              tests::UnknownAttributeMsg.end());
  error_code_attribute.emplace_back(0);

  std::vector<uint8_t> unknown_attributes_attribute = {0x00, 0x0a, 0x00, 0x04,
                                                       0x00, 0x05, 0x00, 0x01};

  std::vector<uint8_t> check = {0x01, 0x11, 0x00, 0x54, 0x00, 0x01, 0x02,
                                0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
                                0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
  check.insert(check.end(), error_code_attribute.begin(),
               error_code_attribute.end());
  check.insert(check.end(), unknown_attributes_attribute.begin(),
               unknown_attributes_attribute.end());

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}
