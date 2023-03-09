#ifndef STUN_LIB_INCLUDE_STUN_UTILS_CONDITION_VARIABLE_H_
#define STUN_LIB_INCLUDE_STUN_UTILS_CONDITION_VARIABLE_H_

#include <cstdint>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace stun {
namespace utils {

class ConditionVariable {
  public:
    ConditionVariable() = default;
    ~ConditionVariable() = default;

    bool Get() const;
    bool WaitFor(uint64_t timeout_ms);
    void Notify();
    void Reset();

    operator bool() const;

  private:
    std::condition_variable cv_;
    std::atomic_bool bool_;
    std::mutex mutex_;
};
    
} 
}

#endif // STUN_LIB_INCLUDE_STUN_UTILS_CONDITION_VARIABLE_H_
