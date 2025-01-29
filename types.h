#ifndef _TYPES_H_
#define _TYPES_H

#include <Arduino.h>
#include <vector>
#include <variant>
#include <optional>
#include <map>

using bytes = std::vector<byte>;
using ints = std::vector<int>;
using floats = std::vector<float>;

using varint = std::variant<int, ints>;

template <typename T>
using maybe = std::optional<T>;

using floating = std::variant<float, double>;

#endif