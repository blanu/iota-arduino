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

    bool operator==(const Storage& other) const
    {
        return (o == other.o) && (t == other.t) && (i == other.i);
    }
};

// FIXME - implement general hash function for Storage
// struct StorageHash {
//     std::size_t operator()(const Storage& i) const
//     {
//         return std::hash<int>()(i.t) ^ (std::hash<int>()(i.o) ^ std::hash<I>()(i.i) << 1);
//     }
// };

class Word
{
  public:
    static maybe<Storage> from_bytes(bytes data, int o);
    static bytes to_bytes(Storage storage);

    static maybe<Storage> from_conn(ReliableConnection conn, int objectType);
    static void to_conn(ReliableConnection conn, Storage i);

    static Storage make(int x, int o);
};

class Float
{
  public:
    static constexpr float tolerance = 1e-14f;

    static maybe<Storage> from_bytes(bytes data, int o);
    static maybe<bytes> to_bytes(Storage storage);

    static maybe<Storage> from_conn(ReliableConnection conn, int objectType);
    static void to_conn(ReliableConnection conn, Storage x);

    static Storage make(float x, int o);
};

class WordArray
{
  public:
    static Storage nil();

    static maybe<Storage> from_bytes(bytes data, int o);
    static bytes to_bytes(Storage storage);

    static maybe<Storage> from_conn(ReliableConnection conn, int objectType);
    static void to_conn(ReliableConnection conn, Storage i);

    static Storage make(ints x, int o);
};

class FloatArray
{
  public:
    static maybe<Storage> from_bytes(bytes data, int o);
    static bytes to_bytes(Storage storage);

    static maybe<Storage> from_conn(ReliableConnection conn, int objectType);
    static void to_conn(ReliableConnection conn, Storage i);

    static Storage make(floats x, int o);
};

// Note: MixedArray is static Storageined in noun.h because it needs access to the Noun serialization API

#endif