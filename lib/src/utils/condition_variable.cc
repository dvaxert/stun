#include "stun/utils/condition_variable.h"

#include <functional>

namespace stun {
namespace utils {

bool ConditionVariable::Get() const { return bool_.load(); }

ConditionVariable::operator bool() const { return Get(); }

bool ConditionVariable::WaitFor(uint64_t timeout_ms) {
    auto lock = std::unique_lock(mutex_);
    cv_.wait_for(lock, std::chrono::milliseconds(timeout_ms), std::bind(&ConditionVariable::Get, this));
    return Get();
}

void ConditionVariable::Notify() {
    bool_.store(true);
    cv_.notify_one();
}

void ConditionVariable::Reset() {
    bool_.store(false);
}

} // namespace utils
} // namespace stun