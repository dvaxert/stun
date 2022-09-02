#include <gtest/gtest.h>
#include <stun/attributes/error_code.h>
#include <stun/attributes/unknown_attributes.h>
#include <stun/message.h>
#include <stun/message_builder.h>
#include <stun/serializer.h>

using namespace stun;

TEST(SharedSecretErrorResponseTest, create_default) {
  auto message =
      Message::New()
          .WithType(MessageType::SharedSecretErrorResponse)
          .WithRandomTransactionId()
          .WithAttribute<ErrorCode>(ErrorCode::PredefinedError::BadRequest)
          .Build();

  ASSERT_EQ(message.Type(), MessageType::SharedSecretErrorResponse);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 1);
  ASSERT_TRUE(message.HasAttribute(AttributeType::ErrorCode));
}

//------------------------------------------------------------------------------

TEST(SharedSecretErrorResponseTest, create_with_transaction_id) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message =
      Message::New()
          .WithType(MessageType::SharedSecretErrorResponse)
          .WithTransactionId(id)
          .WithAttribute<ErrorCode>(ErrorCode::PredefinedError::BadRequest)
          .Build();

  ASSERT_EQ(message.Type(), MessageType::SharedSecretErrorResponse);
  ASSERT_EQ(message.TransactionId(), id);
  ASSERT_EQ(message.AllAtributes().size(), 1);
  ASSERT_TRUE(message.HasAttribute(AttributeType::ErrorCode));
}

//------------------------------------------------------------------------------

TEST(SharedSecretErrorResponseTest, create_with_unknown_attributes) {
  auto message =
      Message::New()
          .WithType(MessageType::SharedSecretErrorResponse)
          .WithRandomTransactionId()
          .WithAttribute<ErrorCode>(
              ErrorCode::PredefinedError::UnknownAttribute)
          .WithAttribute<UnknownAttributes>(AttributeType::ReflectedFrom,
                                            AttributeType::ChangedAddress)
          .Build();

  ASSERT_EQ(message.Type(), MessageType::SharedSecretErrorResponse);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 2);
  ASSERT_TRUE(message.HasAttribute(AttributeType::ErrorCode));
  ASSERT_TRUE(message.HasAttribute(AttributeType::UnknownAttributes));
}
