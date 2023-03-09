#ifndef STUN_LIB_INCLUDE_STUN_INTERFACE_ILOGGER_H_
#define STUN_LIB_INCLUDE_STUN_INTERFACE_ILOGGER_H_

#include <string_view>

#include "stun/details/log_level.h"

namespace stun {

class ILogger {
 public:
  virtual ~ILogger() = default;

  virtual void Trace(const std::string_view message) = 0;
  virtual void Debug(const std::string_view message) = 0;
  virtual void Info(const std::string_view message) = 0;
  virtual void Warning(const std::string_view message) = 0;
  virtual void Error(const std::string_view message) = 0;
  virtual void Fatal(const std::string_view message) = 0;

  virtual void SetLevel(const stun::details::LogLevel level) = 0;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_INTERFACE_ILOGGER_H_
