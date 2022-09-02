#include <gtest/gtest.h>
#include <stun/attributes/change_request.h>
#include <stun/attributes/response_address.h>
#include <stun/attributes/username.h>
#include <stun/message.h>
#include <stun/message_builder.h>
#include <stun/serializer.h>

using namespace stun;

TEST(SharedSecretRequestTest, create_default) {
  auto message = Message::New()
                     .WithType(MessageType::SharedSecretRequest)
                     .WithRandomTransactionId()
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::SharedSecretRequest);
  ASSERT_NE(message.TransactionId(), std::vector<uint8_t>(16, 0));
  ASSERT_EQ(message.AllAtributes().size(), 0);
}

//------------------------------------------------------------------------------

TEST(SharedSecretRequestTest, create_with_transaction_id) {
  const std::vector<uint8_t> id = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                   0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                   0x0C, 0x0D, 0x0E, 0x0F};

  auto message = Message::New()
                     .WithType(MessageType::SharedSecretRequest)
                     .WithTransactionId(id)
                     .Build();

  ASSERT_EQ(message.Type(), MessageType::SharedSecretRequest);
  ASSERT_EQ(message.TransactionId(), id);
  ASSERT_EQ(message.AllAtributes().size(), 0);
}
