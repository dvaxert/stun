#include <gtest/gtest.h>
#include <stun/attributes/changed_address.h>
#include <stun/attributes/mapped_address.h>
#include <stun/attributes/reflected_from.h>
#include <stun/attributes/source_address.h>
#include <stun/message.h>
#include <stun/message_builder.h>
#include <stun/serializer.h>

using namespace stun;

TEST(BindingResponseTest, create_default) {
  auto message = Message::New()
                     .WithType(MessageType::BindingResponse)
                     .WithRandomTransactionId()
                     .WithAttribute<MappedAddress>("127.0.0.1", 1234)
                     .WithAttribute<SourceAddress>("127.0.0.1", 1234)
                     .WithAttribute<ChangedAddress>("127.0.0.1", 1234)
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingResponse);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 3);
  ASSERT_TRUE(message.HasAttribute(AttributeType::MappedAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::SourceAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::ChangedAddress));
}

//------------------------------------------------------------------------------

TEST(BindingResponseTest, create_with_transaction_id) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message = Message::New()
                     .WithType(MessageType::BindingResponse)
                     .WithTransactionId(id)
                     .WithAttribute<MappedAddress>("127.0.0.1", 1234)
                     .WithAttribute<SourceAddress>("127.0.0.1", 1234)
                     .WithAttribute<ChangedAddress>("127.0.0.1", 1234)
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingResponse);
  ASSERT_EQ(message.TransactionId(), id);
  ASSERT_EQ(message.AllAtributes().size(), 3);
  ASSERT_TRUE(message.HasAttribute(AttributeType::MappedAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::SourceAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::ChangedAddress));
}

//------------------------------------------------------------------------------

TEST(BindingResponseTest, create_with_reflected_from) {
  auto message = Message::New()
                     .WithType(MessageType::BindingResponse)
                     .WithRandomTransactionId()
                     .WithAttribute<MappedAddress>("127.0.0.1", 1234)
                     .WithAttribute<SourceAddress>("127.0.0.1", 1234)
                     .WithAttribute<ChangedAddress>("127.0.0.1", 1234)
                     .WithAttribute<ReflectedFrom>("127.0.0.1", 1234)
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingResponse);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 4);
  ASSERT_TRUE(message.HasAttribute(AttributeType::MappedAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::SourceAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::ChangedAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::ReflectedFrom));
}

//------------------------------------------------------------------------------

TEST(BindingResponseTest, create_with_message_integrity) {
  auto message = Message::New()
                     .WithType(MessageType::BindingResponse)
                     .WithRandomTransactionId()
                     .WithAttribute<MappedAddress>("127.0.0.1", 1234)
                     .WithAttribute<SourceAddress>("127.0.0.1", 1234)
                     .WithAttribute<ChangedAddress>("127.0.0.1", 1234)
                     .WithIntegrity()
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingResponse);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 4);
  ASSERT_TRUE(message.HasAttribute(AttributeType::MappedAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::SourceAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::ChangedAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::MessageIntegrity));
  ASSERT_EQ((*message.AllAtributes().rbegin())->Type(),
            AttributeType::MessageIntegrity);
}

//------------------------------------------------------------------------------

TEST(BindingResponseTest, create_with_all) {
  auto message = Message::New()
                     .WithType(MessageType::BindingResponse)
                     .WithRandomTransactionId()
                     .WithAttribute<MappedAddress>("127.0.0.1", 1234)
                     .WithAttribute<SourceAddress>("127.0.0.1", 1234)
                     .WithAttribute<ChangedAddress>("127.0.0.1", 1234)
                     .WithAttribute<ReflectedFrom>("127.0.0.1", 1234)
                     .WithIntegrity()
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::BindingResponse);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 5);
  ASSERT_TRUE(message.HasAttribute(AttributeType::MappedAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::SourceAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::ChangedAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::ReflectedFrom));
  ASSERT_TRUE(message.HasAttribute(AttributeType::MessageIntegrity));
  ASSERT_EQ((*message.AllAtributes().rbegin())->Type(),
            AttributeType::MessageIntegrity);
}

//------------------------------------------------------------------------------

TEST(BindingResponseTest, serialize) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message = Message::New()
                     .WithType(MessageType::BindingResponse)
                     .WithTransactionId(id)
                     .WithAttribute<MappedAddress>("127.0.0.1", 1234)
                     .WithAttribute<SourceAddress>("127.0.0.1", 1234)
                     .WithAttribute<ChangedAddress>("127.0.0.1", 1234)
                     .Build();

  Serializer s{};
  s& message;

  std::vector<uint8_t> check = {
      0x01, 0x01, 0x00, 0x24, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x01, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01, 0x00, 0x05, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01};

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(BindingResponseTest, serialize_with_integrity) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message = Message::New()
                     .WithType(MessageType::BindingResponse)
                     .WithTransactionId(id)
                     .WithAttribute<MappedAddress>("127.0.0.1", 1234)
                     .WithAttribute<SourceAddress>("127.0.0.1", 1234)
                     .WithAttribute<ChangedAddress>("127.0.0.1", 1234)
                     .WithIntegrity()
                     .Build();

  Serializer s{};
  s& message;

  std::vector<uint8_t> check = {
      0x01, 0x01, 0x00, 0x64, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x01, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01, 0x00, 0x05, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x3C,
      0xB3, 0x89, 0x1F, 0x94, 0x9A, 0x13, 0x44, 0x60, 0x1A, 0x36, 0x05, 0x13,
      0xA0, 0x50, 0xAF, 0xED, 0x66, 0xFC, 0x3C, 0x74};
  check.insert(check.end(), 40, 0);

  ASSERT_EQ(s.Data().size(), check.size());
  ASSERT_EQ(s.Data(), check);
}

