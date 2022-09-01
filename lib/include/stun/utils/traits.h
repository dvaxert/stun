#ifndef STUN_LIB_INCLUDE_STUN_UTILS_TRAITS_H_
#define STUN_LIB_INCLUDE_STUN_UTILS_TRAITS_H_

namespace stun {
namespace utils {

template <class T>
class has_begin {
 private:
  template <typename C>
  static constexpr bool test(
      typename std::enable_if<
          std::is_same<decltype(static_cast<typename C::const_iterator (C::*)()
                                                const>(&C::begin)),
                       typename C::const_iterator (C::*)() const>::value,
          void>::type*) {
    return true;
  }

  template <typename C>
  static constexpr bool test(...) {
    return false;
  }

 public:
  static constexpr bool value = test<T>(0);
};

//------------------------------------------------------------------------------

template <class T>
class has_end {
 private:
  template <typename C>
  static constexpr bool test(
      typename std::enable_if<
          std::is_same<decltype(static_cast<typename C::const_iterator (C::*)()
                                                const>(&C::end)),
                       typename C::const_iterator (C::*)() const>::value,
          void>::type*) {
    return true;
  }

  template <typename C>
  static constexpr bool test(...) {
    return false;
  }

 public:
  static constexpr bool value = test<T>(0);
};

//------------------------------------------------------------------------------

template <class T>
static constexpr auto has_begin_v = has_begin<T>::value;

//------------------------------------------------------------------------------

template <class T>
static constexpr auto has_end_v = has_end<T>::value;

//------------------------------------------------------------------------------

template <class T>
class is_iterable {
 public:
  static constexpr bool value = has_begin_v<T> && has_end_v<T>;
};

//------------------------------------------------------------------------------

template <class T>
static constexpr auto is_iterable_v = is_iterable<T>::value;

}  // namespace utils
}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_UTILS_TRAITS_H_
