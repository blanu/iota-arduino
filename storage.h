#ifndef __STORAGE_H_
#define __STORAGE_H_

#include <Arduino.h>
#include <tuple>
#include <vector>
#include <variant>
#include <optional>

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
using I = std::variant<int, float, std::vector<int>, std::vector<float>, std::vector<Storage>>;

class Storage
{
  public:
    int o;
    int t;
    I i;

    static std::optional<Storage> from_bytes(std::vector<byte> data);
    static std::vector<byte> to_bytes(Storage storage);

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
    static std::optional<Storage> from_bytes(std::vector<byte> data, int o);
    static std::vector<byte> to_bytes(Storage storage);
    static Storage make(int x, int o);
};

class Float
{
  public:
    static std::optional<Storage> from_bytes(std::vector<byte> data, int o);
    static std::vector<byte> to_bytes(Storage storage);
    static Storage make(float x, int o);
};

class WordArray
{
  public:
    static std::optional<Storage> from_bytes(std::vector<byte> data, int o);
    static std::vector<byte> to_bytes(Storage storage);
    static Storage make(std::vector<int> x, int o);
};

class FloatArray
{
  public:
    static std::optional<Storage> from_bytes(std::vector<byte> data, int o);
    static std::vector<byte> to_bytes(Storage storage);
    static Storage make(std::vector<float> x, int o);
};

class MixedArray
{
  public:
    static std::optional<Storage> from_bytes(std::vector<byte> data, int o);
    static std::vector<byte> to_bytes(Storage storage);
    static Storage make(std::vector<Storage> x, int o);
};

#endif