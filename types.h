#ifndef _TYPES_H_
#define _TYPES_H_

#include <Arduino.h>
#include <vector>
#include <variant>
#include <optional>
#include <map>

using bytes = std::vector<byte>;
using ints = std::vector<int>;
using floats = std::vector<float>;

struct IntsHash
{
  std::size_t operator()(const std::vector<int>& integers) const
  {
    std::size_t hash = 0;
    std::hash<int> hasher;

    for (int integer : integers)
    {
      hash ^= hasher(integer) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }

    return hash;
  }
};

using varint = std::variant<int, ints>;

template <typename T>
using maybe = std::optional<T>;

using floating = std::variant<float, double>;

#endif