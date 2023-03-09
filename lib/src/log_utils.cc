#include "stun/details/logger.h"

namespace stun {

std::shared_ptr<stun::ILogger> LoggerSingleton() {
  static auto logger = std::make_shared<stun::details::Logger>();
  return logger;
}

}  // namespace stun
