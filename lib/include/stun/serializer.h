#ifndef STUN_LIB_INCLUDE_STUN_SERALIZER_H_
#define STUN_LIB_INCLUDE_STUN_SERALIZER_H_

#include <array>
#include <boost/endian/conversion.hpp>
#include <memory>
#include <vector>

#include "stun/utils/traits.h"

namespace stun {

class Serializer final {
 public:
  std::vector<uint8_t> Data() const;
  void AlignData(size_t align);

  template <class T, std::enable_if_t<std::is_pod_v<T>, bool> = true>
  Serializer& Serialize(const T& value) {
    CheckSize(sizeof(value));

    new (NextPos()) T{boost::endian::native_to_big(value)};
    size_ += sizeof(value);
    return *this;
  }

  template <class Container,
            std::enable_if_t<!std::is_pod_v<Container>, bool> = true,
            std::enable_if_t<utils::is_iterable_v<Container>, bool> = true>
  Serializer& Serialize(const Container& container) {
    using Value = typename Container::value_type;

    for (Value val : container) {
      this->Serialize(val);
    }
    return *this;
  }

  template <class Object, std::enable_if_t<!std::is_pod_v<Object>, bool> = true,
            std::enable_if_t<!utils::is_iterable_v<Object>, bool> = true>
  Serializer& Serialize(const Object& obj) {
    obj.Serialize(*this);
    return *this;
  }

 private:
  uint8_t* NextPos();
  void CheckSize(size_t s) const;

  std::array<uint8_t, 1016> data_;
  size_t size_;
};

//------------------------------------------------------------------------------

template <class T>
Serializer& operator&(Serializer& s, const T& value) {
  return s.Serialize(value);
}

//------------------------------------------------------------------------------

template <class T>
Serializer& operator&(Serializer& s, std::shared_ptr<T> value) {
  return s.Serialize(*value);
}

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_SERALIZER_H_
