#include <gtest/gtest.h>
#include <stun/attributes/change_request.h>
#include <stun/attributes/response_address.h>
#include <stun/attributes/username.h>
#include <stun/message.h>
#include <stun/message_builder.h>
#include <stun/serializer.h>

using namespace stun;

TEST(BindingRequestTest, create_default) {
  auto message = Message::New()
                     .WithType(MessageType::BindingRequest)
                     .WithRandomTransactionId()
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingRequest);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 0);
}

//------------------------------------------------------------------------------

TEST(BindingRequestTest, create_with_transaction_id) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message = Message::New()
                     .WithType(MessageType::BindingRequest)
                     .WithTransactionId(id)
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingRequest);
  ASSERT_EQ(message.TransactionId(), id);
  ASSERT_EQ(message.AllAtributes().size(), 0);
}

//------------------------------------------------------------------------------

TEST(BindingRequestTest, create_with_attributes) {
  auto message = Message::New()
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

TEST(BindingRequestTest, create_with_integrity) {
  auto message = Message::New()
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

TEST(BindingRequestTest, create_with_all_attributes) {
  auto message = Message::New()
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

//------------------------------------------------------------------------------

TEST(BindingRequestTest, serialize) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message = Message::New()
                     .WithType(MessageType::BindingRequest)
                     .WithTransactionId(id)
                     .Build();
  Serializer s{};
  s& message;

  std::vector<uint8_t> check = {0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x02,
                                0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
                                0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(BindingRequestTest, serialize_with_attribute) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message = Message::New()
                     .WithType(MessageType::BindingRequest)
                     .WithTransactionId(id)
                     .WithAttribute<ResponseAddress>("127.0.0.1", 1234)
                     .Build();
  Serializer s{};
  s& message;

  const std::vector<uint8_t> check = {
      0x00, 0x01, 0x00, 0x0C, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
      0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x02,
      0x00, 0x08, 0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01};

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(BindingRequestTest, serialize_with_integrity) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message = Message::New()
                     .WithType(MessageType::BindingRequest)
                     .WithTransactionId(id)
                     .WithAttribute<ResponseAddress>("127.0.0.1", 1234)
                     .WithIntegrity()
                     .Build();
  Serializer s{};
  s& message;

  std::vector<uint8_t> check = {
      0x00, 0x01, 0x00, 0x4C, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x02, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x3C,
      0xA8, 0xEC, 0xBF, 0xC7, 0xC7, 0xC0, 0xA6, 0xB3, 0xBE, 0x3D, 0x6B, 0xEE,
      0x0A, 0x66, 0x4D, 0x42, 0x82, 0xB2, 0xEF, 0xC8};
  check.insert(check.end(), 40, 0);

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}
