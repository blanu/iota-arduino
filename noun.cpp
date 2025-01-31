#include <variant>
#include "noun.h"
#include "squeeze.h"
#include "symbols.h"
#include "error.h"
#include "debug.h"

// Verbs
// Monads
Storage negate(Storage i)
{
  return Noun::dispatchMonad(i, Word::make(Monads::negate, NounType::BUILTIN_MONAD));
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

std::map<Specialization3, Monad> Noun::monads;
std::map<Specialization5, Dyad> Noun::dyads;
std::map<Specialization5, Triad> Noun::triads;
std::map<Specialization3, MonadicAdverb> Noun::monadicAdverbs;
std::map<Specialization5, DyadicAdverb> Noun::dyadicAdverbs;

void Noun::initialize()
{
  Integer::initialize();
  Real::initialize();
  List::initialize();
  Character::initialize();
  IotaString::initialize();
  Expression::initialize();
}

// Dispatch
Storage Noun::dispatchMonad(Storage i, Storage f)
{
  if(i.o == NounType::ERROR)
  {
    return i;
  }

  if(f.t != StorageType::WORD)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization3 specialization = Specialization3(i.t, i.o, fi);
  if (monads.find(specialization) == monads.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  Monad verb = monads[specialization];
  return verb(i);
}

Storage Noun::dispatchDyad(Storage i, Storage f, Storage x)
{
  if(i.o == NounType::ERROR)
  {
    return i;
  }

  if(x.o == NounType::ERROR)
  {
    return x;
  }

  if(f.t != StorageType::WORD)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (dyads.find(specialization) == dyads.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  Dyad verb = dyads[specialization];
  return verb(i, x);
}

Storage Noun::dispatchTriad(Storage i, Storage f, Storage x, Storage y)
{
  if(i.o == NounType::ERROR)
  {
    return i;
  }

  if(x.o == NounType::ERROR)
  {
    return x;
  }

  if(f.t != StorageType::WORD)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (triads.find(specialization) == triads.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  Triad verb = triads[specialization];
  return verb(i, x, y);
}

Storage Noun::dispatchMonadicAdverb(Storage i, Storage f, Storage g)
{
  if(i.o == NounType::ERROR)
  {
    return i;
  }

  if(f.t != StorageType::WORD)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization3 specialization = Specialization3(i.t, i.o, fi);
  if (monadicAdverbs.find(specialization) == monadicAdverbs.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  MonadicAdverb adverb = monadicAdverbs[specialization];
  return adverb(i, g);
}

Storage Noun::dispatchDyadicAdverb(Storage i, Storage f, Storage g, Storage x)
{
  if(i.o == NounType::ERROR)
  {
    return i;
  }

  if(x.o == NounType::ERROR)
  {
    return x;
  }

  if(f.t != StorageType::WORD)
  {
    return Word::make(BAD_OPERATION, NounType::ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (dyadicAdverbs.find(specialization) == dyadicAdverbs.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }

  DyadicAdverb adverb = dyadicAdverbs[specialization];
  return adverb(i, g, x);
}

// Registration

void Noun::registerMonad(Symbol it, Symbol io, Symbol f, Storage (*m)(Storage))
{
  Noun::monads[Specialization3(it, io, f)] = m;
}

void Noun::registerDyad(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*d)(Storage, Storage))
{
  Noun::dyads[Specialization5(it, io, f, xt, xo)] = d;
}

void Noun::registerTriad(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*t)(Storage, Storage, Storage))
{
  Noun::triads[Specialization5(it, io, f, xt, xo)] = t;
}

void Noun::registerMonadicAdverb(Symbol it, Symbol io, Symbol f, Storage (*a)(Storage, Storage))
{
  Noun::monadicAdverbs[Specialization3(it, io, f)] = a;
}

void Noun::registerDyadicAdverb(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*a)(Storage, Storage, Storage))
{
  Noun::dyadicAdverbs[Specialization5(it, io, f, xt, xo)] = a;
}

// Monads - Implementations
Storage Noun::true_impl(Storage i)
{
  return Word::make(1, NounType::INTEGER);
}

Storage Noun::false_impl(Storage i)
{
  return Word::make(0, NounType::INTEGER);
}

// Extension Monads - Implementations
Storage Noun::evaluate_expression(Storage e)
{
  if(std::holds_alternative<mixed>(e.i))
  {
    mixed items = std::get<mixed>(e.i);

    if(items.empty())
    {
      return e;
    }

    Storage i = items[0];

    if(items.size() == 1)
    {
      return i;
    }

    Storage f = items[1];

    mixed rest(items.begin() + 2, items.end());

    switch(f.o)
    {
      case NounType::BUILTIN_MONAD:
      {
        Storage result = Noun::dispatchMonad(i, f);
        if(rest.empty())
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
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Serialization
// Noun::from_bytes decodes a byte array into a Storage object by delegating to each Storage subclass's decoder
maybe<Storage> Noun::from_bytes(bytes x)
{
  int t = (int)x.at(0);
  int o = (int)x.at(1);
  bytes untypedData(x.begin() + 2, x.end());

  switch(o)
  {
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
      switch(t)
      {
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
bytes Noun::to_bytes(Storage x)
{
  // Noun::to_bytes includes type, never include type in any other to_bytes
  bytes typeBytes = {(byte)x.t, (byte)x.o};

  bytes valueBytes = bytes();
  switch(x.o)
  {
    case NounType::INTEGER:
    {
      maybe<bytes> maybeValueBytes = Integer::to_bytes(x);
      if(maybeValueBytes)
      {
        valueBytes = *maybeValueBytes;
        break;
      }
      else
      {
        return bytes();
      }
    }

    case NounType::REAL:
    {
      maybe<bytes> maybeValueBytes = Real::to_bytes(x);
      if(maybeValueBytes)
      {
        valueBytes = *maybeValueBytes;
        break;
      }
      else
      {
        return bytes();
      }
    }

    case NounType::LIST:
    {
      maybe<bytes> maybeValueBytes = List::to_bytes(x);
      if(maybeValueBytes)
      {
        valueBytes = *maybeValueBytes;
        break;
      }
      else
      {
        return bytes();
      }
    }

    case NounType::CHARACTER:
    {
      maybe<bytes> maybeValueBytes = Character::to_bytes(x);
      if(maybeValueBytes)
      {
        valueBytes = *maybeValueBytes;
        break;
      }
      else
      {
        return bytes();
      }
    }

    case NounType::STRING:
    {
      maybe<bytes> maybeValueBytes = IotaString::to_bytes(x);
      if(maybeValueBytes)
      {
        valueBytes = *maybeValueBytes;
        break;
      }
      else
      {
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

maybe<Storage> Noun::from_conn(ReliableConnection conn)
{
  int storageType = (int)conn.readOne();
  int objectType = (int)conn.readOne();

  switch(objectType)
  {
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
      switch(storageType)
      {
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

void Noun::to_conn(ReliableConnection conn, Storage x)
{
  // Storage.to_conn does not include type information, always include it in the specific to_conn implementation
  switch(x.o)
  {
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
      switch(x.t)
      {
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

void Integer::initialize()
{
  // Monads
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::atom, Noun::true_impl);  
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::ichar, Integer::char_impl);  
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::negate, Integer::negate_impl);  

  // Extension Monads
  Noun::registerMonad(StorageType::WORD, NounType::INTEGER, Monads::evaluate, Storage::identity);  

  // Extension Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::INTEGER, Monads::evaluate, Storage::identity);  
}

// Monads
Storage Integer::negate_impl(Storage i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);
    return Word::make(-integer, NounType::INTEGER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

Storage Integer::char_impl(Storage i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int integer = std::get<int>(i.i);
    return Word::make(integer, NounType::CHARACTER);
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

// Serialization
maybe<Storage> Integer::from_bytes(bytes bs, int t)
{
  switch(t)
  {
    case StorageType::WORD:
      return Word::from_bytes(bs, NounType::INTEGER);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Integer::to_bytes(Storage i)
{
  if(i.o != NounType::INTEGER)
  {
    return std::nullopt;
  }
  
  switch(i.t)
  {
    case StorageType::WORD:
      return Word::to_bytes(i);

    case StorageType::WORD_ARRAY:
      if(std::holds_alternative<ints>(i.i))
      {
        ints integers = std::get<ints>(i.i);
        return squeeze_bigint(integers);
      }
      else
      {
        return std::nullopt;
      }
      
    default:
      return std::nullopt;
  }
}

maybe<Storage> Integer::from_conn(ReliableConnection conn, int t)
{
  switch(t)
  {
    case NounType::INTEGER:
      return Word::from_conn(conn, NounType::INTEGER);

    default:
      return std::nullopt;
  }  
}

void Integer::to_conn(ReliableConnection conn, Storage i)
{
  if(i.o != NounType::INTEGER)
  {
    return;
  }

  switch(i.t)
  {
    case StorageType::WORD:
    {
      // No need to include type here because it is provided by Word::to_conn
      return Word::to_conn(conn, i);
    }

    case StorageType::WORD_ARRAY:
    {
      if(std::holds_alternative<ints>(i.i))
      {
        ints integers = std::get<ints>(i.i);
        bytes intBytes = squeeze_bigint(integers);

        // Note that we always send NounType::INTEGERs and StorageType::WORDs, even if we internally represent them as StorageType::WORD_ARRAYs.
        conn.write({(byte)StorageType::WORD, (byte)i.o});
        conn.write(intBytes);
      }
      else
      {
        return;
      }
    }
 
    default:
      return;
  }
}

// Real
// Registration
void Real::initialize()
{
  // Monads
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::atom, Noun::true_impl);  

  // Extension Monads
  Noun::registerMonad(StorageType::FLOAT, NounType::REAL, Monads::evaluate, Storage::identity);  
}

// Serialization
maybe<Storage> Real::from_bytes(bytes bs, int t)
{
  switch(t)
  {
    case StorageType::FLOAT:
      return Float::from_bytes(bs, NounType::REAL);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Real::to_bytes(Storage i)
{
  if(i.o != NounType::REAL)
  {
    return std::nullopt;
  }
  
  switch(i.t)
  {
    case StorageType::FLOAT:
      return Float::to_bytes(i);
      
    default:
      return std::nullopt;
  }
}

maybe<Storage> Real::from_conn(ReliableConnection conn, int t)
{
  switch(t)
  {
    case StorageType::FLOAT:
      return Float::from_conn(conn, NounType::REAL);

    default:
      return std::nullopt;
  }  
}

void Real::to_conn(ReliableConnection conn, Storage i)
{
  if(i.o != NounType::REAL)
  {
    return;
  }

  switch(i.t)
  {
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
void List::initialize()
{
  // WordArray
  // Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);

  // Extension Monads
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::LIST, Monads::evaluate, Storage::identity);  

  // FloatArray
  // Monads
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);

  // Extension Monads
  Noun::registerMonad(StorageType::FLOAT_ARRAY, NounType::LIST, Monads::evaluate, Storage::identity);  

  // MixedArray
  // Monads
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::atom, List::atom_impl);
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::ichar, List::char_impl);
  
  // Extension Monads
  Noun::registerMonad(StorageType::MIXED_ARRAY, NounType::LIST, Monads::evaluate, Storage::identity);  
}

Storage List::atom_impl(Storage i)
{
  if(std::holds_alternative<ints>(i.i))
  {
    ints integers = std::get<ints>(i.i);
    if(integers.empty())
    {
      return Noun::true_impl(i);
    }
    else
    {
      return Noun::false_impl(i);
    }
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);
    if(fs.empty())
    {
      return Noun::true_impl(i);
    }
    else
    {
      return Noun::false_impl(i);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);
    if(ms.empty())
    {
      return Noun::true_impl(i);
    }
    else
    {
      return Noun::false_impl(i);
    }
  }
  else
  {
    return Noun::false_impl(i);
  }
}

Storage List::char_impl(Storage i)
{  
  if(std::holds_alternative<ints>(i.i))
  {  
    ints integers = std::get<ints>(i.i);

    if(integers.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }

    mixed ms = mixed();
    for(int y : integers)
    {
      ms.insert(ms.end(), Word::make(y, NounType::CHARACTER));
    }
    return MixedArray::make(ms, NounType::LIST);
  }
  else if(std::holds_alternative<floats>(i.i))
  {
    floats fs = std::get<floats>(i.i);

    if(fs.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }
    else
    {
      return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  }
  else if(std::holds_alternative<mixed>(i.i))
  {
    mixed ms = std::get<mixed>(i.i);

    if(ms.empty())
    {
      return WordArray::make(ints(), NounType::LIST);
    }
    else
    {
      return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
    }
  }
  else
  {
    return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
  }
}

maybe<Storage> List::from_bytes(bytes bs, int t)
{
  switch(t)
  {
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

maybe<bytes> List::to_bytes(Storage i)
{
  // Don't include type, that is handled by Noun::to_bytes

  if(i.o != NounType::LIST)
  {
    return std::nullopt;
  }

  bytes result = bytes();
  
  switch(i.t)
  {
    case StorageType::WORD_ARRAY:
    {
      if(std::holds_alternative<ints>(i.i))
      {
        ints integers = std::get<ints>(i.i);
        return squeeze_ints(integers);
      }
      else
      {
        return std::nullopt;
      }
    }

    case StorageType::FLOAT_ARRAY:
    {
      if(std::holds_alternative<floats>(i.i))
      {
        floats fs = std::get<floats>(i.i);
        return squeeze_floats(fs);
      }
      else
      {
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

maybe<Storage> List::from_conn(ReliableConnection conn, int t)
{
  switch(t)
  {
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

void List::to_conn(ReliableConnection conn, Storage i)
{
  if(i.o != NounType::LIST)
  {
    return;
  }
  
  switch(i.t)
  {
    case StorageType::WORD_ARRAY:
    {
     if(std::holds_alternative<ints>(i.i))
      {
        // Always include type in to_conn implementation
        conn.write({(byte)i.t, (byte)i.o});

        ints integers = std::get<ints>(i.i);
        bytes bs = squeeze_ints(integers);

        conn.write(bs);
      }
      return;
    }

    case StorageType::FLOAT_ARRAY:
    {
      // Always include type in to_conn implementation
      conn.write({(byte)i.t, (byte)i.o});

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
void Character::initialize()
{
  // Monads
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::atom, Noun::true_impl);  
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::ichar, Storage::identity);  

  // Extension Monads
  Noun::registerMonad(StorageType::WORD, NounType::CHARACTER, Monads::evaluate, Storage::identity);  
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::CHARACTER, Monads::evaluate, Storage::identity);  
}

// Serialization
maybe<Storage> Character::from_bytes(bytes bs, int t)
{
  switch(t)
  {
    case StorageType::WORD:
      return Word::from_bytes(bs, NounType::CHARACTER);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Character::to_bytes(Storage i)
{
  if(i.o != NounType::CHARACTER)
  {
    return std::nullopt;
  }
  
  switch(i.t)
  {
    case StorageType::WORD:
      return Word::to_bytes(i);

    case StorageType::WORD_ARRAY:
      if(std::holds_alternative<ints>(i.i))
      {
        ints integers = std::get<ints>(i.i);
        return squeeze_bigint(integers);
      }
      else
      {
        return std::nullopt;
      }
      
    default:
      return std::nullopt;
  }
}

maybe<Storage> Character::from_conn(ReliableConnection conn, int t)
{
  switch(t)
  {
    case StorageType::WORD:
      return Word::from_conn(conn, NounType::CHARACTER);

    // FIXME - add support for StorageType::WORD_ARRAY to represent grapheme clusters

    default:
      return std::nullopt;
  }  
}

void Character::to_conn(ReliableConnection conn, Storage i)
{
  if(i.o != NounType::CHARACTER)
  {
    return;
  }

  switch(i.t)
  {
    case StorageType::WORD:
    {
      // No need to include type here because it is provided by Word::to_conn
      return Word::to_conn(conn, i);
    }

    case StorageType::WORD_ARRAY:
    {
      if(std::holds_alternative<ints>(i.i))
      {
        ints integers = std::get<ints>(i.i);
        bytes intBytes = squeeze_bigint(integers);

        // Note that we always send NounType::INTEGERs and StorageType::WORDs, even if we internally represent them as StorageType::WORD_ARRAYs.
        conn.write({(byte)StorageType::WORD, (byte)i.o});
        conn.write(intBytes);
      }
      else
      {
        return;
      }
    }
 
    default:
      return;
  }
}

// String
void IotaString::initialize()
{
  Noun::registerMonad(StorageType::WORD_ARRAY, NounType::STRING, Monads::evaluate, Storage::identity);  
}

// Serialization
maybe<Storage> IotaString::from_bytes(bytes bs, int t)
{
  switch(t)
  {
    case StorageType::WORD_ARRAY:
      return WordArray::from_bytes(bs, NounType::STRING);

    default:
      return std::nullopt;
  }
}

maybe<bytes> IotaString::to_bytes(Storage i)
{
  if(i.o != NounType::STRING)
  {
    return std::nullopt;
  }
  
  switch(i.t)
  {
    case StorageType::WORD_ARRAY:
      return WordArray::to_bytes(i);
      
    default:
      return std::nullopt;
  }
}

maybe<Storage> IotaString::from_conn(ReliableConnection conn, int t)
{
  switch(t)
  {
    case StorageType::WORD_ARRAY:
      return WordArray::from_conn(conn, NounType::STRING);

    default:
      return std::nullopt;
  }  
}

void IotaString::to_conn(ReliableConnection conn, Storage i)
{
  if(i.o != NounType::STRING)
  {
    return;
  }

  switch(i.t)
  {
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
void Expression::initialize()
{
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

Storage Expression::truth(Storage i)
{
  return truth(evaluate(i));
}

// MixedArray
// Note: MixedArray is defined in noun.h because it needs access to the Noun serialization API
// Storage::from_bytes decodes a byte array into a MixedArray object
maybe<Storage> MixedArray::from_bytes(bytes x, int o)
{
  return maybe<Storage>(Storage(0, StorageType::WORD, 0));
}

// Encodes a MixedArray into a byte array
// Format: {(size x) squeeze) join x} (i each {x to_bytes} over join)
maybe<bytes> MixedArray::to_bytes(Storage x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed i = std::get<mixed>(x.i);

    bytes r = bytes();

    int size = i.size();
    bytes sizeBytes = squeeze_int(size);

    r.insert(r.begin(), sizeBytes.begin(), sizeBytes.end());

    for(Storage y : i)
    {
      bytes valueBytes = Noun::to_bytes(y);
      r.insert(r.end(), valueBytes.begin(), valueBytes.end());
    }

    return maybe<bytes>(r);
  }
  else
  {
    return std::nullopt;
  }
}

maybe<Storage> MixedArray::from_conn(ReliableConnection conn, int o)
{
  varint varsize = expand_conn(conn);
  if(std::holds_alternative<int>(varsize))
  {
    int size = std::get<int>(varsize);

    mixed i = mixed();

    for(int y=0; y<size; y++)
    {
      maybe<Storage> maybeStorage = Noun::from_conn(conn);
      
      if(maybeStorage)
      {
          i.push_back(*maybeStorage);
      }
      else
      {
        return std::nullopt;
      }
    }

    return MixedArray::make(i, o);
  }
  else
  {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void MixedArray::to_conn(ReliableConnection conn, Storage x)
{
  if(std::holds_alternative<mixed>(x.i))
  {
    mixed i = std::get<mixed>(x.i);

    // Always include type in to_conn implementation
    conn.write({(byte)x.t, (byte)x.o});

    int length = i.size();
    bytes lengthBytes = squeeze_int(length);

    conn.write(lengthBytes);

    for(Storage y : i)
    {
      Noun::to_conn(conn, y);
    }
  }
}

Storage MixedArray::make(mixed x, int o)
{
  return Storage(o, StorageType::MIXED_ARRAY, x);
}