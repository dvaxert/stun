#ifndef STUN_LIB_INCLUDE_STUN_ATTRIBUTES_ERROR_CODE_H_
#define STUN_LIB_INCLUDE_STUN_ATTRIBUTES_ERROR_CODE_H_

#include <string>

#include "stun/interface/iattribute.h"

namespace stun {

class ErrorCode final : public IAttribute {
 public:
  enum class PredefinedError : uint32_t {
    BadRequest = 400,
    Unauthorized = 401,
    UnknownAttribute = 420,
    StaleCredentials = 430,
    IntegrityCheckFailure = 431,
    MissingUsername = 432,
    UseTLS = 433,
    ServerError = 500,
    GlobalFailure = 600
  };

  explicit ErrorCode(PredefinedError error);
  ErrorCode(uint32_t code, std::string message);
  ~ErrorCode() override = default;

  AttributeType Type() const override;

  uint32_t Code() const;
  std::string Message() const;

  void Serialize(Serializer& s) const override;

 private:
  size_t AlignSize() const;
  uint16_t DataLength() const override;

  uint32_t code_;
  std::string message_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_ATTRIBUTES_ERROR_CODE_H_
