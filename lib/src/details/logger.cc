#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "stun/details/logger.h"

namespace stun {
namespace details {

spdlog::level::level_enum ToSpdlogLevel(const LogLevel level) {
  switch (level) {
    case LogLevel::Trace:
      return spdlog::level::trace;

    case LogLevel::Debug:
      return spdlog::level::debug;

    case LogLevel::Warning:
      return spdlog::level::warn;

    case LogLevel::Error:
      return spdlog::level::err;

    case LogLevel::Fatal:
      return spdlog::level::critical;

    default:
      return spdlog::level::info;
  }
}

//------------------------------------------------------------------------------

class Logger::Pimpl {
 public:
  Pimpl() : logger_(spdlog::stdout_color_mt("console")) {
    logger_->set_pattern("[%^%L%$] %v");
    SetLevel(LogLevel::Info);
  }

  void SetLevel(LogLevel level) { logger_->set_level(ToSpdlogLevel(level)); }

  void Log(LogLevel level, const std::string_view message) {
    logger_->log(ToSpdlogLevel(level), message);
  }

 private:
  std::shared_ptr<spdlog::logger> logger_;
};

//------------------------------------------------------------------------------

Logger::Logger() : pimpl_() {}

//------------------------------------------------------------------------------

Logger::~Logger() {}

//------------------------------------------------------------------------------

void Logger::Trace(const std::string_view message) {
  pimpl_->Log(LogLevel::Trace, message);
}

//------------------------------------------------------------------------------

void Logger::Debug(const std::string_view message) {
  pimpl_->Log(LogLevel::Debug, message);
}

//------------------------------------------------------------------------------

void Logger::Info(const std::string_view message) {
  pimpl_->Log(LogLevel::Info, message);
}

//------------------------------------------------------------------------------

void Logger::Warning(const std::string_view message) {
  pimpl_->Log(LogLevel::Warning, message);
}

//------------------------------------------------------------------------------

void Logger::Error(const std::string_view message) {
  pimpl_->Log(LogLevel::Error, message);
}

//------------------------------------------------------------------------------

void Logger::Fatal(const std::string_view message) {
  pimpl_->Log(LogLevel::Fatal, message);
}

//------------------------------------------------------------------------------

void Logger::SetLevel(const LogLevel level) { pimpl_->SetLevel(level); }

}  // namespace details
}  // namespace stun
