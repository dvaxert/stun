#include <fmt/format.h>

#include <boost/asio/ip/address.hpp>

#include "stun/attributes/address_attribute.h"
#include "stun/utils/to_string.h"

namespace stun {

void AddressAttribute::Serialize(Serializer& s) const {
  s& utils::to_integral(Type()) & DataLength() & uint8_t(0x00) & Family() &
      Port() & Address();
}

//------------------------------------------------------------------------------

void AddressAttribute::Deserialize(Deserializer& d) {
  auto length = d.Get<uint16_t>();
  if (length != DataLength()) throw std::runtime_error("Incorrect attribute");

  d.Pop(2);
  port_ = d.Get<uint16_t>();
  address_ = d.Get<uint32_t>();
}

//------------------------------------------------------------------------------

std::string AddressAttribute::ToString() const {
  return fmt::format("[{0}: {1}:{2}]", utils::ToString(Type()), Address(),
                     Port());
}

//------------------------------------------------------------------------------

uint8_t AddressAttribute::Family() const { return 0x01; }

//------------------------------------------------------------------------------

uint16_t AddressAttribute::Port() const { return port_; }

//------------------------------------------------------------------------------

std::string AddressAttribute::Address() const {
  return boost::asio::ip::address_v4(address_).to_string();
}

//------------------------------------------------------------------------------

uint16_t AddressAttribute::DataLength() const { return 8; }

//------------------------------------------------------------------------------

AddressAttribute::AddressAttribute(uint32_t address, uint16_t port)
    : address_(std::move(address)), port_(std::move(port)) {}

//------------------------------------------------------------------------------

AddressAttribute::AddressAttribute(std::string_view address, uint16_t port)
    : address_(boost::asio::ip::address::from_string(address.data())
                   .to_v4()
                   .to_uint()),
      port_(std::move(port)) {}

}  // namespace stun
