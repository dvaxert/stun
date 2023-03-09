#ifndef STUN_LIB_INCLUDE_STUN_UTILS_DEFER_CALL_H_
#define STUN_LIB_INCLUDE_STUN_UTILS_DEFER_CALL_H_

#include <functional>

/**
 * @brief The defer_call shortcut macro
 * @note Call options:
 *  DEFER_CALL(<function>);
 *  DEFER_CALL(<function>, <arguments>);
 *  DEFER_CALL(<method>, <object>, <arguments>);
 */
#define DEFER_CALL(...) stun::utils::DeferCall MAKE_DEFER_CALL_NAME()(__VA_ARGS__);

/**
 * @brief Macros for automatic generation of names for the DEFER_CALL macro
 */
#define MAKE_DEFER_CALL_NAME() CONCAT(defer_call_, __LINE__)
#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a ## b

namespace stun {
namespace utils {
    
class DeferCall {
 public:
  template<class Function, class... Args>
  DeferCall(Function func, Args... args) {
      func_ = std::bind(func, std::forward<Args>(args)...);
  }
  
  template<class Method, class Object, class... Args>
  DeferCall(Method method, Object* object, Args... args) {
      func_ = std::bind(method, object, std::forward<Args>(args)...);
  }
  
  template<class Function>
  DeferCall(Function func) : func_(func) {
  
  }
  
  ~DeferCall() {
      func_();
  }
  
 private:
  std::function<void()> func_;
};

} // namespace utils
} // namespace stun

#endif // STUN_LIB_INCLUDE_STUN_UTILS_DEFER_CALL_H_
