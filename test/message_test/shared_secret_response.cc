#include <gtest/gtest.h>
#include <stun/attributes/password.h>
#include <stun/attributes/username.h>
#include <stun/message.h>
#include <stun/message_builder.h>
#include <stun/serializer.h>

using namespace stun;

TEST(SharedSecretResponseTest, create_default) {
  auto message = Message::New()
                     .WithType(MessageType::SharedSecretResponse)
                     .WithRandomTransactionId()
                     .WithAttribute<Username>("SomeName")
                     .WithAttribute<Password>("SomePass")
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::SharedSecretResponse);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 2);
  ASSERT_TRUE(message.HasAttribute(AttributeType::Username));
  ASSERT_TRUE(message.HasAttribute(AttributeType::Password));
}

//------------------------------------------------------------------------------

TEST(SharedSecretResponseTest, create_with_transaction_id) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message = Message::New()
                     .WithType(MessageType::SharedSecretResponse)
                     .WithTransactionId(id)
                     .WithAttribute<Username>("SomeName")
                     .WithAttribute<Password>("SomePass")
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::SharedSecretResponse);
  ASSERT_EQ(message.TransactionId(), id);
  ASSERT_EQ(message.AllAtributes().size(), 2);
  ASSERT_TRUE(message.HasAttribute(AttributeType::Username));
  ASSERT_TRUE(message.HasAttribute(AttributeType::Password));
}