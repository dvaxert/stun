#ifndef STUN_LIB_INCLUDE_STUN_SERALIZER_H_
#define STUN_LIB_INCLUDE_STUN_SERALIZER_H_

#include <array>
#include <memory>

#include "stun/interface/iserializer.h"
#include "stun/utils/fast_pimpl.h"

namespace stun {

class Serializer final : public ISerializer {
 public:
  Serializer();
  ~Serializer() noexcept override;

  std::vector<uint8_t> Data() const override;
  void AlignData(size_t align) override;

  ISerializer& Serialize(char value) override;
  ISerializer& Serialize(uint8_t value) override;
  ISerializer& Serialize(uint16_t value) override;
  ISerializer& Serialize(uint32_t value) override;
  ISerializer& Serialize(uint64_t value) override;

 private:
  class Impl;
  utils::FastPimpl<Impl, 1024, 8> impl_;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_SERALIZER_H_