//------------------------------------------------------------------------------

TEST(BindingResponseTest, deserialize) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  const std::vector<uint8_t> data = {
      0x01, 0x01, 0x00, 0x24, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x01, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01, 0x00, 0x05, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01};

  auto message = Message::FromRaw(data);

  ASSERT_EQ(message.Type(), MessageType::BindingResponse);
  ASSERT_EQ(message.TransactionId(), id);
  ASSERT_TRUE(message.HasAttribute(AttributeType::MappedAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::SourceAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::ChangedAddress));
  ASSERT_TRUE(message.AllAtributes().size(), 3);

  auto ma_attr = std::dynamic_pointer_cast<MappedAddress>(
      message.Attribute(AttributeType::MappedAddress));

  ASSERT_NE(ma_attr, nullptr);
  ASSERT_EQ(ma_attr->Family(), 0x01);
  ASSERT_EQ(ma_attr->Port(), 1234);
  ASSERT_EQ(ma_attr->Address(), 0x7F000001);  // 127.0.0.1

  auto sa_attr = std::dynamic_pointer_cast<SourceAddress>(
      message.Attribute(AttributeType::SourceAddress));

  ASSERT_NE(sa_attr, nullptr);
  ASSERT_EQ(sa_attr->Family(), 0x01);
  ASSERT_EQ(sa_attr->Port(), 1234);
  ASSERT_EQ(sa_attr->Address(), 0x7F000001);  // 127.0.0.1

  auto ca_attr = std::dynamic_pointer_cast<ChangedAddress>(
      message.Attribute(AttributeType::ChangedAddress));

  ASSERT_NE(ca_attr, nullptr);
  ASSERT_EQ(ca_attr->Family(), 0x01);
  ASSERT_EQ(ca_attr->Port(), 1234);
  ASSERT_EQ(ca_attr->Address(), 0x7F000001);  // 127.0.0.1
}

//------------------------------------------------------------------------------

TEST(BindingResponseTest, deserialize_with_integrity) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  std::vector<uint8_t> data = {
      0x01, 0x01, 0x00, 0x64, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x01, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01, 0x00, 0x05, 0x00, 0x08,
      0x00, 0x01, 0x04, 0xD2, 0x7F, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x3C,
      0xB3, 0x89, 0x1F, 0x94, 0x9A, 0x13, 0x44, 0x60, 0x1A, 0x36, 0x05, 0x13,
      0xA0, 0x50, 0xAF, 0xED, 0x66, 0xFC, 0x3C, 0x74};
  data.insert(data.end(), 40, 0);

  auto message = Message::FromRaw(data);

  ASSERT_EQ(message.Type(), MessageType::BindingResponse);
  ASSERT_EQ(message.TransactionId(), id);
  ASSERT_TRUE(message.HasAttribute(AttributeType::MappedAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::SourceAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::ChangedAddress));
  ASSERT_TRUE(message.HasAttribute(AttributeType::MessageIntegrity));
  ASSERT_TRUE(message.AllAtributes().size(), 4);

  auto ma_attr = std::dynamic_pointer_cast<MappedAddress>(
      message.Attribute(AttributeType::MappedAddress));

  ASSERT_NE(ma_attr, nullptr);
  ASSERT_EQ(ma_attr->Family(), 0x01);
  ASSERT_EQ(ma_attr->Port(), 1234);
  ASSERT_EQ(ma_attr->Address(), 0x7F000001);  // 127.0.0.1

  auto sa_attr = std::dynamic_pointer_cast<SourceAddress>(
      message.Attribute(AttributeType::SourceAddress));

  ASSERT_NE(sa_attr, nullptr);
  ASSERT_EQ(sa_attr->Family(), 0x01);
  ASSERT_EQ(sa_attr->Port(), 1234);
  ASSERT_EQ(sa_attr->Address(), 0x7F000001);  // 127.0.0.1

  auto ca_attr = std::dynamic_pointer_cast<ChangedAddress>(
      message.Attribute(AttributeType::ChangedAddress));

  ASSERT_NE(ca_attr, nullptr);
  ASSERT_EQ(ca_attr->Family(), 0x01);
  ASSERT_EQ(ca_attr->Port(), 1234);
  ASSERT_EQ(ca_attr->Address(), 0x7F000001);  // 127.0.0.1

  auto mi_attr = std::dynamic_pointer_cast<MessageIntegrity>(
      message.Attribute(AttributeType::MessageIntegrity));

  const std::vector<uint8_t> integrity_check = {
      0xB3, 0x89, 0x1F, 0x94, 0x9A, 0x13, 0x44, 0x60, 0x1A, 0x36,
      0x05, 0x13, 0xA0, 0x50, 0xAF, 0xED, 0x66, 0xFC, 0x3C, 0x74};

  ASSERT_NE(mi_attr, nullptr);
  ASSERT_EQ(mi_attr->Value(), integrity_check);
}
