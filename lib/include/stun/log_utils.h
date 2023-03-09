#ifndef STUN_LIB_INCLUDE_STUN_LOG_UTILS_H_
#define STUN_LIB_INCLUDE_STUN_LOG_UTILS_H_

#include <fmt/format.h>

#include <boost/preprocessor.hpp>
#include <sstream>

#include "stun/details/log_level.h"
#include "stun/interface/ilogger.h"
#include "stun/utils/defer_call.h"

#ifndef STUN_DISABLE_LOG

/**
 * @brief Set the logging level
 * @param level { Trace, Debug, Info, Warning, Error, Fatal }
 */
#define SET_LOG_LEVEL(level) \
  stun::LoggerSingleton()->SetLevel(stun::details::LogLevel::level);

/**
 * @brief Sending a message
 * @param msg message
 */
#define LOG_TRACE(msg) stun::LoggerSingleton()->Trace(msg);
#define LOG_DEBUG(msg) stun::LoggerSingleton()->Debug(msg);
#define LOG_INFO(msg) stun::LoggerSingleton()->Info(msg);
#define LOG_WARNING(msg) stun::LoggerSingleton()->Warning(msg);
#define LOG_ERROR(msg) stun::LoggerSingleton()->Error(msg);
#define LOG_FATAL(msg) stun::LoggerSingleton()->Fatal(msg);

/**
 * @brief Notification of entering and exiting the function
 */
#define TRACE_LOG()                                          \
  stun::LoggerSingleton()->Trace(                            \
      fmt::format("enter {}()", GET_FUNCTION_NAME()));       \
  DEFER_CALL(&stun::ILogger::Trace, stun::LoggerSingleton(), \
             fmt::format("exit {}()", GET_FUNCTION_NAME()));

/**
 * @brief Message about entering and exiting a function with information about
 *        the arguments passed at the call
 */
#define TRACE_LOG_P(...)                                     \
  stun::LoggerSingleton()->Trace(                            \
      fmt::format("enter {}()", GET_FUNCTION_NAME()));       \
  LOG_PARAMS(__VA_ARGS__)                                    \
  DEFER_CALL(&stun::ILogger::Trace, stun::LoggerSingleton(), \
             fmt::format("exit {}()", GET_FUNCTION_NAME()));

#define GET_FUNCTION_NAME() __func__

/**
 * @brief Message displaying the arguments of the function call
 *
 * @warning The passed parameters must have the << operator to work with std
 * streams
 */
#define PRINT_PARAM(r, data, elem) data << "\t" #elem " = " << elem << "\n";
#define LOG_PARAMS(...)                                            \
  {                                                                \
    std::ostringstream tmp{};                                      \
    tmp << GET_FUNCTION_NAME() << " call arguments:\n";            \
    BOOST_PP_LIST_FOR_EACH(PRINT_PARAM, tmp,                       \
                           BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__)) \
    std::string res = tmp.str();                                   \
    res.pop_back();                                                \
    LOG_TRACE(res);                                                \
  }

namespace stun {
/**
 * @brief Singleton for a single logger for the entire application
 */
std::shared_ptr<stun::ILogger> LoggerSingleton();

}  // namespace stun

#else  // STUN_DISABLE_LOG

#define SET_LOG_LEVEL(...) void();
#define LOG_TRACE(...) void();
#define LOG_DEBUG(...) void();
#define LOG_INFO(...) void();
#define LOG_WARNING(...) void();
#define LOG_ERROR(...) void();
#define LOG_FATAL(...) void();
#define TRACE_LOG(...) void();
#define TRACE_LOG_P(...) void();
#define PRINT_PARAM(...) void();
#define LOG_PARAMS(...) void();
#define GET_FUNCTION_NAME() void();

#endif  // STUN_DISABLE_LOG

#endif  // STUN_LIB_INCLUDE_STUN_LOG_UTILS_H_
