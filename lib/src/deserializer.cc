#include <stdexcept>

#include "stun/deserializer.h"

namespace stun {

Deserializer::Deserializer(std::vector<uint8_t> raw_data)
    : data_(std::move(raw_data)), pos_(0) {}

//------------------------------------------------------------------------------

bool Deserializer::HasData() const { return pos_ < data_.size(); }

//------------------------------------------------------------------------------

void Deserializer::Pop(size_t count) {
  CheckSize(count);
  UpdatePos(count);
}

//------------------------------------------------------------------------------

std::string Deserializer::GetString(size_t string_size) {
  if (string_size == 0) {
    return {};
  }

  CheckSize(string_size);
  auto it_begin = std::next(data_.begin(), pos_);
  auto it_end = std::next(it_begin, string_size);
  pos_ += string_size;

  auto result = std::string(it_begin, it_end);

  while (result.back() == '\0') {
    result.pop_back();
  }
  result.shrink_to_fit();

  return result;
}

//------------------------------------------------------------------------------

void Deserializer::CheckSize(size_t s) const {
  if (pos_ + s > data_.size()) {
    throw std::runtime_error("Deserializer has no more data!");
  }
}

//------------------------------------------------------------------------------

void Deserializer::UpdatePos(size_t s) { pos_ += s; }

}  // namespace stun
