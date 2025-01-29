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
#define WORD 0
#define FLOAT 1
#define WORD_ARRAY 2 // all integers
#define FLOAT_ARRAY 3 // all floats
#define MIXED_ARRAY 4 // array of storage types

// NounType
#define INTEGER 0
#define REAL 1
#define CHARACTER 2
#define STRING 3
#define LIST 4
#define DICTIONARY 5
#define BUILTIN_SYMBOL 6
#define BUILTIN_MONAD 7
#define BUILTIN_DYAD 8
#define BUILTIN_TRIAD 9
#define MONADIC_ADVERB 10
#define DYADIC_ADVERB 11
#define USER_SYMBOL 12
#define USER_MONAD 13
#define USER_DYAD 14
#define USER_TRIAD 15
#define ERROR 16
#define EXPRESSION 17
#define TYPE 18
#define CONDITIONAL 19

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

    bool operator==(const Storage& other) const
    {
        return (o == other.o) && (t == other.t) && (i == other.i);
    }
};

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
    static maybe<Storage> from_bytes(bytes data, int o);
    static maybe<bytes> to_bytes(Storage storage);

    static maybe<Storage> from_conn(ReliableConnection conn, int objectType);
    static void to_conn(ReliableConnection conn, Storage x);

    static Storage make(float x, int o);
};

class WordArray
{
  public:
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

// Note: MixedArray is defined in noun.h because it needs access to the Noun serialization API

#endif