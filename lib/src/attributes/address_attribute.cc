#include <boost/asio/ip/address.hpp>

#include "stun/attributes/address_attribute.h"

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

uint8_t AddressAttribute::Family() const { return 0x01; }

//------------------------------------------------------------------------------

uint16_t AddressAttribute::Port() const { return port_; }

//------------------------------------------------------------------------------

uint32_t AddressAttribute::Address() const { return address_; }

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
