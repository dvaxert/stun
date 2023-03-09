#include <stdexcept>

#include "stun/serializer.h"

namespace stun {

std::vector<uint8_t> Serializer::Data() const {
  return {data_.begin(), data_.begin() + size_};
}

//------------------------------------------------------------------------------

void Serializer::AlignData(size_t align) {
  auto remainder = size_ % align;

  if (remainder != 0) {
    auto need_to_add = align - remainder;
    CheckSize(need_to_add);

    size_ += need_to_add;
  }
}

//------------------------------------------------------------------------------

void Serializer::Clean() {
  std::memset(data_.data(), 0, size_);
  size_ = 0;
}

//------------------------------------------------------------------------------

uint8_t* Serializer::NextPos() { return data_.data() + size_; }

//------------------------------------------------------------------------------

void Serializer::CheckSize(size_t s) const {
  if (size_ + s >= data_.size()) {
    throw std::runtime_error("Serializer data overflow!");
  }
}

}  // namespace stun
