#include <math.h>
#include <cmath>
#include <vector>
#include <variant>
#include <algorithm>
#include <unordered_set>

#include "noun.h"
#include "squeeze.h"
#include "symbols.h"
#include "error.h"
#include "debug.h"

// Verbs
// Monads
Storage atom(Storage i)  // @a
{
  return Noun::dispatchMonad(i, Word::make(Monads::atom, NounType::BUILTIN_MONAD));
}

Storage ichar(Storage i)  // :#a
{
  return Noun::dispatchMonad(i, Word::make(Monads::ichar, NounType::BUILTIN_MONAD));
}

Storage enclose(Storage i)  // ,a
{
  return Noun::dispatchMonad(i, Word::make(Monads::enclose, NounType::BUILTIN_MONAD));
}

Storage enumerate(Storage i)  // !a
{
  return Noun::dispatchMonad(i, Word::make(Monads::enumerate, NounType::BUILTIN_MONAD));
}

Storage first(Storage i)  // *a
{
  return Noun::dispatchMonad(i, Word::make(Monads::first, NounType::BUILTIN_MONAD));
}

Storage floor(Storage i)  // _a
{
  return Noun::dispatchMonad(i, Word::make(Monads::floor, NounType::BUILTIN_MONAD));
}

// FIXME - implement format
Storage format(Storage i)  // $a
{
  return Noun::dispatchMonad(i, Word::make(Monads::format, NounType::BUILTIN_MONAD));
}

Storage gradeDown(Storage i)  // >a
{
  return Noun::dispatchMonad(i, Word::make(Monads::gradeDown, NounType::BUILTIN_MONAD));
}

Storage gradeUp(Storage i)  // <a
{
  return Noun::dispatchMonad(i, Word::make(Monads::gradeUp, NounType::BUILTIN_MONAD));
}

Storage negate(Storage i) // -a
{
  return Noun::dispatchMonad(i, Word::make(Monads::negate, NounType::BUILTIN_MONAD));
}

Storage inot(Storage i)  // ~a
{
  return Noun::dispatchMonad(i, Word::make(Monads::inot, NounType::BUILTIN_MONAD));
}

Storage reciprocal(Storage i) // %a
{
  return Noun::dispatchMonad(i, Word::make(Monads::reciprocal, NounType::BUILTIN_MONAD));
}

Storage shape(Storage i) // ^a
{
  return Noun::dispatchMonad(i, Word::make(Monads::shape, NounType::BUILTIN_MONAD));
}

Storage size(Storage i) // #a
{
  return Noun::dispatchMonad(i, Word::make(Monads::size, NounType::BUILTIN_MONAD));
}

Storage transpose(Storage i) // +a
{
  return Noun::dispatchMonad(i, Word::make(Monads::transpose, NounType::BUILTIN_MONAD));
}

Storage unique(Storage i) // ?a
{
  return Noun::dispatchMonad(i, Word::make(Monads::unique, NounType::BUILTIN_MONAD));
}

// Extension Monads
Storage evaluate(Storage i)
{
  return Noun::dispatchMonad(i, Word::make(Monads::evaluate, NounType::BUILTIN_MONAD));
}

Storage erase(Storage i)
{
  return Noun::dispatchMonad(i, Word::make(Monads::erase, NounType::BUILTIN_MONAD));
}

Storage truth(Storage i)
{
  return Noun::dispatchMonad(i, Word::make(Monads::truth, NounType::BUILTIN_MONAD));
}

// Dyads
Storage cut(Storage i, Storage x) // a:_b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::cut, NounType::BUILTIN_DYAD), x);
}

Storage divide(Storage i, Storage x) // a%b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::divide, NounType::BUILTIN_DYAD), x);
}

Storage drop(Storage i, Storage x) // a_b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::drop, NounType::BUILTIN_DYAD), x);
}

Storage equal(Storage i, Storage x) // a=b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::equal, NounType::BUILTIN_DYAD), x);
}

Storage find(Storage i, Storage x) // a?b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::find, NounType::BUILTIN_DYAD), x);
}

Storage index(Storage i, Storage x) // a@b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::index, NounType::BUILTIN_DYAD), x);
}

Storage integerDivide(Storage i, Storage x) // a%b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::integerDivide, NounType::BUILTIN_DYAD), x);
}

Storage join(Storage i, Storage x) // a,b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::join, NounType::BUILTIN_DYAD), x);
}

Storage less(Storage i, Storage x) // a<b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::less, NounType::BUILTIN_DYAD), x);
}

Storage match(Storage i, Storage x) // a~b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::match, NounType::BUILTIN_DYAD), x);
}

Storage max(Storage i, Storage x) // a|b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::max, NounType::BUILTIN_DYAD), x);
}

Storage min(Storage i, Storage x) // a&b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::min, NounType::BUILTIN_DYAD), x);
}

Storage minus(Storage i, Storage x) // a-b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::minus, NounType::BUILTIN_DYAD), x);
}

Storage more(Storage i, Storage x) // a>b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::more, NounType::BUILTIN_DYAD), x);
}

Storage plus(Storage i, Storage x) // a+b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::plus, NounType::BUILTIN_DYAD), x);
}

Storage power(Storage i, Storage x) // a^b
{
  return Noun::dispatchDyad(i, Word::make(Dyads::power, NounType::BUILTIN_DYAD), x);
}

std::map<Specialization3, Monad> Noun::monads;
std::map<Specialization5, Dyad> Noun::dyads;
std::map<Specialization5, Triad> Noun::triads;
std::map<Specialization3, MonadicAdverb> Noun::monadicAdverbs;
std::map<Specialization5, DyadicAdverb> Noun::dyadicAdverbs;

void Noun::initialize() {
  Integer::initialize();
  Real::initialize();
  List::initialize();
  Character::initialize();
  IotaString::initialize();
  Expression::initialize();
}

// Dispatch
Storage Noun::dispatchMonad(Storage i, Storage f) {
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization3 specialization = Specialization3(i.t, i.o, fi);
  if (monads.find(specialization) == monads.end()) {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  Monad verb = monads[specialization];
  return verb(i);
}

Storage Noun::dispatchDyad(Storage i, Storage f, Storage x) {
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (x.o == NounType::ERROR) {
    return x;
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (dyads.find(specialization) == dyads.end()) {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  Dyad verb = dyads[specialization];
  return verb(i, x);
}

Storage Noun::dispatchTriad(Storage i, Storage f, Storage x, Storage y) {
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (x.o == NounType::ERROR) {
    return x;
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (triads.find(specialization) == triads.end()) {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  Triad verb = triads[specialization];
  return verb(i, x, y);
}

Storage Noun::dispatchMonadicAdverb(Storage i, Storage f, Storage g) {
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization3 specialization = Specialization3(i.t, i.o, fi);
  if (monadicAdverbs.find(specialization) == monadicAdverbs.end()) {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  MonadicAdverb adverb = monadicAdverbs[specialization];
  return adverb(i, g);
}

Storage Noun::dispatchDyadicAdverb(Storage i, Storage f, Storage g, Storage x) {
  if (i.o == NounType::ERROR) {
    return i;
  }

  if (x.o == NounType::ERROR) {
    return x;
  }

  if (f.t != StorageType::WORD) {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (dyadicAdverbs.find(specialization) == dyadicAdverbs.end()) {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  DyadicAdverb adverb = dyadicAdverbs[specialization];
  return adverb(i, g, x);
}

// Registration

void Noun::registerMonad(Symbol it, Symbol io, Symbol f, Storage (*m)(Storage)) {
  Noun::monads[Specialization3(it, io, f)] = m;
}

void Noun::registerDyad(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*d)(Storage, Storage)) {
  Noun::dyads[Specialization5(it, io, f, xt, xo)] = d;
}

void Noun::registerTriad(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*t)(Storage, Storage, Storage)) {
  Noun::triads[Specialization5(it, io, f, xt, xo)] = t;
}

void Noun::registerMonadicAdverb(Symbol it, Symbol io, Symbol f, Storage (*a)(Storage, Storage)) {
  Noun::monadicAdverbs[Specialization3(it, io, f)] = a;
}

void Noun::registerDyadicAdverb(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*a)(Storage, Storage, Storage)) {
  Noun::dyadicAdverbs[Specialization5(it, io, f, xt, xo)] = a;
}

Storage Noun::true0() {
  return Word::make(1, NounType::INTEGER);
}

Storage Noun::true1(Storage i) {
  return Word::make(1, NounType::INTEGER);
}

Storage Noun::true2(Storage i, Storage x) {
  return Word::make(1, NounType::INTEGER);
}

Storage Noun::false0() {
  return Word::make(0, NounType::INTEGER);
}

Storage Noun::false1(Storage i) {
  return Word::make(0, NounType::INTEGER);
}

Storage Noun::false2(Storage i, Storage x) {
  return Word::make(0, NounType::INTEGER);
}

Storage Noun::identity(Storage i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);
  }

  return i;
}

// Extension Monads - Implementations
Storage Noun::evaluate_expression(Storage e) {
  if (std::holds_alternative<mixed>(e.i)) {
    mixed items = std::get<mixed>(e.i);

    if (items.empty()) {
      return e;
    }

    Storage i = items[0];

    if (items.size() == 1) {
      return i;
    }

    Storage f = items[1];

    mixed rest(items.begin() + 2, items.end());

    switch (f.o)
    {
      case NounType::BUILTIN_MONAD:
      {
        Storage result = Noun::dispatchMonad(i, f);
        if (rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          return result;
        }
      }

      case NounType::BUILTIN_DYAD:
      {
        Storage x = items[2];
        rest = mixed(items.begin() + 3, items.end());

        Storage result = Noun::dispatchDyad(i, f, x);
        if (rest.empty())
        {
          return result;
        }
        else
        {
          rest.insert(rest.begin(), result);

          Storage next_e = MixedArray::make(rest, NounType::EXPRESSION);
          result = evaluate_expression(next_e);

          return result;
        }
      }

        // FIXME - add cases for BUILTIN_DYAD, BUILTIN_TRIAD, MONADIC_ADVERB, and DYADIC_ADVERB

      default:
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Noun::mix(Storage i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    mixed results = mixed();

    for(int y : iis)
    {
      results.push_back(Word::make(y, NounType::INTEGER));
    }

    return MixedArray::make(results, NounType::LIST);
  }  
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    mixed results = mixed();

    for(float y : iis)
    {
      results.push_back(Float::make(y, NounType::REAL));
    }

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return i;
  }
}

// Extension Dyads - Implementations
Storage Noun::join_scalar(Storage i, Storage x)
{
  return join(enclose(i), enclose(x));
}

Storage Noun::prepend(Storage i, Storage x)
{
  return join(enclose(i), x);
}

Storage Noun::append(Storage i, Storage x)
{
  return join(i, enclose(x));
}

Storage Noun::join_mixed(Storage i, Storage x)
{
  return join(Noun::mix(i), Noun::mix(x));
}

Storage Noun::join_mix_left(Storage i, Storage x)
{
  return join(Noun::mix(i), x);
}

Storage Noun::join_mix_right(Storage i, Storage x)
{
  return join(i, Noun::mix(x));
}

Storage Noun::join_enclose_mix(Storage i, Storage x)
{
  return join(enclose(i), mix(x));
}

Storage Noun::join_mix_enclose(Storage i, Storage x)
{
  return join(mix(i), enclose(x));
}

// Serialization
// Noun::from_bytes decodes a byte array into a Storage object by delegating to each Storage subclass's decoder
maybe<Storage> Noun::from_bytes(bytes x) {
  int t = (int)x.at(0);
  int o = (int)x.at(1);
  bytes untypedData(x.begin() + 2, x.end());

  switch (o) {
    case NounType::INTEGER:
      {
        return maybe<Storage>(Integer::from_bytes(untypedData, t));
      }

    case NounType::REAL:
      {
        return maybe<Storage>(Real::from_bytes(untypedData, t));
      }

    case NounType::LIST:
      {
        return maybe<Storage>(List::from_bytes(untypedData, t));
      }

    case NounType::CHARACTER:
      {
        return maybe<Storage>(Character::from_bytes(untypedData, t));
      }

    case NounType::STRING:
      {
        return maybe<Storage>(IotaString::from_bytes(untypedData, t));
      }
    default:
      switch (t) {
        case StorageType::WORD:
          {
            return maybe<Storage>(Word::from_bytes(untypedData, o));
          }

        case StorageType::FLOAT:
          {
            return maybe<Storage>(Float::from_bytes(untypedData, o));
          }

        case StorageType::WORD_ARRAY:
          {
            return maybe<Storage>(WordArray::from_bytes(untypedData, o));
          }

        case StorageType::FLOAT_ARRAY:
          {
            return maybe<Storage>(FloatArray::from_bytes(untypedData, o));
          }

        case StorageType::MIXED_ARRAY:
          {
            return maybe<Storage>(MixedArray::from_bytes(untypedData, o));
          }
      }

      return std::nullopt;
  }
}

// Encodes a Storage into a byte array by delegating to each subclass
// Format: byte:t byte:o [byte]:subclass.from_bytes(i)
bytes Noun::to_bytes(Storage x) {
  // Noun::to_bytes includes type, never include type in any other to_bytes
  bytes typeBytes = { (byte)x.t, (byte)x.o };

  bytes valueBytes = bytes();
  switch (x.o) {
    case NounType::INTEGER:
      {
        maybe<bytes> maybeValueBytes = Integer::to_bytes(x);
        if (maybeValueBytes) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return bytes();
        }
      }

    case NounType::REAL:
      {
        maybe<bytes> maybeValueBytes = Real::to_bytes(x);
        if (maybeValueBytes) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return bytes();
        }
      }

    case NounType::LIST:
      {
        maybe<bytes> maybeValueBytes = List::to_bytes(x);
        if (maybeValueBytes) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return bytes();
        }
      }

    case NounType::CHARACTER:
      {
        maybe<bytes> maybeValueBytes = Character::to_bytes(x);
        if (maybeValueBytes) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return bytes();
        }
      }

    case NounType::STRING:
      {
        maybe<bytes> maybeValueBytes = IotaString::to_bytes(x);
        if (maybeValueBytes) {
          valueBytes = *maybeValueBytes;
          break;
        } else {
          return bytes();
        }
      }

    default:
      return bytes();
  }

  bytes result(typeBytes.begin(), typeBytes.end());
  result.insert(result.end(), valueBytes.begin(), valueBytes.end());
  return result;
}

