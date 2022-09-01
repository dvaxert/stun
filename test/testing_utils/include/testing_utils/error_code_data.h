#ifndef STUN_TEST_ATTRIBUTES_TEST_INCLUDE_ERROR_CODE_DATA_H_
#define STUN_TEST_ATTRIBUTES_TEST_INCLUDE_ERROR_CODE_DATA_H_

#include <string>

namespace tests {

static const std::string BadRequestMsg =
    "The request was malformed.  The client should not "
    "retry the request without modification from the previous attempt.";

static const std::string UnauthorizedMsg =
    "The Binding Request did not contain a MESSAGE-INTEGRITY attribute.";

static const std::string UnknownAttributeMsg =
    "The server did not understand a mandatory attribute in the request.";

static const std::string StaleCredentialsMsg =
    "The Binding Request did contain a MESSAGE-INTEGRITY attribute, but "
    "it used a shared secret that has expired.The client should obtain a "
    "new shared secret and try again.";

static const std::string IntegrityCheckFailureMsg =
    "The Binding Request contained a MESSAGE-INTEGRITY attribute, but the HMAC "
    "failed verification.This could be a sign of a potential attack, or client "
    "implementation error.";

static const std::string MissingUsernameMsg =
    "The Binding Request contained a MESSAGE-INTEGRITY attribute, but not a "
    "USERNAME attribute.  Both must be present for integrity checks.";

static const std::string UseTLSMsg =
    "The Shared Secret request has to be sent over TLS, but was not received "
    "over TLS.";

static const std::string ServerErrorMsg =
    "The server has suffered a temporary error. The client should try again.";

static const std::string GlobalFailureMsg =
    "The server is refusing to fulfill the request. The client should not "
    "retry.";

static const auto BadRequestCode = uint32_t(400);
static const auto UnauthorizedCode = uint32_t(401);
static const auto UnknownAttributeCode = uint32_t(420);
static const auto StaleCredentialsCode = uint32_t(430);
static const auto IntegrityCheckFailureCode = uint32_t(431);
static const auto MissingUsernameCode = uint32_t(432);
static const auto UseTLSCode = uint32_t(433);
static const auto ServerErrorCode = uint32_t(500);
static const auto GlobalFailureCode = uint32_t(600);

}  // namespace tests

#endif  // STUN_TEST_ATTRIBUTES_TEST_INCLUDE_ERROR_CODE_DATA_H_
