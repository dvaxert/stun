// FastPimpl implementation by Yandex Taxi
// taken from -> https://www.youtube.com/watch?v=mkPTreWiglk

#ifndef STUN_LIB_INCLUDE_STUN_UTILS_FAST_PIMPL_H_
#define STUN_LIB_INCLUDE_STUN_UTILS_FAST_PIMPL_H_

#include <type_traits>

namespace stun {
namespace utils {

template <class T, size_t Size, size_t Alignment>
class FastPimpl {
 public:
  template <class... Args>
  explicit FastPimpl(Args&&... args) {
    new (Ptr()) T(std::forward<Args>(args)...);
  }

  FastPimpl(const FastPimpl& other) { *Ptr() = *other.Ptr(); }
  FastPimpl(FastPimpl&& other) { *Ptr() = std::move(*other.Ptr()); }
  FastPimpl& operator=(const FastPimpl& other) { *Ptr() = *other.Ptr(); }
  FastPimpl& operator=(FastPimpl&& other) noexcept {
    *Ptr() = std::move(*other.Ptr());
    return *this;
  }

  ~FastPimpl() noexcept {
    validate<sizeof(T), alignof(T)>();
    Ptr()->~T();
  }

  T* operator->() noexcept { return Ptr(); }
  const T* operator->() const noexcept { return Ptr(); }

  T& operator*() noexcept { return *Ptr(); }
  const T& operator*() const noexcept { return *Ptr(); }

 private:
  template <std::size_t ActualSize, std::size_t ActualAlignment>
  static void validate() noexcept {
    static_assert(Size == ActualSize, "Size and sizeof(T) mismatch");
    static_assert(Alignment == ActualAlignment,
                  "Alignment and alignof(T) mismatch");
  }

  T* Ptr() noexcept { return reinterpret_cast<T*>(&data_); }
  const T* Ptr() const noexcept { return reinterpret_cast<const T*>(&data_); }

  std::aligned_storage_t<Size, Alignment> data_;
};

}  // namespace utils
}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_UTILS_FAST_PIMPL_H_