maybe<Storage> Noun::from_conn(ReliableConnection conn) {
  int storageType = (int)conn.readOne();
  int objectType = (int)conn.readOne();

  switch (objectType) {
    case NounType::INTEGER:
      return maybe<Storage>(Integer::from_conn(conn, storageType));

    case NounType::REAL:
      return maybe<Storage>(Real::from_conn(conn, storageType));

    case NounType::LIST:
      return maybe<Storage>(List::from_conn(conn, storageType));

    case NounType::CHARACTER:
      return maybe<Storage>(Character::from_conn(conn, storageType));

    case NounType::STRING:
      return maybe<Storage>(IotaString::from_conn(conn, storageType));

    default:
      switch (storageType) {
        case StorageType::WORD:
          {
            return maybe<Storage>(Word::from_conn(conn, objectType));
          }

        case StorageType::FLOAT:
          {
            return maybe<Storage>(Float::from_conn(conn, objectType));
          }

        case StorageType::WORD_ARRAY:
          {
            return maybe<Storage>(WordArray::from_conn(conn, objectType));
          }

        case StorageType::FLOAT_ARRAY:
          {
            return maybe<Storage>(FloatArray::from_conn(conn, objectType));
          }

        case StorageType::MIXED_ARRAY:
          {
            return maybe<Storage>(MixedArray::from_conn(conn, objectType));
          }

        default:
          return std::nullopt;
      }
  }
}

void Noun::to_conn(ReliableConnection conn, Storage x) {
  // Storage.to_conn does not include type information, always include it in the specific to_conn implementation
  switch (x.o) {
    case NounType::INTEGER:
      {
        Integer::to_conn(conn, x);
        return;
      }

    case NounType::REAL:
      {
        Real::to_conn(conn, x);
        return;
      }

    case NounType::LIST:
      {
        List::to_conn(conn, x);
        return;
      }

    case NounType::CHARACTER:
      {
        Character::to_conn(conn, x);
        return;
      }

    case NounType::STRING:
      {
        IotaString::to_conn(conn, x);
        return;
      }

    default:
      switch (x.t) {
        case StorageType::WORD:
          Word::to_conn(conn, x);
          return;

        case StorageType::FLOAT:
          Float::to_conn(conn, x);
          return;

        case StorageType::WORD_ARRAY:
          WordArray::to_conn(conn, x);
          return;

        case StorageType::FLOAT_ARRAY:
          FloatArray::to_conn(conn, x);
          return;

        case StorageType::MIXED_ARRAY:
          MixedArray::to_conn(conn, x);
          return;

        default:
          Word::to_conn(conn, Word::make(UNSUPPORTED_OBJECT, NounType::ERROR));
          return; 
      }
  }
}

// Monads
Storage Noun::enclose_impl(Storage i) {
  return MixedArray::make(mixed({ i }), NounType::LIST);
}

Storage Noun::shape_scalar(Storage i)
{
  return Word::make(0, NounType::INTEGER);
}

// Integer
void Integer::initialize() {
  // Monads
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::ichar, Integer::char_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::inot, Integer::not_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::enclose, Integer::enclose_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::enumerate, Integer::enumerate_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::first, Noun::identity);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::floor, Noun::identity);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::negate, Integer::negate_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::reciprocal, Integer::reciprocal_impl);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::reverse, Noun::identity);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::shape, Noun::shape_scalar);
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::size, Integer::size_impl);

  // Extension Monads
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::evaluate, Storage::identity);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::INTEGER, Monads::evaluate, Storage::identity);

  // Dyads
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, Integer::cut_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::cut, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::cut_reals);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::cut, StorageType::MIXED_ARRAY, NounType::LIST, Integer::cut_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::WORD, NounType::INTEGER, Integer::divide_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::FLOAT, NounType::REAL, Integer::divide_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, Integer::divide_integers);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::divide_reals);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, Integer::divide_mixed);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::equal, StorageType::WORD, NounType::INTEGER, Integer::equal_impl);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::integerDivide, StorageType::WORD, NounType::INTEGER, Integer::integerDivide_impl);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD, NounType::INTEGER, Integer::join_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::FLOAT, NounType::REAL, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, List::prepend_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_scalar);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::WORD, NounType::INTEGER, Integer::less_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::FLOAT, NounType::REAL, Integer::less_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, Integer::less_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::less_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, Integer::less_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD, NounType::INTEGER, Integer::match_impl);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::FLOAT, NounType::REAL, Integer::match_impl);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::WORD, NounType::INTEGER, Integer::max_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::FLOAT, NounType::REAL, Integer::max_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, Integer::max_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::max_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, Integer::max_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::WORD, NounType::INTEGER, Integer::min_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::FLOAT, NounType::REAL, Integer::min_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, Integer::min_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::min_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, Integer::min_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::WORD, NounType::INTEGER, Integer::minus_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::FLOAT, NounType::REAL, Integer::minus_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, Integer::minus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::minus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, Integer::minus_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::WORD, NounType::INTEGER, Integer::more_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::FLOAT, NounType::REAL, Integer::more_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, Integer::more_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::more_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, Integer::more_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::WORD, NounType::INTEGER, Integer::plus_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::FLOAT, NounType::REAL, Integer::plus_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, Integer::plus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::plus_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, Integer::plus_list);

  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::WORD, NounType::INTEGER, Integer::power_integer);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::FLOAT, NounType::REAL, Integer::power_real);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, Integer::power_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, Integer::power_list);
  Noun::registerDyad(StorageType::WORD, NounType::INTEGER, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, Integer::power_list);
}

