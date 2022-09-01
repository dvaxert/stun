#include <boost/endian/conversion.hpp>
#include <stdexcept>

#include "stun/serializer.h"

namespace stun {

class Serializer::Impl {
 public:
  Impl() : data_(), size_() {}

  template <class T>
  void Serialize(T value) {
    CheckSize(sizeof(value));

    new (NextPos()) T{boost::endian::native_to_big(value)};
    size_ += sizeof(value);
  }

  void AlignData(size_t align) {
    auto remainder = size_ % align;

    if (remainder != 0) {
      auto need_to_add = align - remainder;
      CheckSize(need_to_add);

      size_ += need_to_add;
    }
  }

  std::vector<uint8_t> Data() const {
    return {data_.begin(), data_.begin() + size_};
  }

 private:
  uint8_t* NextPos() { return data_.data() + size_; }

  void CheckSize(size_t s) const {
    if (size_ + s >= data_.size()) {
      throw std::runtime_error("Serializer data overflow!");
    }
  }

  std::array<uint8_t, 1016> data_;
  size_t size_;
};

//------------------------------------------------------------------------------

Serializer::Serializer() : impl_() {}

//------------------------------------------------------------------------------

Serializer::~Serializer() noexcept {}

//------------------------------------------------------------------------------

std::vector<uint8_t> Serializer::Data() const { return impl_->Data(); }

//------------------------------------------------------------------------------

void Serializer::AlignData(size_t align) { impl_->AlignData(align); }

//------------------------------------------------------------------------------

ISerializer& Serializer::Serialize(uint8_t value) {
  impl_->Serialize(value);
  return *this;
}

//------------------------------------------------------------------------------

ISerializer& Serializer::Serialize(uint32_t value) {
  impl_->Serialize(value);
  return *this;
}

//------------------------------------------------------------------------------

ISerializer& Serializer::Serialize(uint16_t value) {
  impl_->Serialize(value);
  return *this;
}

//------------------------------------------------------------------------------

stun::ISerializer& Serializer::Serialize(char value) {
  impl_->Serialize(value);
  return *this;
}

//------------------------------------------------------------------------------

stun::ISerializer& Serializer::Serialize(uint64_t value) {
  impl_->Serialize(value);
  return *this;
}

}  // namespace stun
