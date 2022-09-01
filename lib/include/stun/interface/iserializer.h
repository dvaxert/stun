#ifndef STUN_LIB_INCLUDE_STUN_INTERFACE_ISERIALIZER_H_
#define STUN_LIB_INCLUDE_STUN_INTERFACE_ISERIALIZER_H_

#include <cstdint>
#include <memory>
#include <type_traits>
#include <vector>

#include "stun/utils/traits.h"

namespace stun {

class ISerializer {
 public:
  ISerializer() = default;
  virtual ~ISerializer() noexcept = default;

  virtual std::vector<uint8_t> Data() const = 0;
  virtual void AlignData(size_t align) = 0;

  virtual ISerializer& Serialize(char value) = 0;
  virtual ISerializer& Serialize(uint8_t value) = 0;
  virtual ISerializer& Serialize(uint16_t value) = 0;
  virtual ISerializer& Serialize(uint32_t value) = 0;
  virtual ISerializer& Serialize(uint64_t value) = 0;

  template <
      class Container, std::enable_if_t<!std::is_pod_v<Container>, bool> = true,
      std::enable_if_t<stun::utils::is_iterable_v<Container>, bool> = true>
  ISerializer& Serialize(Container& container) {
    using Value = typename Container::value_type;

    for (Value val : container) {
      this->Serialize(val);
    }
    return *this;
  }

  template <class Object, std::enable_if_t<!std::is_pod_v<Object>, bool> = true,
            std::enable_if_t<!stun::utils::is_iterable_v<Object>, bool> = true>
  ISerializer& Serialize(const Object& obj) {
    obj.Serialize(*this);
    return *this;
  }
};

template <class T>
ISerializer& operator&(ISerializer& s, T&& value) {
  return s.Serialize(std::forward<T>(value));
}

template <class T>
ISerializer& operator&(ISerializer& s, std::shared_ptr<T> value) {
  return s.Serialize(*value);
}

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_INTERFACE_ISERIALIZER_H_
