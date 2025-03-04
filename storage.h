#ifndef __STORAGE_H_
#define __STORAGE_H_

#include <Arduino.h>
#include <tuple>
#include <vector>
#include <variant>
#include <optional>

#include "ReliableConnection.h"
#include "types.h"

// StorageType
class StorageType
{
  public:
    static const int WORD = 0;
    static const int FLOAT = 1;
    static const int WORD_ARRAY = 2;  // all integers
    static const int FLOAT_ARRAY = 3; // all floats
    static const int MIXED_ARRAY = 4; // array of storage types
};

class NounType
{
  public:
    static const int INTEGER = 0;
    static const int REAL = 1;
    static const int CHARACTER = 2;
    static const int STRING = 3;
    static const int LIST = 4;
    static const int DICTIONARY = 5;
    static const int BUILTIN_SYMBOL = 6;
    static const int BUILTIN_MONAD = 7;
    static const int BUILTIN_DYAD = 8;
    static const int BUILTIN_TRIAD = 9;
    static const int MONADIC_ADVERB = 10;
    static const int DYADIC_ADVERB = 11;
    static const int USER_SYMBOL = 12;
    static const int USER_MONAD = 13;
    static const int USER_DYAD = 14;
    static const int USER_TRIAD = 15;
    static const int ERROR = 16;
    static const int EXPRESSION = 17;
    static const int TYPE = 18;
    static const int CONDITIONAL = 19;
    static const int QUOTED_SYMBOL = 20;
};

class SymbolType
{
  public:
    static const int i = 0;
    static const int x = 1;
    static const int y = 2;
    static const int z = 3;
    static const int f = 4;
    static const int undefined = 5; // If adding new symbols, undefined must also be the last symbol as it marks the end of the list of builtin symbols.
};

class Storage;

using mixed = std::vector<Storage>;
using I = std::variant<int, float, ints, floats, mixed>;

class Storage
{
  public:
    int o;
    int t;
    I i;

    static Storage identity(Storage i);

    Storage(int o, int t, I x) : o(o), t(t), i(x) {}

    int truth();

    bool operator==(const Storage& other) const;
};

namespace std
{
  template<>
  struct hash<Storage>
  {
      std::size_t operator()(const Storage& i) const
      {
        std::size_t ht = std::hash<int>()(i.t);
        std::size_t ho = std::hash<int>()(i.o);
        std::size_t hi = 0;

        if(std::holds_alternative<int>(i.i))
        {
          int ii = std::get<int>(i.i);
          hi = std::hash<int>()(ii);
        }
        else if(std::holds_alternative<float>(i.i))
        {
          float ii = std::get<float>(i.i);
          hi = std::hash<float>()(ii);
        }
        else if(std::holds_alternative<ints>(i.i))
        {
          ints ii = std::get<ints>(i.i);
          hi = ii.size();
          for(int y : ii)
          {
            hi ^= std::hash<int>()(y) + 0x9e3779b9 + (hi << 6) + (hi >> 2);
          }
        }
        else if(std::holds_alternative<floats>(i.i))
        {
          floats ii = std::get<floats>(i.i);
          hi = ii.size();
          for(float y : ii)
          {
            hi ^= std::hash<float>()(y) + 0x9e3779b9 + (hi << 6) + (hi >> 2);
          }
        }
        else if(std::holds_alternative<mixed>(i.i))
        {
          mixed ii = std::get<mixed>(i.i);
          for(Storage y : ii)
          {
            hi ^= std::hash<Storage>()(y) + 0x9e3779b9 + (hi << 6) + (hi >> 2);
          }
        }

        return ht ^ (ho << 1) ^ (hi << 2);
      }
  };
}

class Word
{
  public:
    static maybe<Storage> from_bytes(bytes data, int o);
    static bytes to_bytes(Storage storage);

    static maybe<Storage> from_conn(ReliableConnection conn, int objectType);
    static void to_conn(ReliableConnection conn, Storage i);

    static Storage make(int x, int o = NounType::INTEGER);
};

class Float
{
  public:
    static constexpr float tolerance = 1e-14f; // for match
    static constexpr float precision = 6; // for format

    static maybe<Storage> from_bytes(bytes data, int o);
    static maybe<bytes> to_bytes(Storage storage);

    static maybe<Storage> from_conn(ReliableConnection conn, int objectType);
    static void to_conn(ReliableConnection conn, Storage x);

    static Storage make(float x, int o = NounType::REAL);
};

class WordArray
{
  public:
    static Storage nil();

    static maybe<Storage> from_bytes(bytes data, int o);
    static bytes to_bytes(Storage storage);

    static maybe<Storage> from_conn(ReliableConnection conn, int objectType);
    static void to_conn(ReliableConnection conn, Storage i);

    static Storage make(ints x, int o = NounType::LIST);
};

class FloatArray
{
  public:
    static maybe<Storage> from_bytes(bytes data, int o);
    static bytes to_bytes(Storage storage);

    static maybe<Storage> from_conn(ReliableConnection conn, int objectType);
    static void to_conn(ReliableConnection conn, Storage i);

    static Storage make(floats x, int o = NounType::LIST);
};

// Note: MixedArray is static Storageined in noun.h because it needs access to the Noun serialization API

#endif