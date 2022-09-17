#ifndef STUN_LIB_INCLUDE_STUN_DESERIALIZER_H_
#define STUN_LIB_INCLUDE_STUN_DESERIALIZER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <boost/endian/conversion.hpp>

namespace stun {

class Deserializer final {
 public:
  Deserializer(std::vector<uint8_t> raw_data);

  bool HasData() const;
  void Pop(size_t count);

  template <class T, std::enable_if_t<std::is_pod_v<T>, bool> = true>
  T Peek() {
    CheckSize(sizeof(T));
    return boost::endian::big_to_native(*reinterpret_cast<T*>(data_.data() + pos_));
  }

  template <class T, std::enable_if_t<std::is_pod_v<T>, bool> = true>
  T Get() {
    T result = Peek<T>();
    UpdatePos(sizeof(T));
    return result;
  }

  template <class T, std::enable_if_t<std::is_pod_v<T>, bool> = true>
  std::vector<T> GetArray(size_t array_size) {
    if (array_size == 0) {
      return {};
    }

    CheckSize(array_size * sizeof(T));
    std::vector<T> result{};
    result.reserve(array_size);

    for (auto i = 0; i < array_size; ++i) {
      result.emplace_back(Get<T>());
    }

    return result;
  }

  std::string GetString(size_t string_size);

 private:
  void UpdatePos(size_t s);
  void CheckSize(size_t s) const;

  std::vector<uint8_t> data_;
  size_t pos_;
};


}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_DESERIALIZER_H_
