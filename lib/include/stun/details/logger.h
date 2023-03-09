#ifndef STUN_LIB_INCLUDE_STUN_DETAILS_LOGGER_H_
#define STUN_LIB_INCLUDE_STUN_DETAILS_LOGGER_H_

#include <fmt/format.h>

#include <string_view>

#include "stun/details/log_level.h"
#include "stun/interface/ilogger.h"
#include "stun/utils/defer_call.h"
#include "stun/utils/fast_pimpl.h"

namespace stun {
namespace details {

class Logger : public ILogger {
 public:
  Logger();
  ~Logger() override;

  void Trace(const std::string_view message) override;
  void Debug(const std::string_view message) override;
  void Info(const std::string_view message) override;
  void Warning(const std::string_view message) override;
  void Error(const std::string_view message) override;
  void Fatal(const std::string_view message) override;

  void SetLevel(const LogLevel level) override;

 private:
  class Pimpl;
  utils::FastPimpl<Pimpl, 16, 8> pimpl_;
};

}  // namespace details
}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_DETAILS_LOGGER_H_