// Monads
Storage Integer::char_impl(Storage i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(integer, NounType::CHARACTER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::enclose_impl(Storage i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return WordArray::make(ints({ integer }), NounType::LIST);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::enumerate_impl(Storage i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);

    ints results(integer);
    std::iota(results.begin(), results.end(), 1);  // iota here refers to the C++/STL version of enumerate

    return WordArray::make(results, NounType::LIST);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::negate_impl(Storage i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(-integer, NounType::INTEGER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::not_impl(Storage i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(1 - integer, NounType::INTEGER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::reciprocal_impl(Storage i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Float::make(1.0 / static_cast<float>(integer), NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::size_impl(Storage i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(abs(integer), NounType::INTEGER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads
Storage Integer::cut_integers(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints integers = std::get<ints>(x.i);

      if(integer == 0)
      {
        if(integers.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), x);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer > 0 && integer <= integers.size())
      {
        ints left = ints(integers.begin(), integers.begin() + integer);
        ints right = ints(integers.begin() + integer, integers.end());

        mixed results = mixed();
        results.insert(results.end(), WordArray::make(left, NounType::LIST));
        results.insert(results.end(), WordArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::cut_reals(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats list = std::get<floats>(x.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), x);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer > 0 && integer <= list.size())
      {
        floats left = floats(list.begin(), list.begin() + integer);
        floats right = floats(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), FloatArray::make(left, NounType::LIST));
        results.insert(results.end(), FloatArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::cut_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed list = std::get<mixed>(x.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), x);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer > 0 && integer <= list.size())
      {
        mixed left = mixed(list.begin(), list.begin() + integer);
        mixed right = mixed(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), MixedArray::make(left, NounType::LIST));
        results.insert(results.end(), MixedArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Floating-point division with two integer arguments
Storage Integer::divide_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      float fx = static_cast<float>(xi);

      return Float::make(fi / fx, NounType::REAL);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Floating-point division with an integer and a float
Storage Integer::divide_real(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fx < Float::tolerance)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      return Float::make(fi / fx, NounType::REAL);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::divide_integers(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();
      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if(y == 0)
        {
          return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
        }

        results.insert(results.end(), fi / fy);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::divide_reals(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<floats>(x.i))
    {
      floats fis = std::get<floats>(x.i);

      floats results = floats();
      for(float fy : fis)
      {
        if(fy < Float::tolerance)
        {
          return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
        }

        results.insert(results.end(), fi / fy);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::divide_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      floats results = floats();
      for(Storage y : xis)
      {
        Storage result = divide(Float::make(fi, NounType::REAL), y);

        if(result.t == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<float>(result.i))
        {
          float fr = std::get<float>(result.i);
          results.insert(results.end(), fr);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::equal_impl(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      return Word::make(ii == xi, NounType::INTEGER);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::integerDivide_impl(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      return Word::make(ii / xi, NounType::INTEGER);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Join
Storage Integer::join_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results = ints({ii, xi});

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::prepend_to_integers(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xi = std::get<ints>(x.i);

      ints results(xi);
      results.insert(results.begin(), ii);

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::less_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii < xi)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::less_real(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fi < fx)
      {
        float difference = fx - fi;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false0();
}

Storage Integer::less_list(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii < y)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      ints results = ints();

      for(float fy : xis)
      {
        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(Storage y : xis)
      {
        Storage result = less(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::match_impl(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii == xi)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
    else if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);
      float fi = static_cast<float>(ii);

      if(abs(fi - fx) < Float::tolerance)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::max_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii < xi)
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::max_real(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if((fi < fx) && ((fx - fi) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Noun::false0();
}

Storage Integer::max_list(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii < y)
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      mixed results = mixed();

      for(float fy : xis)
      {
        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(Float::make(fy));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = less(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(si);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::min_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii > xi)
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::min_real(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if((fi > fx) && ((fi - fx) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Noun::false0();
}

Storage Integer::min_list(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii > y)
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      mixed results = mixed();

      for(float fy : xis)
      {
        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(Float::make(fy));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = more(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(si);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::minus_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      int result = ii - xi;
      return Word::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::minus_real(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      float result = fi - fx;
      return Float::make(result);
    }
  }

  return Noun::false0();
}

Storage Integer::minus_list(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        results.push_back(ii - y);
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi - fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = minus(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::more_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii > xi)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::more_real(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fi > fx)
      {
        float difference = fi - fx;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false0();
}

Storage Integer::more_list(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        if(ii > y)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      ints results = ints();

      for(float fy : xis)
      {
        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(Storage y : xis)
      {
        Storage result = more(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::plus_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      int result = ii + xi;
      return Word::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::plus_real(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      float result = fi + fx;
      return Float::make(result);
    }
  }

  return Noun::false0();
}

Storage Integer::plus_list(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        results.push_back(ii + y);
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi + fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = plus(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::power_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      float fi = static_cast<float>(ii);
      float fx = static_cast<float>(xi);

      float result = powf(fi, fx);
      return Float::make(result);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Integer::power_real(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);
    float fi = static_cast<float>(ii);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      float result = powf(fi, fx);
      return Float::make(result);
    }
  }

  return Noun::false0();
}

Storage Integer::power_list(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      float fi = static_cast<float>(ii);

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(powf(fi, fy));
      }

      return FloatArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      float fi = static_cast<float>(ii);
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(powf(fi, fy));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Word::make(ii);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = power(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Serialization
maybe<Storage> Integer::from_bytes(bytes bs, int t) {
  switch (t) {
    case StorageType::WORD:
      return Word::from_bytes(bs, NounType::INTEGER);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Integer::to_bytes(Storage i) {
  if (i.o != NounType::INTEGER) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::WORD:
      return Word::to_bytes(i);

    case StorageType::WORD_ARRAY:
      if (std::holds_alternative<ints>(i.i)) {
        ints integers = std::get<ints>(i.i);
        return squeeze_bigint(integers);
      } else {
        return std::nullopt;
      }

    default:
      return std::nullopt;
  }
}

maybe<Storage> Integer::from_conn(ReliableConnection conn, int t) {
  switch (t) {
    case NounType::INTEGER:
      return Word::from_conn(conn, NounType::INTEGER);

    default:
      return std::nullopt;
  }
}

void Integer::to_conn(ReliableConnection conn, Storage i) {
  if (i.o != NounType::INTEGER) {
    return;
  }

  switch (i.t) {
    case StorageType::WORD:
      {
        // No need to include type here because it is provided by Word::to_conn
        return Word::to_conn(conn, i);
      }

    case StorageType::WORD_ARRAY:
      {
        if (std::holds_alternative<ints>(i.i)) {
          ints integers = std::get<ints>(i.i);
          bytes intBytes = squeeze_bigint(integers);

          // Note that we always send NounType::INTEGERs and StorageType::WORDs, even if we internally represent them as StorageType::WORD_ARRAYs.
          conn.write({ (byte)StorageType::WORD, (byte)i.o });
          conn.write(intBytes);
        } else {
          return;
        }
      }

    default:
      return;
  }
}

// Real
// Registration
void Real::initialize() {
  // Monads
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::enclose, Real::enclose_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::first, Noun::identity);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::floor, Real::floor_impl);
  // FIXME - format
  // FIXME - group
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::negate, Real::negate_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::inot, Real::not_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::reciprocal, Real::reciprocal_impl);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::reverse, Noun::identity);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::shape, Noun::shape_scalar);
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::size, Real::size_impl);

  // Extension Monads
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::evaluate, Storage::identity);

  // Dyads
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::WORD, NounType::INTEGER, Real::divide_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::FLOAT, NounType::REAL, Real::divide_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, Real::divide_integers);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, Real::divide_reals);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, Real::divide_mixed);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::join_scalar);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::FLOAT, NounType::REAL, Real::join_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Real::prepend_to_reals);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::prepend);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_scalar);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_scalar);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::WORD, NounType::INTEGER, Real::less_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::FLOAT, NounType::REAL, Real::less_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, Real::less_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, Real::less_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, Real::less_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD, NounType::INTEGER, Real::match_impl);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::FLOAT, NounType::REAL, Real::match_impl);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::WORD, NounType::INTEGER, Real::max_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::FLOAT, NounType::REAL, Real::max_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, Real::max_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, Real::max_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, Real::max_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::WORD, NounType::INTEGER, Real::min_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::FLOAT, NounType::REAL, Real::min_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, Real::min_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, Real::min_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, Real::min_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::WORD, NounType::INTEGER, Real::minus_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::FLOAT, NounType::REAL, Real::minus_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, Real::minus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, Real::minus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, Real::minus_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::WORD, NounType::INTEGER, Real::more_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::FLOAT, NounType::REAL, Real::more_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, Real::more_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, Real::more_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, Real::more_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::WORD, NounType::INTEGER, Real::plus_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::FLOAT, NounType::REAL, Real::plus_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, Real::plus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, Real::plus_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, Real::plus_list);

  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::WORD, NounType::INTEGER, Real::power_integer);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::FLOAT, NounType::REAL, Real::power_real);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, Real::power_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, Real::power_list);
  Noun::registerDyad(StorageType::FLOAT, NounType::REAL, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, Real::power_list);
}

Storage Real::enclose_impl(Storage i)
{
  if (std::holds_alternative<float>(i.i))
  {
    float f = std::get<float>(i.i);
    return FloatArray::make(floats({ f }), NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::floor_impl(Storage i)
{
  if (std::holds_alternative<float>(i.i))
  {
    float f = std::get<float>(i.i);
    int result = (int)std::floor(f);

    return Word::make(result, NounType::INTEGER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::negate_impl(Storage i) {
  if (std::holds_alternative<float>(i.i)) {
    float f = std::get<float>(i.i);
    return Float::make(-f, NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::not_impl(Storage i) {
  if (std::holds_alternative<float>(i.i)) {
    float f = std::get<float>(i.i);
    return Float::make(1.0 - f, NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::reciprocal_impl(Storage i) {
  if (std::holds_alternative<float>(i.i)) {
    float f = std::get<float>(i.i);
    return Float::make(1.0 / f, NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Real::size_impl(Storage i) {
  if (std::holds_alternative<float>(i.i)) {
    float f = std::get<float>(i.i);
    return Float::make(abs(f), NounType::REAL);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads
// Floating-point division with a float and an integer
Storage Real::divide_integer(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      float fx = static_cast<float>(xi);

      return Float::make(fi / fx, NounType::REAL);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Floating-point division with two floats
Storage Real::divide_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fx < Float::tolerance)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      return Float::make(fi / fx, NounType::REAL);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::divide_integers(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();
      for(int y : xis)
      {
        if(y == 0)
        {
          return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
        }

        float fy = static_cast<float>(y);
        results.insert(results.end(), fi / fy);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::divide_reals(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats fis = std::get<floats>(x.i);

      floats results = floats();
      for(float fy : fis)
      {
        if(fy < Float::tolerance)
        {
          return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
        }

        results.insert(results.end(), fi / fy);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::divide_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      floats results = floats();
      for(Storage y : xis)
      {
        Storage result = divide(Float::make(fi, NounType::REAL), y);

        if(result.t == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<float>(result.i))
        {
          float fr = std::get<float>(result.i);
          results.insert(results.end(), fr);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Join
Storage Real::join_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float ii = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      floats results = floats({ii, xi});

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::prepend_to_reals(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float ii = std::get<float>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xi = std::get<floats>(x.i);

      floats results(xi);
      results.insert(results.begin(), ii);

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::less_integer(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      if(fi < fx)
      {
        float difference = fx - fi;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::less_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fi < fx)
      {
        float difference = fx - fi;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::less_list(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      ints results = ints();

      for(float fy : xis)
      {
        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(Storage y : xis)
      {
        Storage result = less(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::max_integer(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      if((fi < fx) && ((fx - fi) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::max_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if((fi < fx) && ((fx - fi) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::max_list(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(Word::make(y));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        if((fi < fy) && ((fy - fi) > Float::tolerance))
        {
          results.push_back(fy);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = less(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(si);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::min_integer(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      if((fi > fx) && ((fi - fx) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::min_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if((fi > fx) && ((fi - fx) > Float::tolerance))
      {
        return x;
      }
      else
      {
        return i;
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::min_list(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(Word::make(y));
        }
        else
        {
          results.push_back(i);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(fy);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = more(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(y);
        }
        else
        {
          results.push_back(si);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::minus_integer(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      return Float::make(fi - fx);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::minus_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      return Float::make(fi - fx);
    }
  }

  return Noun::false1(i);
}

Storage Real::minus_list(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fi - fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi - fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = minus(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::match_impl(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      if(abs(fi - fx) < Float::tolerance)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
    else if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(abs(fi - fx) < Float::tolerance)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::more_integer(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      if(fi > fx)
      {
        float difference = fi - fx;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::more_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      if(fi > fx)
      {
        float difference = fi - fx;
        if(difference > Float::tolerance)
        {
          return Noun::true0();
        }
      }
    }
  }

  return Noun::false1(i);
}

Storage Real::more_list(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      ints results = ints();

      for(float fy : xis)
      {
        if((fi > fy) && ((fi - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(Storage y : xis)
      {
        Storage result = more(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::plus_integer(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      return Float::make(fi + fx);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::plus_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      return Float::make(fi + fx);
    }
  }

  return Noun::false1(i);
}

Storage Real::plus_list(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fi + fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(fi + fy);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = plus(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::power_integer(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      float fx = static_cast<float>(xi);

      return Float::make(powf(fi, fx));
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Real::power_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    int fi = std::get<float>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      return Float::make(powf(fi, fx));
    }
  }

  return Noun::false1(i);
}

Storage Real::power_list(Storage i, Storage x)
{
  if(std::holds_alternative<float>(i.i))
  {
    float fi = std::get<float>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();

      for(int y : xis)
      {
        float fy = static_cast<float>(y);

        results.push_back(powf(fi, fy));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results = floats();

      for(float fy : xis)
      {
        results.push_back(powf(fi, fy));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      Storage si = Float::make(fi);
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : xis)
      {
        Storage result = power(si, y);
        if(result.t == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Serialization
maybe<Storage> Real::from_bytes(bytes bs, int t) {
  switch (t) {
    case StorageType::FLOAT:
      return Float::from_bytes(bs, NounType::REAL);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Real::to_bytes(Storage i) {
  if (i.o != NounType::REAL) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::FLOAT:
      return Float::to_bytes(i);

    default:
      return std::nullopt;
  }
}

maybe<Storage> Real::from_conn(ReliableConnection conn, int t) {
  switch (t) {
    case StorageType::FLOAT:
      return Float::from_conn(conn, NounType::REAL);

    default:
      return std::nullopt;
  }
}

void Real::to_conn(ReliableConnection conn, Storage i) {
  if (i.o != NounType::REAL) {
    return;
  }

  switch (i.t) {
    case StorageType::FLOAT:
      {
        // No need to include type here because it is provided by Float::to_conn
        return Float::to_conn(conn, i);
      }

    default:
      return;
  }
}

// List
void List::initialize() {
  // WordArray
  // Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::inot, List::not_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::first, List::first_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::floor, Noun::identity);
  // FIXME - format
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::gradeDown, List::gradeDown_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::gradeUp, List::gradeUp_impl);
  // FIXME - group
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::negate, List::negate_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::reciprocal, List::reciprocal_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::reverse, List::reverse_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::shape, List::shape_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::size, List::size_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::unique, List::unique_impl);
  
  // Extension Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::evaluate, Storage::identity);

  // Dyads
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD, NounType::INTEGER, List::cut_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, List::cut_integers);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD, NounType::INTEGER, List::divide_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT, NounType::REAL, List::divide_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, List::divide_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, List::divide_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, List::divide_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::drop, StorageType::WORD, NounType::INTEGER, List::drop_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::equal, StorageType::WORD_ARRAY, NounType::LIST, List::equal_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::INTEGER, List::find_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT, NounType::REAL, List::find_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::LIST, List::find_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT_ARRAY, NounType::LIST, List::find_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::LIST, List::find_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD, NounType::INTEGER, List::index_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, List::index_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::INTEGER, List::append_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT, NounType::REAL, List::join_integers_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, List::join_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::join_mixed);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::join_mix_left);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_mix_enclose);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_mix_enclose);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD, NounType::INTEGER, List::less_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT, NounType::REAL, List::less_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, List::less_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, List::less_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, List::less_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD, NounType::INTEGER, List::max_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT, NounType::REAL, List::max_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, List::max_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, List::max_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, List::max_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD, NounType::INTEGER, List::min_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT, NounType::REAL, List::min_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, List::min_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, List::min_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, List::min_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD, NounType::INTEGER, List::minus_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT, NounType::REAL, List::minus_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, List::minus_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, List::minus_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, List::minus_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD, NounType::INTEGER, List::more_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT, NounType::REAL, List::more_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, List::more_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, List::more_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, List::more_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD, NounType::INTEGER, List::plus_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT, NounType::REAL, List::plus_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, List::plus_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, List::plus_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, List::plus_mixed);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD, NounType::INTEGER, List::power_integer);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT, NounType::REAL, List::power_real);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, List::power_integers);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, List::power_reals);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::LIST, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, List::power_mixed);  

  // FloatArray
  // Monads
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::inot, List::not_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::first, List::first_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::floor, List::floor_impl);
  // FIXME - format
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::gradeDown, List::gradeDown_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::gradeUp, List::gradeUp_impl);
  // FIXME - group
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::negate, List::negate_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::reciprocal, List::reciprocal_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::reverse, List::reverse_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::shape, List::shape_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::size, List::size_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::unique, List::unique_impl);

  // Extension Monads
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::evaluate, Storage::identity);

  // Dyads
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD, NounType::INTEGER, List::cut_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, List::cut_integers);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD, NounType::INTEGER, List::divide_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT, NounType::REAL, List::divide_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, List::divide_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, List::divide_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, List::divide_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::drop, StorageType::WORD, NounType::INTEGER, List::drop_impl);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::INTEGER, List::find_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT, NounType::REAL, List::find_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::LIST, List::find_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT_ARRAY, NounType::LIST, List::find_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::LIST, List::find_impl);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD, NounType::INTEGER, List::index_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, List::index_impl);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::join_mix_enclose);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT, NounType::REAL, List::append_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::join_mixed);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, List::join_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::join_mix_left);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::join_mix_enclose);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_mix_enclose);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD, NounType::INTEGER, List::less_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT, NounType::REAL, List::less_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, List::less_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, List::less_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, List::less_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD, NounType::INTEGER, List::max_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT, NounType::REAL, List::max_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, List::max_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, List::max_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, List::max_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD, NounType::INTEGER, List::min_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT, NounType::REAL, List::min_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, List::min_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, List::min_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, List::min_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD, NounType::INTEGER, List::minus_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT, NounType::REAL, List::minus_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, List::minus_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, List::minus_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, List::minus_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD, NounType::INTEGER, List::more_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT, NounType::REAL, List::more_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, List::more_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, List::more_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, List::more_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD, NounType::INTEGER, List::plus_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT, NounType::REAL, List::plus_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, List::plus_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, List::plus_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, List::plus_mixed);

  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD, NounType::INTEGER, List::power_integer);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT, NounType::REAL, List::power_real);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, List::power_integers);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, List::power_reals);
  Noun::registerDyad(StorageType::FLOAT_ARRAY, NounType::LIST, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, List::power_mixed);  

  // MixedArray
  // Monads
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::inot, List::not_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::first, List::first_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::floor, List::floor_impl);
  // FIXME - format
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::gradeDown, List::gradeDown_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::gradeUp, List::gradeUp_impl);
  // FIXME - group
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::negate, List::negate_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::reciprocal, List::reciprocal_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::reverse, List::reverse_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::shape, List::shape_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::size, List::size_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::transpose, List::transpose_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::unique, List::unique_impl);

  // Extension Monads
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::evaluate, Storage::identity);

  // Dyads
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD, NounType::INTEGER, List::cut_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::cut, StorageType::WORD_ARRAY, NounType::LIST, List::cut_integers);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD, NounType::INTEGER, List::divide_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT, NounType::REAL, List::divide_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::WORD_ARRAY, NounType::LIST, List::divide_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::FLOAT_ARRAY, NounType::LIST, List::divide_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::divide, StorageType::MIXED_ARRAY, NounType::LIST, List::divide_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::drop, StorageType::WORD, NounType::INTEGER, List::drop_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD, NounType::INTEGER, List::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT, NounType::REAL, List::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::WORD_ARRAY, NounType::LIST, List::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::FLOAT_ARRAY, NounType::LIST, List::find_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::find, StorageType::MIXED_ARRAY, NounType::LIST, List::find_impl);  

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD, NounType::INTEGER, List::index_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, List::index_impl);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::append);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT, NounType::REAL, Noun::append);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::join_mix_right);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::join_mix_right);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, List::join_mixed);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD, NounType::CHARACTER, Noun::append);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Noun::join_mix_right);
  
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD, NounType::INTEGER, List::less_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT, NounType::REAL, List::less_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::WORD_ARRAY, NounType::LIST, List::less_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::FLOAT_ARRAY, NounType::LIST, List::less_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::less, StorageType::MIXED_ARRAY, NounType::LIST, List::less_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, List::match_impl);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD, NounType::INTEGER, List::max_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT, NounType::REAL, List::max_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::WORD_ARRAY, NounType::LIST, List::max_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::FLOAT_ARRAY, NounType::LIST, List::max_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::max, StorageType::MIXED_ARRAY, NounType::LIST, List::max_mixed);

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD, NounType::INTEGER, List::min_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT, NounType::REAL, List::min_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::WORD_ARRAY, NounType::LIST, List::min_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::FLOAT_ARRAY, NounType::LIST, List::min_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::min, StorageType::MIXED_ARRAY, NounType::LIST, List::min_mixed);  

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD, NounType::INTEGER, List::minus_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT, NounType::REAL, List::minus_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::WORD_ARRAY, NounType::LIST, List::minus_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::FLOAT_ARRAY, NounType::LIST, List::minus_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::minus, StorageType::MIXED_ARRAY, NounType::LIST, List::minus_mixed);   

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD, NounType::INTEGER, List::more_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT, NounType::REAL, List::more_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::WORD_ARRAY, NounType::LIST, List::more_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::FLOAT_ARRAY, NounType::LIST, List::more_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::more, StorageType::MIXED_ARRAY, NounType::LIST, List::more_mixed);   

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD, NounType::INTEGER, List::plus_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT, NounType::REAL, List::plus_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::WORD_ARRAY, NounType::LIST, List::plus_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::FLOAT_ARRAY, NounType::LIST, List::plus_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::plus, StorageType::MIXED_ARRAY, NounType::LIST, List::plus_mixed);   

  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD, NounType::INTEGER, List::power_integer);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT, NounType::REAL, List::power_real);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::WORD_ARRAY, NounType::LIST, List::power_integers);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::FLOAT_ARRAY, NounType::LIST, List::power_reals);
  Noun::registerDyad(StorageType::MIXED_ARRAY, NounType::LIST, Dyads::power, StorageType::MIXED_ARRAY, NounType::LIST, List::power_mixed);   
}

Storage List::atom_impl(Storage i) {
  if (std::holds_alternative<ints>(i.i)) {
    ints integers = std::get<ints>(i.i);
    if (integers.empty()) {
      return Noun::true0();
    } else {
      return Noun::false0();
    }
  } else if (std::holds_alternative<floats>(i.i)) {
    floats fs = std::get<floats>(i.i);
    if (fs.empty()) {
      return Noun::true0();
    } else {
      return Noun::false0();
    }
  } else if (std::holds_alternative<mixed>(i.i)) {
    mixed ms = std::get<mixed>(i.i);
    if (ms.empty()) {
      return Noun::true0();
    } else {
      return Noun::false0();
    }
  } else {
    return Noun::false0();
  }
}

Storage List::char_impl(Storage i) {
  if (std::holds_alternative<ints>(i.i)) {
    ints integers = std::get<ints>(i.i);

    if (integers.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    }

    mixed ms = mixed();
    for (int y : integers) {
      ms.insert(ms.end(), Word::make(y, NounType::CHARACTER));
    }
    return MixedArray::make(ms, NounType::LIST);
  } else if (std::holds_alternative<floats>(i.i)) {
    floats fs = std::get<floats>(i.i);

    if (fs.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    } else {
      return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  } else if (std::holds_alternative<mixed>(i.i)) {
    mixed ms = std::get<mixed>(i.i);

    if (ms.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    } else {
      return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::first_impl(Storage i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    int integer = integers.front();

    return Word::make(integer, NounType::INTEGER);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    float f = fs.front();

    return Float::make(f, NounType::REAL);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    Storage result = ms.front();

    return result;
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::floor_impl(Storage i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    return i;
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    ints results = ints();
    for(float y : fs)
    {
      results.insert(results.end(), (int)std::floor(y));
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    mixed results = mixed();
    for(Storage y : ms)
    {
      results.insert(results.end(), floor(y));
    }

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::gradeDown_impl(Storage i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());
    
    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](int x, int y)
    {
        return integers[x] > integers[y];
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);
    if(fs.empty())
    {
      return i;
    }

    ints results(fs.size());
    
    for (int i = 0; i < results.size(); ++i)
    {
        results[i] = i;
    }

    std::sort(results.begin(), results.end(), [&fs](int x, int y)
    {
        if(fs[x] > fs[y])
        {
          float difference = fs[x] - fs[y];
          if(difference > Float::tolerance)
          {
            return 1; // x > y
          }
          else
          {
            return 0; // x ~= y
          }
        }
        else
        {
          return 0; // x <= y
        }
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);
    if(ms.empty())
    {
      return i;
    }

    ints results(ms.size());
    
    for (int i = 0; i < results.size(); ++i)
    {
        results[i] = i;
    }

    std::sort(results.begin(), results.end(), [&ms](int x, int y)
    {
        Storage result = more(ms[x], ms[y]);
        switch(result.t)
        {
          case NounType::INTEGER:
            if(std::holds_alternative<int>(result.i))
            {
              return std::get<int>(result.i);
            }
        }

        return 0;
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::gradeUp_impl(Storage i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());
    
    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](int x, int y)
    {
        return integers[x] < integers[y];
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);
    if(fs.empty())
    {
      return i;
    }

    ints results(fs.size());
    
    for (int i = 0; i < results.size(); ++i)
    {
        results[i] = i;
    }

    std::sort(results.begin(), results.end(), [&fs](int x, int y)
    {
        if(fs[x] < fs[y])
        {
          float difference = fs[y] - fs[x];
          if(difference > Float::tolerance)
          {
            return 1; // y < x
          }
          else
          {
            return 0; // y ~= x
          }
        }
        else
        {
          return 0; // y >= x
        }
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);
    if(ms.empty())
    {
      return i;
    }

    ints results(ms.size());
    
    for (int i = 0; i < results.size(); ++i)
    {
        results[i] = i;
    }

    std::sort(results.begin(), results.end(), [&ms](int x, int y)
    {
        Storage result = less(ms[x], ms[y]);
        switch(result.t)
        {
          case NounType::INTEGER:
            if(std::holds_alternative<int>(result.i))
            {
              int integer = std::get<int>(result.i);
              return integer;
            }
        }

        return 0;
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::negate_impl(Storage i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return i;
    }

    ints results = ints();
    for(int y : integers)
    {
      results.insert(results.end(), -y);
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return i;
    }

    floats results = floats();
    for(float y : fs)
    {
      results.insert(results.end(), -y);
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }

    mixed results = mixed();
    for(Storage y : ms)
    {
      results.insert(results.end(), negate(y));
    }

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::not_impl(Storage i) {
  if (std::holds_alternative<ints>(i.i)) {
    ints integers = std::get<ints>(i.i);

    if (integers.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    }

    ints results = ints();
    for (int y : integers) {
      int result = 1 - y;
      results.insert(results.end(), result);
    }
    return WordArray::make(results, NounType::LIST);
  } else if (std::holds_alternative<floats>(i.i)) {
    floats fs = std::get<floats>(i.i);

    if (fs.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    }

    floats results = floats();
    for (float y : fs) {
      float result = 1.0 - y;
      results.insert(results.end(), result);
    }
    return FloatArray::make(results, NounType::LIST);
  } else if (std::holds_alternative<mixed>(i.i)) {
    mixed ms = std::get<mixed>(i.i);

    if (ms.empty()) {
      return WordArray::make(ints(), NounType::LIST);
    }

    mixed results = mixed();
    for (Storage y : ms) {
      Storage result = inot(y);
      results.insert(results.end(), result);
    }
    return MixedArray::make(results, NounType::LIST);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::reciprocal_impl(Storage i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return i;
    }

    floats results = floats();
    for(int y : integers)
    {
      results.insert(results.end(), 1.0 / static_cast<float>(y));
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return i;
    }

    floats results = floats();
    for(float y : fs)
    {
      results.insert(results.end(), 1.0 / y);
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }

    mixed results = mixed();
    for(Storage y : ms)
    {
      results.insert(results.end(), divide(Float::make(1.0, NounType::REAL), y));
    }

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::reverse_impl(Storage i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return i;
    }

    ints results = ints(integers);
    std::reverse(results.begin(), results.end());

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return i;
    }

    floats results = floats(fs);
    std::reverse(results.begin(), results.end());

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }

    mixed results = mixed(ms);
    std::reverse(results.begin(), results.end());

    return MixedArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::shape_impl(Storage i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return Word::make(0, NounType::INTEGER);
    }

    ints results = ints({static_cast<int>(integers.size())});
    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return Word::make(0, NounType::INTEGER);
    }

    ints results = ints({static_cast<int>(fs.size())});
    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return Word::make(0, NounType::INTEGER);
    }

    mixed shapes = mixed();
    for(Storage y : ms)
    {
      Storage result = shape(y);
      shapes.insert(shapes.end(), result);
    }

    Storage firstShape = shapes.front();
    if(firstShape.o == NounType::LIST && firstShape.t == StorageType::WORD_ARRAY && std::holds_alternative<ints>(firstShape.i))
    {
      ints firstShapeIntegers = std::get<ints>(firstShape.i);

      for(Storage y : shapes)
      {
        Storage nextShape = shape(y);
        if(nextShape.o == NounType::LIST && nextShape.t == StorageType::WORD_ARRAY && std::holds_alternative<ints>(nextShape.i))
        {
          ints nextShapeIntegers = std::get<ints>(nextShape.i);

          if(firstShapeIntegers != nextShapeIntegers)
          {
            return WordArray::make(ints({static_cast<int>(shapes.size())}), NounType::LIST);
          }
        }
      }

      ints results = ints(firstShapeIntegers);
      results.insert(results.begin(), shapes.size());

      return WordArray::make(results, NounType::LIST);
    }
    else
    {
      return WordArray::make(ints({static_cast<int>(ms.size())}), NounType::LIST);
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage List::size_impl(Storage i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    return Word::make(static_cast<int>(integers.size()), NounType::INTEGER);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    return Word::make(static_cast<int>(fs.size()), NounType::INTEGER);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    return Word::make(static_cast<int>(ms.size()), NounType::INTEGER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// We can only transpose 2D arrays, which means a mixed array of either all words or all floats, where all subarrays are the same size
// FIXME - support 2D arrays of mixed words and floats
// FIXME - support 2D arrays of bigints
Storage List::transpose_impl(Storage i)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return i;
    }
    else
    {
      int all_word_arrays = 1;
      int all_float_arrays = 1;
      for(Storage y : ms)
      {
        if(y.t == StorageType::WORD_ARRAY)
        {
          all_float_arrays = 0;
        }
        else if(y.t == StorageType::FLOAT_ARRAY)
        {
          all_word_arrays = 0;
        }
        else
        {
          all_word_arrays = 0;
          all_float_arrays = 0;
          break;
        }
      }

      if(all_word_arrays)
      {
        Storage first = ms.front();
        if(std::holds_alternative<ints>(first.i))
        {
          ints firstIntegers = std::get<ints>(first.i);

          int rows = ms.size();
          int columns = firstIntegers.size();

          std::vector<ints> source(rows);
          for (int j = 0; j < rows; ++j)
          {
            Storage subarray = ms[j];
            if(std::holds_alternative<ints>(subarray.i))
            {
              source[j] = std::get<ints>(subarray.i);
            }
            else
            {
              return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
            }
          }

          std::vector<ints> transposed(columns, ints(rows));
          for (int j = 0; j < rows; ++j)
          {
            for (int k = 0; k < columns; ++k)
            {
                transposed[k][j] = source[j][k];  // Swap row and column indices
            }
          }

          mixed results = mixed();
          for (int k = 0; k < columns; ++k)
          {
            results.insert(results.end(), WordArray::make(transposed[k], NounType::LIST));
          }

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(all_float_arrays)
      {
        Storage first = ms.front();
        if(std::holds_alternative<floats>(first.i))
        {
          floats firstFloats = std::get<floats>(first.i);

          int rows = ms.size();
          int columns = firstFloats.size();

          std::vector<floats> source(rows);
          for (int j = 0; j < rows; ++j)
          {
            Storage subarray = ms[j];
            if(std::holds_alternative<floats>(subarray.i))
            {
              source[j] = std::get<floats>(subarray.i);
            }
            else
            {
              return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
            }
          }

          std::vector<floats> transposed(columns, floats(rows));
          for (int j = 0; j < rows; ++j)
          {
            for (int k = 0; k < columns; ++k)
            {
                transposed[k][j] = source[j][k];  // Swap row and column indices
            }
          }

          mixed results = mixed();
          for (int k = 0; k < columns; ++k)
          {
            results.insert(results.end(), FloatArray::make(transposed[k], NounType::LIST));
          }

          return MixedArray::make(results, NounType::LIST);
        }
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::unique_impl(Storage i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    std::unordered_set<int> set = std::unordered_set<int>();
    ints results = ints();

    for(int y : integers)
    {
      if(set.find(y) == set.end())
      {
        set.insert(y);
        results.insert(results.end(), y);
      }
    }

    return WordArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    std::unordered_set<float> set = std::unordered_set<float>();
    floats results = floats();

    for(float y : fs)
    {
      if(set.find(y) == set.end())
      {
        set.insert(y);
        results.insert(results.end(), y);
      }
    }

    return FloatArray::make(results, NounType::LIST);
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    // FIXME - implement unique for mixed
    // mixed ms = std::get<mixed>(i.i);

    // std::unordered_set<Storage> set = std::unordered_set<Storage>();
    // mixed results = mixed();

    // for(Storage y : ms)
    // {
    //   if(set.find(y) == set.end())
    //   {
    //     set.insert(y);
    //     results.insert(results.end(), y);
    //   }
    // }

    // return MixedArray::make(results, NounType::LIST);
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// List Dyads
// FIXME - cut for strings
Storage List::cut_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int integer = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints list = std::get<ints>(i.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), i);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer == list.size())
      {
          mixed results = mixed();
          results.insert(results.end(), i);
          results.insert(results.end(), WordArray::nil());

          return MixedArray::make(results, NounType::LIST);
      }
      else if(integer > 0 && integer < list.size())
      {
        ints left = ints(list.begin(), list.begin() + integer);
        ints right = ints(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), WordArray::make(left, NounType::LIST));
        results.insert(results.end(), WordArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats list = std::get<floats>(i.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), i);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer == list.size())
      {
          mixed results = mixed();
          results.insert(results.end(), i);
          results.insert(results.end(), WordArray::nil());

          return MixedArray::make(results, NounType::LIST);
      }
      else if(integer > 0 && integer < list.size())
      {
        floats left = floats(list.begin(), list.begin() + integer);
        floats right = floats(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), FloatArray::make(left, NounType::LIST));
        results.insert(results.end(), FloatArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed list = std::get<mixed>(i.i);

      if(integer == 0)
      {
        if(list.empty())
        {
          Storage result = WordArray::nil();
          mixed results = mixed({result});

          return MixedArray::make(results, NounType::LIST);
        }
        else
        {
          mixed results = mixed();
          results.insert(results.end(), WordArray::nil());
          results.insert(results.end(), i);

          return MixedArray::make(results, NounType::LIST);
        }
      }
      else if(integer == list.size())
      {
          mixed results = mixed();
          results.insert(results.end(), i);
          results.insert(results.end(), WordArray::nil());

          return MixedArray::make(results, NounType::LIST);
      }
      else if(integer > 0 && integer < list.size())
      {
        mixed left = mixed(list.begin(), list.begin() + integer);
        mixed right = mixed(list.begin() + integer, list.end());

        mixed results = mixed();
        results.insert(results.end(), MixedArray::make(left, NounType::LIST));
        results.insert(results.end(), MixedArray::make(right, NounType::LIST));
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::cut_integers(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints integers = std::get<ints>(x.i);

    // If no indices where specified, we always return [i]
    if(integers.empty())
    {
      mixed results = mixed({i});
      return MixedArray::make(results, NounType::LIST);
    }

    if(std::holds_alternative<ints>(i.i))
    {
      ints list = std::get<ints>(i.i);

      // Indices are non-empty, so source list must also be non-empty
      if(!list.empty())
      {
        mixed results = mixed();

        // Every index must be between 0 and list.size(), inclusive
        // 0 and list.size() are special cases
        // Indices must be monotonically increasing
        int last = 0;
        for(int y : integers)
        {
          // Catch all the error cases
          // - negative index
          // - non-monotonic sequence
          // - out of bounds
          if(y < 0 || y < last || y > list.size())
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }

          // Deal with some special cases that have the same behavior
          // - index is 0
          // - duplicate indices
          // In both cases, insert nil into the results
          if(y == 0 || y == last)
          {
            results.insert(results.end(), WordArray::nil());
          }
          else // y > last and is between 1 and list.size(), inclusive
          {
            // Special case: y is list.size()
            // Due to the monotonicly increasing requirement, future y must be
            // list.size() also or out of bounds
            // The duplicate index check above means that this is the first time
            // that y has been list.size()
            if(y == list.size())
            {
              // Capture the rest of the list that wasn't in any previous slice
              ints slice = ints(list.begin() + last, list.end());
              results.insert(results.end(), WordArray::make(slice, NounType::LIST));

              // Also insert a nil
              results.insert(results.end(), WordArray::nil());
            }
            else if(last == 0) // slice list[last:y]
            {
              ints slice = ints(list.begin() + last, list.begin() + y);
              results.insert(results.end(), WordArray::make(slice, NounType::LIST));
            }
          }

          last = y;
        }

        // We never had an index where y was list.size()
        // So we need to capture the rest of the list that wasn't in any previous slice
        // If y had been list.size(), this would have happened above
        if(last < list.size())
        {
          ints slice = ints(list.begin() + last, list.end());
          results.insert(results.end(), WordArray::make(slice, NounType::LIST));
        }

        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats list = std::get<floats>(i.i);

      // Indices are non-empty, so source list must also be non-empty
      if(!list.empty())
      {
        mixed results = mixed();

        // Every index must be between 0 and list.size(), inclusive
        // 0 and list.size() are special cases
        // Indices must be monotonically increasing
        int last = 0;
        for(int y : integers)
        {
          // Catch all the error cases
          // - negative index
          // - non-monotonic sequence
          // - out of bounds
          if(y < 0 || y < last || y > list.size())
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }

          // Deal with some special cases that have the same behavior
          // - index is 0
          // - duplicate indices
          // In both cases, insert nil into the results
          if(y == 0 || y == last)
          {
            results.insert(results.end(), WordArray::nil());
          }
          else // y > last and is between 1 and list.size(), inclusive
          {
            // Special case: y is list.size()
            // Due to the monotonicly increasing requirement, future y must be
            // list.size() also or out of bounds
            // The duplicate index check above means that this is the first time
            // that y has been list.size()
            if(y == list.size())
            {
              // Capture the rest of the list that wasn't in any previous slice
              floats slice = floats(list.begin() + last, list.end());
              results.insert(results.end(), FloatArray::make(slice, NounType::LIST));

              // Also insert a nil
              results.insert(results.end(), WordArray::nil());
            }
            else if(last == 0) // slice list[last:y]
            {
              floats slice = floats(list.begin() + last, list.begin() + y);
              results.insert(results.end(), FloatArray::make(slice, NounType::LIST));
            }
          }

          last = y;
        }

        // We never had an index where y was list.size()
        // So we need to capture the rest of the list that wasn't in any previous slice
        // If y had been list.size(), this would have happened above
        if(last < list.size())
        {
          ints slice = ints(list.begin() + last, list.end());
          results.insert(results.end(), WordArray::make(slice, NounType::LIST));
        }

        return MixedArray::make(results, NounType::LIST);
      }
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed list = std::get<mixed>(i.i);

      // Indices are non-empty, so source list must also be non-empty
      if(!list.empty())
      {
        mixed results = mixed();

        // Every index must be between 0 and list.size(), inclusive
        // 0 and list.size() are special cases
        // Indices must be monotonically increasing
        int last = 0;
        for(int y : integers)
        {
          // Catch all the error cases
          // - negative index
          // - non-monotonic sequence
          // - out of bounds
          if(y < 0 || y < last || y > list.size())
          {
            return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
          }

          // Deal with some special cases that have the same behavior
          // - index is 0
          // - duplicate indices
          // In both cases, insert nil into the results
          if(y == 0 || y == last)
          {
            results.insert(results.end(), WordArray::nil());
          }
          else // y > last and is between 1 and list.size(), inclusive
          {
            // Special case: y is list.size()
            // Due to the monotonicly increasing requirement, future y must be
            // list.size() also or out of bounds
            // The duplicate index check above means that this is the first time
            // that y has been list.size()
            if(y == list.size())
            {
              // Capture the rest of the list that wasn't in any previous slice
              mixed slice = mixed(list.begin() + last, list.end());
              results.insert(results.end(), MixedArray::make(slice, NounType::LIST));

              // Also insert a nil
              results.insert(results.end(), WordArray::nil());
            }
            else if(last == 0) // slice list[last:y]
            {
              mixed slice = mixed(list.begin() + last, list.begin() + y);
              results.insert(results.end(), MixedArray::make(slice, NounType::LIST));
            }
          }

          last = y;
        }

        // We never had an index where y was list.size()
        // So we need to capture the rest of the list that wasn't in any previous slice
        // If y had been list.size(), this would have happened above
        if(last < list.size())
        {
          mixed slice = mixed(list.begin() + last, list.end());
          results.insert(results.end(), MixedArray::make(slice, NounType::LIST));
        }

        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_integer(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      floats results = floats();
      for(int y : iis)
      {
        float fy = static_cast<float>(y);
        float fxi = static_cast<float>(xi);
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      float fxi = static_cast<float>(xi);

      floats results = floats();
      for(float fy : fis)
      {
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }    
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed mis = std::get<mixed>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      float fxi = static_cast<float>(xi);

      floats results = floats();
      for(Storage y : mis)
      {
        Storage result = divide(y, Float::make(fxi, NounType::REAL));
        if(std::holds_alternative<float>(result.i))
        {
          float fr = std::get<float>(result.i);
          results.insert(results.end(), fr);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }       
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_real(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      if(xi < Float::tolerance)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      floats results = floats();
      for(int y : iis)
      {
        float fy = static_cast<float>(y);
        float fxi = static_cast<float>(xi);
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fis = std::get<floats>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float fxi = std::get<float>(x.i);

      if(fxi < Float::tolerance)
      {
        return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
      }

      floats results = floats();
      for(float fy : fis)
      {
        results.insert(results.end(), fy / fxi);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed mis = std::get<mixed>(i.i);

    mixed results = mixed();

    for(Storage y : mis)
    {
      Storage result = divide(y, x);
      if(result.o == NounType::ERROR)
      {
        return result;
      }

      results.push_back(result);
    }

    return MixedArray::make(results, NounType::LIST);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_integers(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      for(int index = 0; index < iis.size(); index++)
      {
        if(xis[index] == 0)
        {
          return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
        }

        float fi = static_cast<float>(iis[index]);
        float fx = static_cast<float>(xis[index]);

        float result = fi / fx;
        results.push_back(result);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      for(int index = 0; index < iis.size(); index++)
      {
        if(xis[index] == 0)
        {
          return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
        }

        float fi = iis[index];
        float fx = static_cast<float>(xis[index]);

        float result = fi / fx;
        results.push_back(result);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < iis.size(); index++)
      {
        if(xis[index] == 0)
        {
          return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
        }

        Storage si = iis[index];
        Storage sx = Word::make(xis[index], NounType::INTEGER);

        Storage result = divide(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_reals(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      for(int index = 0; index < iis.size(); index++)
      {
        if(xis[index] < Float::tolerance)
        {
          return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
        }

        float fi = static_cast<float>(iis[index]);
        float fx = xis[index];

        float result = fi / fx;
        results.push_back(result);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();
      for(int index = 0; index < iis.size(); index++)
      {
        if(xis[index] < Float::tolerance)
        {
          return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
        }

        float fi = iis[index];
        float fx = xis[index];

        float result = fi / fx;
        results.push_back(result);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < iis.size(); index++)
      {
        if(xis[index] < Float::tolerance)
        {
          return Word::make(DIVISION_BY_ZERO, NounType::ERROR);
        }

        Storage si = iis[index];
        Storage sx = Float::make(xis[index], NounType::REAL);

        Storage result = divide(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::divide_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = xis[index];

        Storage result = divide(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Float::make(iis[index], NounType::REAL);
        Storage sx = xis[index];

        Storage result = divide(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();
      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];

        Storage result = divide(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// FIXME - drop for strings
Storage List::drop_impl(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        ints results(iis.begin() + xi, iis.end());
        return WordArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        ints results(iis.begin(), iis.end() - xi);
        return WordArray::make(results, NounType::LIST);
      }
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        floats results(iis.begin() + xi, iis.end());
        return FloatArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        floats results(iis.begin(), iis.end() - xi);
        return FloatArray::make(results, NounType::LIST);
      }
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi == 0)
      {
        return i;
      }

      if(xi > 0)
      {
        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        mixed results(iis.begin() + xi, iis.end());
        return MixedArray::make(results, NounType::LIST);
      }
      else // x < 0
      {
        xi = -xi;

        if(xi >= iis.size())
        {
          return WordArray::nil();
        }

        mixed results(iis.begin(), iis.end() - xi);
        return MixedArray::make(results, NounType::LIST);
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::equal_impl(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        results.insert(results.end(), iis[index] == xis[index]);
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::find_impl(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = Word::make(xi, NounType::INTEGER);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }
      
      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<float>(x.i))
    {
      float fx = std::get<float>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = Float::make(fx, NounType::REAL);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }
      
      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis.empty())
        {
          results.push_back(index + 1);
          continue;
        }

        int found = true;
        for(int xindex = 0; xindex < xis.size(); xindex++)
        {
          int offset = index + xindex;
          if(offset >= iis.size())
          {
            found = false;
            break;
          }

          Storage si = Word::make(iis[offset], NounType::INTEGER);
          Storage sx = Word::make(xis[xindex], NounType::INTEGER);
          Storage matched = match(si, sx);
          if(matched.o == NounType::ERROR)
          {
            return matched;
          }

          if(!matched.truth())
          {
            found = false;
            break;
          }
        }

        if(found)
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis.empty())
        {
          results.push_back(index + 1);
          continue;
        }

        int found = true;
        for(int xindex = 0; xindex < xis.size(); xindex++)
        {
          int offset = index + xindex;
          if(offset >= iis.size())
          {
            found = false;
            break;
          }

          Storage si = Float::make(iis[offset], NounType::REAL);
          Storage sx = Float::make(xis[xindex], NounType::REAL);
          Storage matched = match(si, sx);
          if(matched.o == NounType::ERROR)
          {
            return matched;
          }

          if(!matched.truth())
          {
            found = false;
            break;
          }
        }

        if(found)
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis.empty())
        {
          results.push_back(index + 1);
          continue;
        }

        int found = true;
        for(int xindex = 0; xindex < xis.size(); xindex++)
        {
          int offset = index + xindex;
          if(offset >= iis.size())
          {
            found = false;
            break;
          }

          Storage si = Word::make(iis[offset], NounType::INTEGER);
          Storage sx = xis[xindex];
          Storage matched = match(si, sx);
          if(matched.o == NounType::ERROR)
          {
            return matched;
          }

          if(!matched.truth())
          {
            found = false;
            break;
          }
        }

        if(found)
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);
      Storage sx = Word::make(xi, NounType::INTEGER);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Float::make(iis[index], NounType::REAL);

        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }
      
      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Float::make(iis[index], NounType::REAL);
        Storage sx = Float::make(xi, NounType::REAL);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }
      
      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis.empty())
        {
          results.push_back(index + 1);
          continue;
        }

        int found = true;
        for(int xindex = 0; xindex < xis.size(); xindex++)
        {
          int offset = index + xindex;
          if(offset >= iis.size())
          {
            found = false;
            break;
          }

          Storage si = Float::make(iis[offset], NounType::REAL);
          Storage sx = Word::make(xis[xindex], NounType::INTEGER);
          Storage matched = match(si, sx);
          if(matched.o == NounType::ERROR)
          {
            return matched;
          }

          if(!matched.truth())
          {
            found = false;
            break;
          }
        }

        if(found)
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis.empty())
        {
          results.push_back(index + 1);
          continue;
        }

        int found = true;
        for(int xindex = 0; xindex < xis.size(); xindex++)
        {
          int offset = index + xindex;
          if(offset >= iis.size())
          {
            found = false;
            break;
          }

          Storage si = Float::make(iis[offset], NounType::REAL);
          Storage sx = Float::make(xis[xindex], NounType::REAL);
          Storage matched = match(si, sx);
          if(matched.o == NounType::ERROR)
          {
            return matched;
          }

          if(!matched.truth())
          {
            found = false;
            break;
          }
        }

        if(found)
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(i.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis.empty())
        {
          results.push_back(index + 1);
          continue;
        }

        int found = true;
        for(int xindex = 0; xindex < xis.size(); xindex++)
        {
          int offset = index + xindex;
          if(offset >= iis.size())
          {
            found = false;
            break;
          }

          Storage si = Float::make(iis[offset], NounType::REAL);
          Storage sx = xis[xindex];
          Storage matched = match(si, sx);
          if(matched.o == NounType::ERROR)
          {
            return matched;
          }

          if(!matched.truth())
          {
            found = false;
            break;
          }
        }

        if(found)
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = Word::make(xi, NounType::INTEGER);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }
      
      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = Float::make(xi, NounType::REAL);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(matched.truth())
        {
          results.push_back(index + 1);
        }
      }
      
      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis.empty())
        {
          results.push_back(index + 1);
          continue;
        }

        int found = true;
        for(int xindex = 0; xindex < xis.size(); xindex++)
        {
          int offset = index + xindex;
          if(offset >= iis.size())
          {
            found = false;
            break;
          }

          Storage si = iis[offset];
          Storage sx = Word::make(xis[xindex], NounType::INTEGER);
          Storage matched = match(si, sx);
          if(matched.o == NounType::ERROR)
          {
            return matched;
          }

          if(!matched.truth())
          {
            found = false;
            break;
          }
        }

        if(found)
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis.empty())
        {
          results.push_back(index + 1);
          continue;
        }

        int found = true;
        for(int xindex = 0; xindex < xis.size(); xindex++)
        {
          int offset = index + xindex;
          if(offset >= iis.size())
          {
            found = false;
            break;
          }

          Storage si = iis[offset];
          Storage sx = Float::make(xis[xindex], NounType::REAL);
          Storage matched = match(si, sx);
          if(matched.o == NounType::ERROR)
          {
            return matched;
          }

          if(!matched.truth())
          {
            found = false;
            break;
          }
        }

        if(found)
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        if(xis.empty())
        {
          results.push_back(index + 1);
          continue;
        }

        int found = true;
        for(int xindex = 0; xindex < xis.size(); xindex++)
        {
          int offset = index + xindex;
          if(offset >= iis.size())
          {
            found = false;
            break;
          }

          Storage si = iis[offset];
          Storage sx = xis[xindex];
          Storage matched = match(si, sx);
          if(matched.o == NounType::ERROR)
          {
            return matched;
          }

          if(!matched.truth())
          {
            found = false;
            break;
          }
        }

        if(found)
        {
          results.push_back(index + 1);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::index_impl(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= iis.size())
      {
        int result = iis[xi - 1];
        return Word::make(result, NounType::INTEGER);
      }
      else
      {
        return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();
      for(int xi : xis)
      {
        if(xi > 0 && xi <= iis.size())
        {
          int result = iis[xi - 1];
          results.push_back(result);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }

      return WordArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= iis.size())
      {
        float result = iis[xi - 1];
        return Float::make(result, NounType::REAL);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      floats results = floats();
      for(int xi : xis)
      {
        if(xi > 0 && xi <= iis.size())
        {
          float result = iis[xi - 1];
          results.push_back(result);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= iis.size())
      {
        return iis[xi - 1];
      }
      else
      {
        return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();
      for(int xi : xis)
      {
        if(xi > 0 && xi <= iis.size())
        {
          results.push_back(iis[xi - 1]);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Join
Storage List::append_integer(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results(iis);
      results.push_back(xi);

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::append_real(Storage i, Storage x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      floats results(iis);
      results.push_back(xi);

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::prepend_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results(xis);
      results.insert(results.begin(), ii);

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::prepend_real(Storage i, Storage x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<float>(x.i))
    {
      float xi = std::get<float>(x.i);

      floats results(iis);
      results.insert(results.begin(), xi);

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_integers(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results(iis);

      for(int y : xis)
      {
        results.push_back(y);
      }

      return WordArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_integers_reals(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      mixed results = mixed();

      for(int y : iis)
      {
        results.push_back(Word::make(y, NounType::INTEGER));
      }

      for(float y : xis)
      {
        results.push_back(Float::make(y, NounType::REAL));
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_reals(Storage i, Storage x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      floats results(iis);

      for(float y : xis)
      {
        results.push_back(y);
      }

      return FloatArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_reals_integers(Storage i, Storage x)
{
  if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      mixed results = mixed();

      for(float y : iis)
      {
        results.push_back(Float::make(y, NounType::REAL));
      }

      for(int y : xis)
      {
        results.push_back(Word::make(y, NounType::INTEGER));
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::join_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      mixed results = mixed();

      for(Storage y : iis)
      {
        results.push_back(y);
      }

      for(Storage y : xis)
      {
        results.push_back(y);
      }

      return MixedArray::make(results, NounType::LIST);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        if(y < xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      ints results = ints();

      for(int fy : iis)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(Storage sy : iis)
      {
        Storage result = less(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        if((fy < fx) && ((fx - fy ) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      ints results = ints();

      for(float fy : iis)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(Storage sy : iis)
      {
        Storage result = less(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_integers(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];
        
        if(ii < xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = less(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_reals(Storage i, Storage x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];
        
        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = less(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::less_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        if(y > xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      ints results = ints();

      for(int fy : iis)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(Storage sy : iis)
      {
        Storage result = more(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      ints results = ints();

      for(float fy : iis)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      ints results = ints();

      for(Storage sy : iis)
      {
        Storage result = more(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_integers(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];
        
        if(ii > xi)
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_reals(Storage i, Storage x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];
        
        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(1);
        }
        else
        {
          results.push_back(0);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::more_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);
          results.push_back(ri);
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return WordArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::match_impl(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        if(iis[index] != xis[index])
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        float fi = static_cast<float>(iis[index]);
        float fx = xis[index];
        if(abs(fi - fx) >= Float::tolerance)
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = xis[index];
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats iis = std::get<floats>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Float::make(iis[index], NounType::REAL);
        Storage sx = Word::make(xis[index], NounType::INTEGER);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = Float::make(xis[index], NounType::REAL);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = Word::make(iis[index], NounType::INTEGER);
        Storage sx = xis[index];
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed iis = std::get<mixed>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = Word::make(xis[index], NounType::INTEGER);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<floats>(x.i))
    {
      floats xis = std::get<floats>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = Float::make(xis[index], NounType::REAL);
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
    else if(std::holds_alternative<mixed>(x.i))
    {
      mixed xis = std::get<mixed>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        Storage matched = match(si, sx);
        if(matched.o == NounType::ERROR)
        {
          return matched;
        }

        if(!matched.truth())
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        if(y < xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(y);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      mixed results = mixed();

      for(int fy : iis)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Word::make(fy));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = less(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      mixed results = mixed();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        if((fy < fx) && ((fx - fy ) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Word::make(y));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        if((fy < fx) && ((fx - fy) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fy);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = less(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_integers(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];
        
        if(ii < xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(Word::make(xi));
        }
        else
        {
          results.push_back(Float::make(fi));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = less(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_reals(Storage i, Storage x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];
        
        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(Float::make(fx));
        }
        else
        {
          results.push_back(Word::make(ii));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi < fx) && ((fx - fi) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = less(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::max_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = less(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        if(y > xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(y);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      mixed results = mixed();

      for(int fy : iis)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Word::make(fy));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = more(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      mixed results = mixed();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(Word::make(y));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        if((fy > fx) && ((fy - fx) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fy);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = more(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(result.truth())
        {
          results.push_back(x);
        }
        else
        {
          results.push_back(sy);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_integers(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];
        
        if(ii > xi)
        {
          results.push_back(xi);
        }
        else
        {
          results.push_back(ii);
        }
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(Word::make(xi));
        }
        else
        {
          results.push_back(Float::make(fi));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_reals(Storage i, Storage x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];
        
        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(Float::make(fx));
        }
        else
        {
          results.push_back(Word::make(ii));
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        if((fi > fx) && ((fi - fx) > Float::tolerance))
        {
          results.push_back(fx);
        }
        else
        {
          results.push_back(fi);
        }
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(sy);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::min_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = more(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        if(std::holds_alternative<int>(result.i))
        {
          int ri = std::get<int>(result.i);

          if(ri)
          {
            results.push_back(sx);
          }
          else
          {
            results.push_back(si);
          }
        }
        else
        {
          return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
        }
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        results.push_back(y - xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      floats results = floats();

      for(int fy : iis)
      {
        results.push_back(fy - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = minus(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fy - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        results.push_back(fy - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = minus(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_integers(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        results.push_back(ii - xi);       
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        results.push_back(fi - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = minus(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_reals(Storage i, Storage x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];

        results.push_back(fi - fx);       
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        results.push_back(fi - fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::minus_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = minus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = minus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = minus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      ints results = ints();

      for(int y : iis)
      {
        results.push_back(y + xi);
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      floats results = floats();

      for(int fy : iis)
      {
        results.push_back(fy + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = plus(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        results.push_back(fy + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        results.push_back(fy + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = plus(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_integers(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      ints results = ints();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        int ii = iis[index];

        results.push_back(ii + xi);       
      }

      return WordArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        float fx = static_cast<float>(xi);

        float fi = iis[index];

        results.push_back(fi + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = plus(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_reals(Storage i, Storage x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];

        results.push_back(fi + fx);       
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        results.push_back(fi + fx);
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = more(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::plus_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = plus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = plus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = plus(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_integer(Storage i, Storage x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int xi = std::get<int>(x.i);
    float fx = static_cast<float>(xi);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);
      float fx = static_cast<float>(xi);

      floats results = floats();

      for(int fy : iis)
      {
        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = power(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_real(Storage i, Storage x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float fx = std::get<float>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      floats results = floats();

      for(int y : iis)
      {
        float fy = static_cast<float>(y);

        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      floats results = floats();

      for(float fy : iis)
      {
        results.push_back(powf(fy, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      mixed results = mixed();

      for(Storage sy : iis)
      {
        Storage result = power(sy, x);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_integers(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    ints xis = std::get<ints>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        int xi = xis[index];

        float fi = static_cast<float>(ii);
        float fx = static_cast<float>(xi);

        results.push_back(powf(fi, fx));       
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fi = iis[index];

        int xi = xis[index];
        float fx = static_cast<float>(xi);

        results.push_back(powf(fi, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int xi = xis[index];
        Storage sx = Word::make(xi);

        Storage sy = iis[index];

        Storage result = power(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_reals(Storage i, Storage x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    floats xis = std::get<floats>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        float fi = static_cast<float>(ii);

        float fx = xis[index];

        results.push_back(powf(fi, fx));       
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      floats results = floats();

      for(int index = 0; index < iis.size(); index++)
      {
        float fx = xis[index];
        float fi = iis[index];

        results.push_back(powf(fi, fx));
      }

      return FloatArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float xi = xis[index];
        Storage sx = Float::make(xi);

        Storage sy = iis[index];

        Storage result = power(sy, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage List::power_mixed(Storage i, Storage x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed xis = std::get<mixed>(x.i);

    if(std::holds_alternative<ints>(i.i))
    {
      ints iis = std::get<ints>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        int ii = iis[index];
        Storage si = Word::make(ii);

        Storage sx = xis[index];
        
        Storage result = power(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<floats>(i.i))
    {
      floats iis = std::get<floats>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        float ii = iis[index];
        Storage si = Float::make(ii);

        Storage sx = xis[index];
        
        Storage result = power(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
    else if(std::holds_alternative<mixed>(i.i))
    {
      mixed iis = std::get<mixed>(i.i);

      if(iis.size() != xis.size())
      {
        return Word::make(UNEQUAL_ARRAY_LENGTHS, NounType::ERROR);
      }

      mixed results = mixed();

      for(int index = 0; index < iis.size(); index++)
      {
        Storage si = iis[index];
        Storage sx = xis[index];
        
        Storage result = power(si, sx);
        if(result.o == NounType::ERROR)
        {
          return result;
        }

        results.push_back(result);
      }

      return MixedArray::make(results);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

maybe<Storage> List::from_bytes(bytes bs, int t) {
  switch (t) {
    case StorageType::WORD_ARRAY:
      return WordArray::from_bytes(bs, NounType::LIST);

    case StorageType::FLOAT_ARRAY:
      return FloatArray::from_bytes(bs, NounType::LIST);

    case StorageType::MIXED_ARRAY:
      return MixedArray::from_bytes(bs, NounType::LIST);

    default:
      return std::nullopt;
  }
}

maybe<bytes> List::to_bytes(Storage i) {
  // Don't include type, that is handled by Noun::to_bytes

  if (i.o != NounType::LIST) {
    return std::nullopt;
  }

  bytes result = bytes();

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      {
        if (std::holds_alternative<ints>(i.i)) {
          ints integers = std::get<ints>(i.i);
          return squeeze_ints(integers);
        } else {
          return std::nullopt;
        }
      }

    case StorageType::FLOAT_ARRAY:
      {
        if (std::holds_alternative<floats>(i.i)) {
          floats fs = std::get<floats>(i.i);
          return squeeze_floats(fs);
        } else {
          return std::nullopt;
        }
      }

    case StorageType::MIXED_ARRAY:
      {
        return MixedArray::to_bytes(i);
      }

    default:
      return std::nullopt;
  }
}

maybe<Storage> List::from_conn(ReliableConnection conn, int t) {
  switch (t) {
    case StorageType::WORD_ARRAY:
      return WordArray::from_conn(conn, NounType::LIST);

    case StorageType::FLOAT_ARRAY:
      return FloatArray::from_conn(conn, NounType::LIST);

    case StorageType::MIXED_ARRAY:
      return MixedArray::from_conn(conn, NounType::LIST);

    default:
      return std::nullopt;
  }
}

void List::to_conn(ReliableConnection conn, Storage i) {
  if (i.o != NounType::LIST) {
    return;
  }

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      {
        if (std::holds_alternative<ints>(i.i)) {
          // Always include type in to_conn implementation
          conn.write({ (byte)i.t, (byte)i.o });

          ints integers = std::get<ints>(i.i);
          bytes bs = squeeze_ints(integers);

          conn.write(bs);
        }
        return;
      }

    case StorageType::FLOAT_ARRAY:
      {
        // Always include type in to_conn implementation
        conn.write({ (byte)i.t, (byte)i.o });

        floats fs = std::get<floats>(i.i);
        bytes bs = squeeze_floats(fs);

        conn.write(bs);
      }

    case StorageType::MIXED_ARRAY:
      {
        // No need to include type here, because it is provided by MixedArray::to_conn
        MixedArray::to_conn(conn, i);
      }

    default:
      return;
  }
}

// Character
void Character::initialize() {
  // Monads
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::atom, Noun::true1);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::ichar, Storage::identity);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::enclose, Character::enclose_impl);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::first, Noun::identity);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::reverse, Noun::identity);
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::size, Character::size_impl);

  // Extension Monads
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::evaluate, Storage::identity);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::CHARACTER, Monads::evaluate, Storage::identity);

  // Dyads
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD, NounType::INTEGER, Character::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::FLOAT, NounType::REAL, Character::join_scalar);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Character::join_list);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Character::join_list);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Character::join_list);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD, NounType::CHARACTER, Character::join_character);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, Character::prepend_string);

  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD, NounType::CHARACTER, Character::match_impl);
  Noun::registerDyad(StorageType::WORD, NounType::CHARACTER, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, Noun::false2);
}

Storage Character::enclose_impl(Storage i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return WordArray::make({ integer }, NounType::STRING);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Character::size_impl(Storage i) {
  if (std::holds_alternative<int>(i.i)) {
    int integer = std::get<int>(i.i);
    return Word::make(abs(integer), NounType::INTEGER);
  } else {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads
// Join
Storage Character::join_scalar(Storage i, Storage x)
{
  mixed results = mixed({i, x});

  return MixedArray::make(results, NounType::LIST);
}

Storage Character::join_character(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results = ints({ii, xi});

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Character::join_list(Storage i, Storage x)
{
  Storage mx = Noun::mix(x);
  if(std::holds_alternative<mixed>(mx.i))
  {
    mixed results = std::get<mixed>(mx.i);
    results.insert(results.begin(), i);

    return MixedArray::make(results, NounType::LIST);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Character::prepend_string(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results(xis);
      results.insert(results.begin(), ii);

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Character::match_impl(Storage i, Storage x)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(ii == xi)
      {
        return Noun::true0();
      }
      else
      {
        return Noun::false0();
      }
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Serialization
maybe<Storage> Character::from_bytes(bytes bs, int t) {
  switch (t) {
    case StorageType::WORD:
      return Word::from_bytes(bs, NounType::CHARACTER);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Character::to_bytes(Storage i) {
  if (i.o != NounType::CHARACTER) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::WORD:
      return Word::to_bytes(i);

    case StorageType::WORD_ARRAY:
      if (std::holds_alternative<ints>(i.i)) {
        ints integers = std::get<ints>(i.i);
        return squeeze_bigint(integers);
      } else {
        return std::nullopt;
      }

    default:
      return std::nullopt;
  }
}

maybe<Storage> Character::from_conn(ReliableConnection conn, int t) {
  switch (t) {
    case StorageType::WORD:
      return Word::from_conn(conn, NounType::CHARACTER);

      // FIXME - add support for StorageType::WORD_ARRAY to represent grapheme clusters

    default:
      return std::nullopt;
  }
}

void Character::to_conn(ReliableConnection conn, Storage i) {
  if (i.o != NounType::CHARACTER) {
    return;
  }

  switch (i.t) {
    case StorageType::WORD:
      {
        // No need to include type here because it is provided by Word::to_conn
        return Word::to_conn(conn, i);
      }

    case StorageType::WORD_ARRAY:
      {
        if (std::holds_alternative<ints>(i.i)) {
          ints integers = std::get<ints>(i.i);
          bytes intBytes = squeeze_bigint(integers);

          // Note that we always send NounType::INTEGERs and StorageType::WORDs, even if we internally represent them as StorageType::WORD_ARRAYs.
          conn.write({ (byte)StorageType::WORD, (byte)i.o });
          conn.write(intBytes);
        } else {
          return;
        }
      }

    default:
      return;
  }
}

// String
void IotaString::initialize() {
  // Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::atom, IotaString::atom_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::enclose, Noun::enclose_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::first, IotaString::first_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::gradeDown, IotaString::gradeDown_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::gradeUp, IotaString::gradeUp_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::reverse, IotaString::reverse_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::size, IotaString::size_impl);

  // Extension Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::evaluate, Storage::identity);

  // Dyads
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::find, StorageType::WORD, NounType::CHARACTER, List::find_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::find, StorageType::WORD_ARRAY, NounType::STRING, List::find_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::index, StorageType::WORD, NounType::INTEGER, IotaString::index_impl);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::index, StorageType::WORD_ARRAY, NounType::LIST, IotaString::index_impl);

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD, NounType::INTEGER, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::FLOAT, NounType::REAL, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD_ARRAY, NounType::LIST, Noun::join_mix_right);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::MIXED_ARRAY, NounType::LIST, Noun::join_scalar);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD, NounType::CHARACTER, IotaString::append_character);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::join, StorageType::WORD_ARRAY, NounType::STRING, IotaString::join_string);  

  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD, NounType::INTEGER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::FLOAT, NounType::REAL, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::FLOAT_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::MIXED_ARRAY, NounType::LIST, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD, NounType::CHARACTER, Noun::false2);
  Noun::registerDyad(StorageType::WORD_ARRAY, NounType::STRING, Dyads::match, StorageType::WORD_ARRAY, NounType::STRING, IotaString::match_impl);
}

Storage IotaString::atom_impl(Storage i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints chars = std::get<ints>(i.i);

    if (chars.empty())
    {
      return Noun::true0();
    }
    else
    {
      return Noun::false0();
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::first_impl(Storage i)
{
  if (std::holds_alternative<ints>(i.i))
  {
    ints chars = std::get<ints>(i.i);

    if (chars.empty())
    {
      return Word::make(EMPTY, NounType::ERROR);
    }

    int c = chars.front();

    return Word::make(c, NounType::CHARACTER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::gradeDown_impl(Storage i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());
    
    for (int index = 0; index < results.size(); ++index)
    {
      results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](int x, int y)
    {
      return integers[x] > integers[y];
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::gradeUp_impl(Storage i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers.size());
    
    for (int index = 0; index < results.size(); ++index)
    {
      results[index] = index;
    }

    std::sort(results.begin(), results.end(), [&integers](int x, int y)
    {
      return integers[x] > integers[y];
    });

    for (int index = 0; index < results.size(); ++index)
    {
        results[index] = results[index] + 1;
    }

    return WordArray::make(results, NounType::LIST);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::reverse_impl(Storage i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return i;
    }

    ints results(integers);
    std::reverse(results.begin(), results.end());
    
    return WordArray::make(results, NounType::STRING);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage IotaString::size_impl(Storage i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);

    int result = static_cast<int>(integers.size());
    
    return Word::make(result, NounType::INTEGER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Dyads
Storage IotaString::index_impl(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      if(xi > 0 && xi <= iis.size())
      {
        int result = iis[xi - 1];
        return Word::make(result, NounType::CHARACTER);
      }
      else
      {
        return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
      }
    }
    else if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results = ints();
      for(int xi : xis)
      {
        if(xi > 0 && xi <= iis.size())
        {
          int result = iis[xi - 1];
          results.push_back(result);
        }
        else
        {
          return Word::make(OUT_OF_BOUNDS, NounType::ERROR);
        }
      }

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Join
Storage IotaString::append_character(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<int>(x.i))
    {
      int xi = std::get<int>(x.i);

      ints results(iis);
      results.insert(results.end(), xi);

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::join_string(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      ints results(iis);
      results.insert(results.end(), xis.begin(), xis.end());

      return WordArray::make(results, NounType::STRING);
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage IotaString::match_impl(Storage i, Storage x)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints iis = std::get<ints>(i.i);

    if(std::holds_alternative<ints>(x.i))
    {
      ints xis = std::get<ints>(x.i);

      if(iis.size() != xis.size())
      {
        return Noun::false0();
      }

      for(int index = 0; index < iis.size(); index++)
      {
        if(iis[index] != xis[index])
        {
          return Noun::false0();
        }
      }

      return Noun::true0();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

// Serialization
maybe<Storage> IotaString::from_bytes(bytes bs, int t) {
  switch (t) {
    case StorageType::WORD_ARRAY:
      return WordArray::from_bytes(bs, NounType::STRING);

    default:
      return std::nullopt;
  }
}

maybe<bytes> IotaString::to_bytes(Storage i) {
  if (i.o != NounType::STRING) {
    return std::nullopt;
  }

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      return WordArray::to_bytes(i);

    default:
      return std::nullopt;
  }
}

maybe<Storage> IotaString::from_conn(ReliableConnection conn, int t) {
  switch (t)
  {
    case StorageType::WORD_ARRAY:
      return WordArray::from_conn(conn, NounType::STRING);

    default:
      return std::nullopt;
  }
}

void IotaString::to_conn(ReliableConnection conn, Storage i) {
  if (i.o != NounType::STRING) {
    return;
  }

  switch (i.t) {
    case StorageType::WORD_ARRAY:
      {
        // No need to include type here because it is provided by Word::to_conn
        return WordArray::to_conn(conn, i);
      }

    default:
      return;
  }
}

// Expression
void Expression::initialize() {
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::EXPRESSION, Monads::evaluate, Noun::evaluate_expression);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::EXPRESSION, Monads::truth, Expression::truth);

  /* FIXME
  Dyads.applyMonad: {
      (NounType.BUILTIN_MONAD, StorageType.StorageType::WORD): Storage.applyMonad_expression,
      (NounType.USER_MONAD, StorageType.StorageType::MIXED_ARRAY): Storage.applyMonad_expression,
  },

  Triads.applyDyad: {
      (NounType.BUILTIN_DYAD, StorageType.StorageType::WORD): Storage.applyDyad_expression,
      (NounType.USER_DYAD, StorageType.StorageType::MIXED_ARRAY): Storage.applyDyad_expression,
  },
  */
}

Storage Expression::truth(Storage i) {
  return truth(evaluate(i));
}

// MixedArray
// Note: MixedArray is defined in noun.h because it needs access to the Noun serialization API
// Storage::from_bytes decodes a byte array into a MixedArray object
maybe<Storage> MixedArray::from_bytes(bytes x, int o) {
  return maybe<Storage>(Storage(0, StorageType::WORD, 0));
}

// Encodes a MixedArray into a byte array
// Format: {(size x) squeeze) join x} (i each {x to_bytes} over join)
maybe<bytes> MixedArray::to_bytes(Storage x) {
  if (std::holds_alternative<mixed>(x.i)) {
    mixed i = std::get<mixed>(x.i);

    bytes r = bytes();

    int size = i.size();
    bytes sizeBytes = squeeze_int(size);

    r.insert(r.begin(), sizeBytes.begin(), sizeBytes.end());

    for (Storage y : i) {
      bytes valueBytes = Noun::to_bytes(y);
      r.insert(r.end(), valueBytes.begin(), valueBytes.end());
    }

    return maybe<bytes>(r);
  } else {
    return std::nullopt;
  }
}

maybe<Storage> MixedArray::from_conn(ReliableConnection conn, int o) {
  varint varsize = expand_conn(conn);
  if (std::holds_alternative<int>(varsize)) {
    int size = std::get<int>(varsize);

    mixed i = mixed();

    for (int y = 0; y < size; y++) {
      maybe<Storage> maybeStorage = Noun::from_conn(conn);

      if (maybeStorage) {
        i.push_back(*maybeStorage);
      } else {
        return std::nullopt;
      }
    }

    return MixedArray::make(i, o);
  } else {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void MixedArray::to_conn(ReliableConnection conn, Storage x) {
  if (std::holds_alternative<mixed>(x.i)) {
    mixed i = std::get<mixed>(x.i);

    // Always include type in to_conn implementation
    conn.write({ (byte)x.t, (byte)x.o });

    int length = i.size();
    bytes lengthBytes = squeeze_int(length);

    conn.write(lengthBytes);

    for (Storage y : i) {
      Noun::to_conn(conn, y);
    }
  }
}

Storage MixedArray::make(mixed x, int o) {
  return Storage(o, StorageType::MIXED_ARRAY, x);
}