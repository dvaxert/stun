#ifndef STUN_LIB_INCLUDE_STUN_INTERFACE_IATTRIBUTE_H_
#define STUN_LIB_INCLUDE_STUN_INTERFACE_IATTRIBUTE_H_

#include <cstdint>
#include <vector>

#include "stun/deserializer.h"
#include "stun/enums/attribute_type.h"
#include "stun/serializer.h"

namespace stun {

/**
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Type                  |            Length             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             Data...
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

class IAttribute {
 public:
  virtual ~IAttribute() = default;

  virtual AttributeType Type() const = 0;
  uint16_t Length() { return DataLength() + 4; }

  virtual void Serialize(Serializer& s) const = 0;
  virtual void Deserialize(Deserializer& d) = 0;

  virtual std::string ToString() const = 0;

 protected:
  virtual uint16_t DataLength() const = 0;
};

}  // namespace stun

#endif  // STUN_LIB_INCLUDE_STUN_INTERFACE_IATTRIBUTE_H_
