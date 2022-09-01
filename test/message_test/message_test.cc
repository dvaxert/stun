#include <gtest/gtest.h>
#include <stun/attributes/change_request.h>
#include <stun/attributes/response_address.h>
#include <stun/attributes/username.h>
#include <stun/message.h>
#include <stun/message_builder.h>
#include <stun/serializer.h>

using namespace stun;

TEST(MessageTest, create_binding_request_default) {
  auto message = Message::Builder()
                     .WithType(MessageType::BindingRequest)
                     .WithRandomTransactionId()
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingRequest);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 0);
}

//------------------------------------------------------------------------------

TEST(MessageTest, create_binding_with_transaction_id) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message = Message::Builder()
                     .WithType(MessageType::BindingRequest)
                     .WithTransactionId(id)
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingRequest);
  ASSERT_EQ(message.TransactionId(), id);
  ASSERT_EQ(message.AllAtributes().size(), 0);
}

//------------------------------------------------------------------------------

TEST(MessageTest, create_binding_request_with_attributes) {
  auto message = Message::Builder()
                     .WithType(MessageType::BindingRequest)
                     .WithRandomTransactionId()
                     .WithAttribute<ResponseAddress>("127.0.0.1", 1234)
                     .WithAttribute<ChangeRequest>(true, true)
                     .WithAttribute<Username>("some_name")
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingRequest);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 3);
  ASSERT_TRUE(message.HasAttribute(AttributeType::ResponseAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::ChangeRequest));
  ASSERT_TRUE(message.HasAttribute(AttributeType::Username));
}

//------------------------------------------------------------------------------

TEST(MessageTest, create_binding_request_with_integrity) {
  auto message = Message::Builder()
                     .WithType(MessageType::BindingRequest)
                     .WithRandomTransactionId()
                     .WithIntegrity()
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingRequest);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 1);
  ASSERT_TRUE(message.HasAttribute(AttributeType::MessageIntegrity));
}

//------------------------------------------------------------------------------

TEST(MessageTest, create_binding_request_with_all_attributes) {
  auto message = Message::Builder()
                     .WithType(MessageType::BindingRequest)
                     .WithRandomTransactionId()
                     .WithAttribute<ResponseAddress>("127.0.0.1", 1234)
                     .WithAttribute<ChangeRequest>(true, true)
                     .WithAttribute<Username>("some_name")
                     .WithIntegrity()
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingRequest);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 4);
  ASSERT_TRUE(message.HasAttribute(AttributeType::ResponseAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::ChangeRequest));
  ASSERT_TRUE(message.HasAttribute(AttributeType::Username));
  ASSERT_TRUE(message.HasAttribute(AttributeType::MessageIntegrity));
  ASSERT_EQ((*message.AllAtributes().rbegin())->Type(),
            AttributeType::MessageIntegrity);
}
