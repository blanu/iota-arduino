#ifndef _NOUN_H_
#define _NOUN_H_

#include <Arduino.h>
#include <map>
#include <functional>
#include <vector>
#include <tuple>
#include <optional>

#include "error.h"
#include "storage.h"
#include "ReliableConnection.h"

using Symbol = int;
using Specialization3 = std::tuple<Symbol, Symbol, Symbol>;
using Specialization5 = std::tuple<Symbol, Symbol, Symbol, Symbol, Symbol>;
using Monad = std::function<Storage(Storage)>;
using Dyad = std::function<Storage(Storage,Storage)>;
using Triad = std::function<Storage(Storage,Storage,Storage)>;
using MonadicAdverb = std::function<Storage(Storage,Storage)>;
using DyadicAdverb = std::function<Storage(Storage,Storage,Storage)>;

class Noun
{
  public:
    static void initialize();

    static Storage dispatchMonad(Storage i, Storage f);
    static Storage dispatchDyad(Storage i, Storage f, Storage x);
    static Storage dispatchTriad(Storage i, Storage f, Storage x, Storage y);
    static Storage dispatchMonadicAdverb(Storage i, Storage f, Storage g);
    static Storage dispatchDyadicAdverb(Storage i, Storage f, Storage g, Storage x);

    static void registerMonad(Symbol it, Symbol io, Symbol f, Storage (*m)(Storage));
    static void registerDyad(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*d)(Storage, Storage));
    static void registerTriad(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*t)(Storage, Storage, Storage));
    static void registerMonadicAdverb(Symbol it, Symbol io, Symbol f, Storage (*a)(Storage, Storage));
    static void registerDyadicAdverb(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*a)(Storage, Storage, Storage));

    // General serialization
    static maybe<Storage> from_bytes(bytes data);
    static bytes to_bytes(Storage storage);
    static maybe<Storage> from_conn(ReliableConnection conn);
    static void to_conn(ReliableConnection conn, Storage x);

    private:
      static std::map<Specialization3, Monad> monads;
      static std::map<Specialization5, Dyad> dyads;
      static std::map<Specialization5, Triad> triads;
      static std::map<Specialization3, MonadicAdverb> monadicAdverbs;
      static std::map<Specialization5, DyadicAdverb> dyadicAdverbs;
};

class Integer
{
  public:
    // Initialize dispatch table
    static void initialize();

    // Serialization
    static maybe<bytes> to_bytes(Storage i);
    static maybe<Storage> from_bytes(bytes bs, int t);
    static void to_conn(ReliableConnection conn, Storage i);
    static maybe<Storage> from_conn(ReliableConnection conn, int t);
};

class Real
{
  public:
    // Initialize dispatch table
    static void initialize();

    // Serialization
    static maybe<bytes> to_bytes(Storage i);
    static maybe<Storage> from_bytes(bytes bs, int t);
    static void to_conn(ReliableConnection conn, Storage i);
    static maybe<Storage> from_conn(ReliableConnection conn, int t);
};

class List
{
  public:
    // Initialize dispatch table
    static void initialize();

    // Serialization
    static maybe<bytes> to_bytes(Storage i);
    static maybe<Storage> from_bytes(bytes bs, int t);
    static void to_conn(ReliableConnection conn, Storage i);
    static maybe<Storage> from_conn(ReliableConnection conn, int t);
};

class Character
{
  public:
    // Initialize dispatch table
    static void initialize();

    // Serialization
    static maybe<bytes> to_bytes(Storage i);
    static maybe<Storage> from_bytes(bytes bs, int t);
    static void to_conn(ReliableConnection conn, Storage i);
    static maybe<Storage> from_conn(ReliableConnection conn, int t);
};

class IotaString
{
  public:
    // Initialize dispatch table
    static void initialize();

    // Serialization
    static maybe<bytes> to_bytes(Storage i);
    static maybe<Storage> from_bytes(bytes bs, int t);
    static void to_conn(ReliableConnection conn, Storage i);
    static maybe<Storage> from_conn(ReliableConnection conn, int t);
};

// Note: MixedArray is defined in noun.h because it needs access to the Noun serialization API
class MixedArray
{
  public:
    static maybe<Storage> from_bytes(bytes data, int o);
    static maybe<bytes> to_bytes(Storage storage);

    static maybe<Storage> from_conn(ReliableConnection conn, int objectType);
    static void to_conn(ReliableConnection conn, Storage x);

    static Storage make(mixed x, int o);
};

#endif