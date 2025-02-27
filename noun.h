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
Storage reverse(Storage i);
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
Storage cut(Storage i, Storage x);
Storage divide(Storage i, Storage x);
Storage drop(Storage i, Storage x);
Storage equal(Storage i, Storage x);
Storage find(Storage i, Storage x);
Storage index(Storage i, Storage x);
Storage join(Storage i, Storage x);
Storage less(Storage i, Storage x);
Storage match(Storage i, Storage x);
Storage max(Storage i, Storage x);
Storage min(Storage i, Storage x);
Storage minus(Storage i, Storage x);
Storage more(Storage i, Storage x);
Storage plus(Storage i, Storage x);
Storage power(Storage i, Storage x);
Storage remainder(Storage i, Storage x);
Storage reshape(Storage i, Storage x);
Storage rotate(Storage i, Storage x);
Storage split(Storage i, Storage x);
Storage take(Storage i, Storage x);
Storage times(Storage i, Storage x);

// Monadic Adverbs
Storage converge(Storage i, Storage f);
Storage each(Storage i, Storage f);
Storage eachPair(Storage i, Storage f);
Storage over(Storage i, Storage f);
Storage scanConverging(Storage i, Storage f);
Storage scanOver(Storage i, Storage f);

// Dyadic Adverbs
Storage each2(Storage i, Storage f, Storage x);
Storage eachLeft(Storage i, Storage f, Storage x);
Storage eachRight(Storage i, Storage f, Storage x);
Storage overNeutral(Storage i, Storage f, Storage x);
Storage iterate(Storage i, Storage f, Storage x);
Storage scanIterating(Storage i, Storage f, Storage x);
Storage scanOverNeutral(Storage i, Storage f, Storage x);
Storage scanWhileOne(Storage i, Storage f, Storage x);
Storage whileOne(Storage i, Storage f, Storage x);

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
    static constexpr int maximumConvergeIterations = 1000;

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
    static Storage mix(Storage i);
    static Storage simplify(Storage i);

    static Storage true0();
    static Storage true1(Storage i);
    static Storage true2(Storage i, Storage x);
    static Storage false0();
    static Storage false1(Storage i);
    static Storage false2(Storage i, Storage x);
    static Storage identity1(Storage i);

    // Extension Dyads
    static Storage join_scalar(Storage i, Storage x);
    static Storage prepend(Storage i, Storage x);
    static Storage append(Storage i, Storage x);
    static Storage join_mixed(Storage i, Storage x);
    static Storage join_mix_left(Storage i, Storage x);
    static Storage join_mix_right(Storage i, Storage x);
    static Storage join_mix_enclose(Storage i, Storage x);
    static Storage join_enclose_mix(Storage i, Storage x);
    static Storage identity2(Storage i, Storage x);
    static Storage enclose2(Storage i, Storage x);

    // Monadic Adverbs
    static Storage converge_impl(Storage i, Storage f);
    static Storage scanConverging_impl(Storage i, Storage f);

    // Dyadic Adverbs
    // each2
    static Storage each2_impl(Storage i, Storage f, Storage x);
    static Storage eachLeft_impl(Storage i, Storage f, Storage x);
    static Storage eachRight_impl(Storage i, Storage f, Storage x);
    static Storage overNeutral_impl(Storage i, Storage f, Storage x);
    static Storage iterate_integer(Storage i, Storage f, Storage x);
    static Storage scanIterating_integer(Storage i, Storage f, Storage x);
    static Storage scanOverNeutral_impl(Storage i, Storage f, Storage x);
    static Storage scanWhileOne_impl(Storage i, Storage f, Storage g);
    static Storage whileOne_impl(Storage i, Storage f, Storage g);

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

    static Storage make(int i);
    static Storage zero();
    static Storage one();

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
    static Storage cut_reals(Storage i, Storage x);
    static Storage cut_mixed(Storage i, Storage x);
    static Storage divide_integer(Storage i, Storage x);
    static Storage divide_real(Storage i, Storage x);
    static Storage divide_integers(Storage i, Storage x);
    static Storage divide_reals(Storage i, Storage x);
    static Storage divide_mixed(Storage i, Storage x);
    static Storage equal_impl(Storage i, Storage x);
    static Storage integerDivide_impl(Storage i, Storage x);
    static Storage join_integer(Storage i, Storage x);
    static Storage prepend_to_integers(Storage i, Storage x);
    static Storage less_integer(Storage i, Storage x);
    static Storage less_real(Storage i, Storage x);
    static Storage less_list(Storage i, Storage x);
    static Storage match_impl(Storage i, Storage x);
    static Storage max_integer(Storage i, Storage x);
    static Storage max_real(Storage i, Storage x);
    static Storage max_list(Storage i, Storage x);
    static Storage min_integer(Storage i, Storage x);
    static Storage min_real(Storage i, Storage x);
    static Storage min_list(Storage i, Storage x);
    static Storage minus_integer(Storage i, Storage x);
    static Storage minus_real(Storage i, Storage x);
    static Storage minus_list(Storage i, Storage x);
    static Storage more_integer(Storage i, Storage x);
    static Storage more_real(Storage i, Storage x);
    static Storage more_list(Storage i, Storage x);
    static Storage plus_integer(Storage i, Storage x);
    static Storage plus_real(Storage i, Storage x);
    static Storage plus_list(Storage i, Storage x);
    static Storage power_integer(Storage i, Storage x);
    static Storage power_real(Storage i, Storage x);
    static Storage power_list(Storage i, Storage x);
    static Storage remainder_integer(Storage i, Storage x);
    static Storage remainder_integers(Storage i, Storage x);
    static Storage remainder_mixed(Storage i, Storage x);
    static Storage reshape_integer(Storage i, Storage x);
    static Storage reshape_integers(Storage i, Storage x);
    static Storage reshape_mixed(Storage i, Storage x);
    static Storage times_integer(Storage i, Storage x);
    static Storage times_real(Storage i, Storage x);
    static Storage times_list(Storage i, Storage x);

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

    static Storage make(float i);
    static Storage zero();
    static Storage one();

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
    static Storage join_real(Storage i, Storage x);
    static Storage prepend_to_reals(Storage i, Storage x);
    static Storage less_integer(Storage i, Storage x);
    static Storage less_real(Storage i, Storage x);
    static Storage less_list(Storage i, Storage x);
    static Storage match_impl(Storage i, Storage x);
    static Storage max_integer(Storage i, Storage x);
    static Storage max_real(Storage i, Storage x);
    static Storage max_list(Storage i, Storage x);
    static Storage min_integer(Storage i, Storage x);
    static Storage min_real(Storage i, Storage x);
    static Storage min_list(Storage i, Storage x);
    static Storage minus_integer(Storage i, Storage x);
    static Storage minus_real(Storage i, Storage x);
    static Storage minus_list(Storage i, Storage x);
    static Storage more_integer(Storage i, Storage x);
    static Storage more_real(Storage i, Storage x);
    static Storage more_list(Storage i, Storage x);
    static Storage plus_integer(Storage i, Storage x);
    static Storage plus_real(Storage i, Storage x);
    static Storage plus_list(Storage i, Storage x);
    static Storage power_integer(Storage i, Storage x);
    static Storage power_real(Storage i, Storage x);
    static Storage power_list(Storage i, Storage x);
    static Storage reshape_integer(Storage i, Storage x);
    static Storage reshape_integers(Storage i, Storage x);
    static Storage reshape_mixed(Storage i, Storage x);
    static Storage times_integer(Storage i, Storage x);
    static Storage times_real(Storage i, Storage x);
    static Storage times_list(Storage i, Storage x);

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
    static Storage cut_integer(Storage i, Storage x);
    static Storage cut_integers(Storage i, Storage x);
    static Storage divide_integer(Storage i, Storage x);
    static Storage divide_real(Storage i, Storage x);
    static Storage divide_integers(Storage i, Storage x);
    static Storage divide_reals(Storage i, Storage x);
    static Storage divide_mixed(Storage i, Storage x);
    static Storage drop_impl(Storage i, Storage x);
    static Storage equal_impl(Storage i, Storage x);
    static Storage find_impl(Storage i, Storage x);
    static Storage index_impl(Storage i, Storage x);

    // Join
    static Storage append_integer(Storage i, Storage x);
    static Storage append_real(Storage i, Storage x);
    static Storage prepend_integer(Storage i, Storage x);
    static Storage prepend_real(Storage i, Storage x);
    static Storage join_integers(Storage i, Storage x);
    static Storage join_integers_reals(Storage i, Storage x);
    static Storage join_reals(Storage i, Storage x);
    static Storage join_reals_integers(Storage i, Storage x);
    static Storage join_mixed(Storage i, Storage x);

    static Storage less_integer(Storage i, Storage x);
    static Storage less_real(Storage i, Storage x);
    static Storage less_integers(Storage i, Storage x);
    static Storage less_reals(Storage i, Storage x);
    static Storage less_mixed(Storage i, Storage x);
    static Storage match_impl(Storage i, Storage x);
    static Storage max_integer(Storage i, Storage x);
    static Storage max_real(Storage i, Storage x);
    static Storage max_integers(Storage i, Storage x);
    static Storage max_reals(Storage i, Storage x);
    static Storage max_mixed(Storage i, Storage x);
    static Storage min_integer(Storage i, Storage x);
    static Storage min_real(Storage i, Storage x);
    static Storage min_integers(Storage i, Storage x);
    static Storage min_reals(Storage i, Storage x);
    static Storage min_mixed(Storage i, Storage x);
    static Storage minus_integer(Storage i, Storage x);
    static Storage minus_real(Storage i, Storage x);
    static Storage minus_integers(Storage i, Storage x);
    static Storage minus_reals(Storage i, Storage x);
    static Storage minus_mixed(Storage i, Storage x);
    static Storage more_integer(Storage i, Storage x);
    static Storage more_real(Storage i, Storage x);
    static Storage more_integers(Storage i, Storage x);
    static Storage more_reals(Storage i, Storage x);
    static Storage more_mixed(Storage i, Storage x);
    static Storage plus_integer(Storage i, Storage x);
    static Storage plus_real(Storage i, Storage x);
    static Storage plus_integers(Storage i, Storage x);
    static Storage plus_reals(Storage i, Storage x);
    static Storage plus_mixed(Storage i, Storage x);
    static Storage power_integer(Storage i, Storage x);
    static Storage power_real(Storage i, Storage x);
    static Storage power_integers(Storage i, Storage x);
    static Storage power_reals(Storage i, Storage x);
    static Storage power_mixed(Storage i, Storage x);
    static Storage remainder_integer(Storage i, Storage x);
    static Storage remainder_integers(Storage i, Storage x);
    static Storage remainder_mixed(Storage i, Storage x);
    static Storage reshape_integer(Storage i, Storage x);
    static Storage reshape_integers(Storage i, Storage x);
    static Storage reshape_mixed(Storage i, Storage x);
    static Storage rotate_integer(Storage i, Storage x);
    static Storage split_integer(Storage i, Storage x);
    static Storage split_integers(Storage i, Storage x);
    static Storage take_integer(Storage i, Storage x);
    static Storage times_integer(Storage i, Storage x);
    static Storage times_real(Storage i, Storage x);
    static Storage times_integers(Storage i, Storage x);
    static Storage times_reals(Storage i, Storage x);
    static Storage times_mixed(Storage i, Storage x);

    // Monadic Adverbs
    static Storage each_integers(Storage i, Storage f);
    static Storage each_reals(Storage i, Storage f);
    static Storage each_mixed(Storage i, Storage f);
    static Storage eachPair_integers(Storage i, Storage f);
    static Storage eachPair_reals(Storage i, Storage f);
    static Storage eachPair_mixed(Storage i, Storage f);
    static Storage over_integers(Storage i, Storage f);
    static Storage over_reals(Storage i, Storage f);
    static Storage over_mixed(Storage i, Storage f);
    static Storage scanOver_integers(Storage i, Storage f);
    static Storage scanOver_reals(Storage i, Storage f);
    static Storage scanOver_mixed(Storage i, Storage f);

    // Dyadic Adverbs

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

    static Storage make(int i);

    // Monads
    static Storage enclose_impl(Storage i);    
    static Storage reverse_impl(Storage i);    
    static Storage size_impl(Storage i);    

    // Dyads
    // Join
    static Storage join_scalar(Storage i, Storage x);
    static Storage join_character(Storage i, Storage x);
    static Storage join_list(Storage i, Storage x);
    static Storage prepend_string(Storage i, Storage x);

    static Storage less_character(Storage i, Storage x);
    static Storage match_impl(Storage i, Storage x);
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

    static Storage make(ints i);
    static Storage makeEmpty();

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
    static Storage index_impl(Storage i, Storage x);
    
    // Join
    static Storage append_character(Storage i, Storage x);
    static Storage join_string(Storage i, Storage x);

    static Storage match_impl(Storage i, Storage x);
    static Storage more_string(Storage i, Storage x);

    static Storage split_integer(Storage i, Storage x);
    static Storage split_integers(Storage i, Storage x);
    static Storage take_integer(Storage i, Storage x);

    // Monadic Adverbs
    static Storage each_impl(Storage i, Storage f);
    static Storage eachPair_impl(Storage i, Storage f);
    static Storage over_impl(Storage i, Storage f);
    static Storage scanOver_impl(Storage i, Storage f);

    // Dyadic Adverbs

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

class Conditional
{
  public:
    // Initialize dispatch table
    static void initialize();

    static Storage make(mixed i);

    static Storage evaluate_impl(Storage i);
    static Storage truth_impl(Storage i);
};

// Note: MixedArray is defined in noun.h because it needs access to the Noun serialization API
class MixedArray
{
  public:
    static maybe<Storage> from_bytes(bytes data, int o);
    static maybe<bytes> to_bytes(Storage storage);

    static maybe<Storage> from_conn(ReliableConnection conn, int objectType);
    static void to_conn(ReliableConnection conn, Storage x);

    static Storage make(mixed x, int o = NounType::LIST);
};

#endif