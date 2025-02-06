#ifndef _NOUN_H_
#define _NOUN_H_

#include <Arduino.h>
#include <map>
#include <functional>
#include <vector>
#include <tuple>
#include <optional>
#include <numeric>

#include "error.h"
#include "storage.h"
#include "ReliableConnection.h"

// Monads
Storage atom(Storage i);
Storage ichar(Storage i);
Storage enclose(Storage i);
Storage enumerate(Storage i);
Storage first(Storage i);
Storage floor(Storage i);
Storage format(Storage i);
Storage gradeDown(Storage i);
Storage negate(Storage i);
Storage reciprocal(Storage i);
Storage shape(Storage i);
Storage size(Storage i);
Storage transpose(Storage i);
Storage unique(Storage i);
Storage inot(Storage i);

// Extension Monads

Storage evaluate(Storage i);
Storage erase(Storage i);
Storage truth(Storage i);

// Dyads
Storage divide(Storage i, Storage x);
Storage less(Storage i, Storage x);
Storage match(Storage i, Storage x);
Storage more(Storage i, Storage x);

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

    // Monads
    static Storage enclose_impl(Storage i);
    static Storage shape_scalar(Storage i);

    // Extension Monads
    static Storage evaluate_expression(Storage e);

    // Convenience Monads
    static Storage true_impl(Storage i);
    static Storage false_impl(Storage i);
    static Storage identity(Storage i);

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

    // Monads
    static Storage char_impl(Storage i);    
    static Storage enclose_impl(Storage i);    
    static Storage enumerate_impl(Storage i);
    static Storage floor_impl(Storage i);
    static Storage negate_impl(Storage i);    
    static Storage not_impl(Storage i);
    static Storage reciprocal_impl(Storage i);    
    static Storage reverse_impl(Storage i);    
    static Storage size_impl(Storage i);    

    // Dyads
    static Storage cut_integers(Storage i, Storage x);
    // static Storage cut_reals(Storage i, Storage x);
    // static Storage cut_mixed(Storage i, Storage x);
    static Storage divide_integer(Storage i, Storage x);
    static Storage divide_real(Storage i, Storage x);
    static Storage divide_integers(Storage i, Storage x);
    static Storage divide_reals(Storage i, Storage x);
    static Storage divide_mixed(Storage i, Storage x);
    static Storage less_integer(Storage i, Storage x);
    static Storage less_real(Storage i, Storage x);
    static Storage less_list(Storage i, Storage x);
    static Storage more_integer(Storage i, Storage x);
    static Storage more_real(Storage i, Storage x);
    static Storage more_list(Storage i, Storage x);

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

    static Storage enclose_impl(Storage i);    
    static Storage floor_impl(Storage i);
    static Storage negate_impl(Storage i);    
    static Storage not_impl(Storage i);
    static Storage reciprocal_impl(Storage i);    
    static Storage reverse_impl(Storage i);    
    static Storage size_impl(Storage i);    

    // Dyads
    static Storage divide_integer(Storage i, Storage x);
    static Storage divide_real(Storage i, Storage x);
    static Storage divide_integers(Storage i, Storage x);
    static Storage divide_reals(Storage i, Storage x);
    static Storage divide_mixed(Storage i, Storage x);
    static Storage less_integer(Storage i, Storage x);
    static Storage less_real(Storage i, Storage x);
    static Storage less_list(Storage i, Storage x);
    static Storage more_integer(Storage i, Storage x);
    static Storage more_real(Storage i, Storage x);
    static Storage more_list(Storage i, Storage x);

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

    // Monads
    static Storage atom_impl(Storage i);    
    static Storage char_impl(Storage i);    
    static Storage enclose_impl(Storage i);    
    static Storage first_impl(Storage i);
    static Storage floor_impl(Storage i);
    static Storage gradeDown_impl(Storage i);
    static Storage gradeUp_impl(Storage i);
    static Storage negate_impl(Storage i);    
    static Storage not_impl(Storage i);
    static Storage reciprocal_impl(Storage i);    
    static Storage reverse_impl(Storage i);    
    static Storage shape_impl(Storage i);    
    static Storage size_impl(Storage i);    
    static Storage transpose_impl(Storage i);    
    static Storage unique_impl(Storage i);    

    // Dyads
    static Storage divide_integer(Storage i, Storage x);
    static Storage divide_real(Storage i, Storage x);
    static Storage divide_integers(Storage i, Storage x);
    static Storage divide_reals(Storage i, Storage x);
    static Storage divide_mixed(Storage i, Storage x);
    static Storage less_integer(Storage i, Storage x);
    static Storage less_real(Storage i, Storage x);
    static Storage less_list(Storage i, Storage x);
    static Storage more_integer(Storage i, Storage x);
    static Storage more_real(Storage i, Storage x);
    static Storage more_list(Storage i, Storage x);

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

    // Monads
    static Storage enclose_impl(Storage i);    
    static Storage reverse_impl(Storage i);    
    static Storage size_impl(Storage i);    

    // Dyads
    static Storage less_character(Storage i, Storage x);
    static Storage more_character(Storage i, Storage x);

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

    // Monads
    static Storage atom_impl(Storage i);    
    static Storage enclose_impl(Storage i);    
    static Storage first_impl(Storage i);
    static Storage gradeDown_impl(Storage i);
    static Storage gradeUp_impl(Storage i);
    static Storage reverse_impl(Storage i);    
    static Storage size_impl(Storage i);    

    // Dyads
    static Storage less_string(Storage i, Storage x);
    static Storage more_string(Storage i, Storage x);

    // Serialization
    static maybe<bytes> to_bytes(Storage i);
    static maybe<Storage> from_bytes(bytes bs, int t);
    static void to_conn(ReliableConnection conn, Storage i);
    static maybe<Storage> from_conn(ReliableConnection conn, int t);
};

class Expression
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage truth(Storage i);
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