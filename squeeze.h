#ifndef __SQUEEZE_H_
#define __SQUEEZE_H_

#include <Arduino.h>
#include <tuple>
#include <vector>

#include "ReliableConnection.h"
#include "types.h"

class Storage;

bytes squeeze_int(int value);
bytes squeeze_bigint(ints value);
bytes squeeze_varint(varint value);
std::tuple<varint, bytes> expand_int(bytes value);
varint expand_int_from_bytes(bytes bytes);
varint expand_conn(ReliableConnection);

bytes squeeze_floating(floating value);
maybe<floating> expand_floating(bytes value);
maybe<floating> expand_conn_floating(ReliableConnection conn);

bytes squeeze_ints(ints value);
std::tuple<ints, bytes> expand_ints(bytes value);

bytes squeeze_floats(floats value);
// std::tuple<floats, bytes> expand_floats(bytes value);

#endif