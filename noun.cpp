#include <variant>
#include "noun.h"
#include "squeeze.h"
#include "symbols.h"
#include "error.h"

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
}

// Dispatch
Storage Noun::dispatchMonad(Storage i, Storage f)
{
  if(i.o == ERROR)
  {
    return i;
  }

  if(f.t != WORD)
  {
    return Word::make(BAD_OPERATION, ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization3 specialization = Specialization3(i.t, i.o, fi);
  if (monads.find(specialization) == monads.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, ERROR);
  }

  Monad verb = monads[specialization];
  return verb(i);
}

Storage Noun::dispatchDyad(Storage i, Storage f, Storage x)
{
  if(i.o == ERROR)
  {
    return i;
  }

  if(x.o == ERROR)
  {
    return x;
  }

  if(f.t != WORD)
  {
    return Word::make(BAD_OPERATION, ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (dyads.find(specialization) == dyads.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, ERROR);
  }

  Dyad verb = dyads[specialization];
  return verb(i, x);
}

Storage Noun::dispatchTriad(Storage i, Storage f, Storage x, Storage y)
{
  if(i.o == ERROR)
  {
    return i;
  }

  if(x.o == ERROR)
  {
    return x;
  }

  if(f.t != WORD)
  {
    return Word::make(BAD_OPERATION, ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (triads.find(specialization) == triads.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, ERROR);
  }

  Triad verb = triads[specialization];
  return verb(i, x, y);
}

Storage Noun::dispatchMonadicAdverb(Storage i, Storage f, Storage g)
{
  if(i.o == ERROR)
  {
    return i;
  }

  if(f.t != WORD)
  {
    return Word::make(BAD_OPERATION, ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization3 specialization = Specialization3(i.t, i.o, fi);
  if (monadicAdverbs.find(specialization) == monadicAdverbs.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, ERROR);
  }

  MonadicAdverb adverb = monadicAdverbs[specialization];
  return adverb(i, g);
}

Storage Noun::dispatchDyadicAdverb(Storage i, Storage f, Storage g, Storage x)
{
  if(i.o == ERROR)
  {
    return i;
  }

  if(x.o == ERROR)
  {
    return x;
  }

  if(f.t != WORD)
  {
    return Word::make(BAD_OPERATION, ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (dyadicAdverbs.find(specialization) == dyadicAdverbs.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, ERROR);
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

// Serialization
// Noun::from_bytes decodes a byte array into a Storage object by delegating to each Storage subclass's decoder
maybe<Storage> Noun::from_bytes(bytes x)
{
  int t = (int)x.at(0);
  int o = (int)x.at(1);
  bytes untypedData(x.begin() + 2, x.end());

  switch(o)
  {
    case INTEGER:
    {
      return maybe<Storage>(Integer::from_bytes(untypedData, o));
    }

    case REAL:
    {
      return maybe<Storage>(Real::from_bytes(untypedData, o));
    }

    case LIST:
    {
      return maybe<Storage>(List::from_bytes(untypedData, o));
    }

    case CHARACTER:
    {
      return maybe<Storage>(Character::from_bytes(untypedData, o));
    }

    case STRING:
    {
      return maybe<Storage>(IotaString::from_bytes(untypedData, o));
    }
    default:
      switch(t)
      {
        case WORD:
        {
          return maybe<Storage>(Word::from_bytes(untypedData, o)); 
        }

        case FLOAT:
        {
          return maybe<Storage>(Float::from_bytes(untypedData, o)); 
        }

        case WORD_ARRAY:
        {
          return maybe<Storage>(WordArray::from_bytes(untypedData, o)); 
        }

        case FLOAT_ARRAY:
        {
          return maybe<Storage>(FloatArray::from_bytes(untypedData, o)); 
        }

        case MIXED_ARRAY:
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
    case INTEGER:
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

    case REAL:
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

    case LIST:
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

    case CHARACTER:
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

    case STRING:
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
    case INTEGER:
      return maybe<Storage>(Integer::from_conn(conn, storageType));

    case REAL:
      return maybe<Storage>(Real::from_conn(conn, storageType));

    case LIST:
      return maybe<Storage>(List::from_conn(conn, storageType));

    case CHARACTER:
      return maybe<Storage>(Character::from_conn(conn, storageType));

    case STRING:
      return maybe<Storage>(IotaString::from_conn(conn, storageType));

    default:
      return std::nullopt;
  }
}

void Noun::to_conn(ReliableConnection conn, Storage x)
{
  // Storage.to_conn does not include type information, always include it in the specific to_conn implementation
  switch(x.o)
  {
    case INTEGER:
    {
      Integer::to_conn(conn, x);
      return;
    }

    case REAL:
    {
      Real::to_conn(conn, x);
      return;
    }

    case LIST:
    {
      List::to_conn(conn, x);
      return;
    }

    case CHARACTER:
    {
      Character::to_conn(conn, x);
      return;
    }

    case STRING:
    {
      IotaString::to_conn(conn, x);
      return;
    }

    default:
      return;
  }
}

void Integer::initialize()
{
  Noun::registerMonad(WORD, INTEGER, Monads::evaluate, Storage::identity);  
  Noun::registerMonad(WORD_ARRAY, INTEGER, Monads::evaluate, Storage::identity);  
}

// Serialization
maybe<Storage> Integer::from_bytes(bytes bs, int t)
{
  switch(t)
  {
    case WORD:
      return Word::from_bytes(bs, INTEGER);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Integer::to_bytes(Storage i)
{
  if(i.o != INTEGER)
  {
    return std::nullopt;
  }
  
  switch(i.t)
  {
    case WORD:
      return Word::to_bytes(i);

    case WORD_ARRAY:
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
    case INTEGER:
      return Word::from_conn(conn, INTEGER);

    default:
      return std::nullopt;
  }  
}

void Integer::to_conn(ReliableConnection conn, Storage i)
{
  if(i.o != INTEGER)
  {
    return;
  }

  switch(i.t)
  {
    case WORD:
    {
      // No need to include type here because it is provided by Word::to_conn
      return Word::to_conn(conn, i);
    }

    case WORD_ARRAY:
    {
      if(std::holds_alternative<ints>(i.i))
      {
        ints integers = std::get<ints>(i.i);
        bytes intBytes = squeeze_bigint(integers);

        // Note that we always send INTEGERs and WORDs, even if we internally represent them as WORD_ARRAYs.
        conn.write({(byte)WORD, (byte)i.o});
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
  Noun::registerMonad(FLOAT, REAL, Monads::evaluate, Storage::identity);  
}

// Serialization
maybe<Storage> Real::from_bytes(bytes bs, int t)
{
  switch(t)
  {
    case FLOAT:
      return Float::from_bytes(bs, REAL);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Real::to_bytes(Storage i)
{
  if(i.o != REAL)
  {
    return std::nullopt;
  }
  
  switch(i.t)
  {
    case FLOAT:
      return Float::to_bytes(i);
      
    default:
      return std::nullopt;
  }
}

maybe<Storage> Real::from_conn(ReliableConnection conn, int t)
{
  switch(t)
  {
    case FLOAT:
      return Float::from_conn(conn, REAL);

    default:
      return std::nullopt;
  }  
}

void Real::to_conn(ReliableConnection conn, Storage i)
{
  if(i.o != REAL)
  {
    return;
  }

  switch(i.t)
  {
    case FLOAT:
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
  Noun::registerMonad(WORD_ARRAY, LIST, Monads::evaluate, Storage::identity);  
  Noun::registerMonad(FLOAT_ARRAY, LIST, Monads::evaluate, Storage::identity);  
  Noun::registerMonad(MIXED_ARRAY, LIST, Monads::evaluate, Storage::identity);  
}

maybe<Storage> List::from_bytes(bytes bs, int t)
{
  switch(t)
  {
    case WORD_ARRAY:
      return WordArray::from_bytes(bs, LIST);

    case FLOAT_ARRAY:
      return FloatArray::from_bytes(bs, LIST);

    case MIXED_ARRAY:
      return MixedArray::from_bytes(bs, LIST);

    default:
      return std::nullopt;
  }
}

maybe<bytes> List::to_bytes(Storage i)
{
  // Don't include type, that is handled by Noun::to_bytes

  if(i.o != LIST)
  {
    return std::nullopt;
  }

  bytes result = bytes();
  
  switch(i.t)
  {
    case WORD_ARRAY:
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

    case FLOAT_ARRAY:
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

    case MIXED_ARRAY:
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
    case WORD_ARRAY:
      return WordArray::from_conn(conn, LIST);

    case FLOAT_ARRAY:
      return FloatArray::from_conn(conn, LIST);

    case MIXED_ARRAY:
      return MixedArray::from_conn(conn, LIST);

    default:
      return std::nullopt;
  }  
}

void List::to_conn(ReliableConnection conn, Storage i)
{
  if(i.o != LIST)
  {
    return;
  }
  
  switch(i.t)
  {
    case WORD_ARRAY:
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

    case FLOAT_ARRAY:
    {
      // Always include type in to_conn implementation
      conn.write({(byte)i.t, (byte)i.o});

      floats fs = std::get<floats>(i.i);
      bytes bs = squeeze_floats(fs);

      conn.write(bs);
    }

    case MIXED_ARRAY:
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
  Noun::registerMonad(WORD, CHARACTER, Monads::evaluate, Storage::identity);  
  Noun::registerMonad(WORD_ARRAY, CHARACTER, Monads::evaluate, Storage::identity);  
}

// Serialization
maybe<Storage> Character::from_bytes(bytes bs, int t)
{
  switch(t)
  {
    case WORD:
      return Word::from_bytes(bs, CHARACTER);

    default:
      return std::nullopt;
  }
}

maybe<bytes> Character::to_bytes(Storage i)
{
  if(i.o != CHARACTER)
  {
    return std::nullopt;
  }
  
  switch(i.t)
  {
    case WORD:
      return Word::to_bytes(i);

    case WORD_ARRAY:
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
    case WORD:
      return Word::from_conn(conn, CHARACTER);

    // FIXME - add support for WORD_ARRAY to represent grapheme clusters

    default:
      return std::nullopt;
  }  
}

void Character::to_conn(ReliableConnection conn, Storage i)
{
  if(i.o != CHARACTER)
  {
    return;
  }

  switch(i.t)
  {
    case WORD:
    {
      // No need to include type here because it is provided by Word::to_conn
      return Word::to_conn(conn, i);
    }

    case WORD_ARRAY:
    {
      if(std::holds_alternative<ints>(i.i))
      {
        ints integers = std::get<ints>(i.i);
        bytes intBytes = squeeze_bigint(integers);

        // Note that we always send INTEGERs and WORDs, even if we internally represent them as WORD_ARRAYs.
        conn.write({(byte)WORD, (byte)i.o});
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
  Noun::registerMonad(WORD_ARRAY, STRING, Monads::evaluate, Storage::identity);  
}

// Serialization
maybe<Storage> IotaString::from_bytes(bytes bs, int t)
{
  switch(t)
  {
    case WORD_ARRAY:
      return WordArray::from_bytes(bs, STRING);

    default:
      return std::nullopt;
  }
}

maybe<bytes> IotaString::to_bytes(Storage i)
{
  if(i.o != STRING)
  {
    return std::nullopt;
  }
  
  switch(i.t)
  {
    case WORD_ARRAY:
      return WordArray::to_bytes(i);
      
    default:
      return std::nullopt;
  }
}

maybe<Storage> IotaString::from_conn(ReliableConnection conn, int t)
{
  switch(t)
  {
    case WORD_ARRAY:
      return WordArray::from_conn(conn, STRING);

    default:
      return std::nullopt;
  }  
}

void IotaString::to_conn(ReliableConnection conn, Storage i)
{
  if(i.o != STRING)
  {
    return;
  }

  switch(i.t)
  {
    case WORD_ARRAY:
    {
      // No need to include type here because it is provided by Word::to_conn
      return WordArray::to_conn(conn, i);
    }
 
    default:
      return;
  }
}

// MixedArray
// Note: MixedArray is defined in noun.h because it needs access to the Noun serialization API
// Storage::from_bytes decodes a byte array into a MixedArray object
maybe<Storage> MixedArray::from_bytes(bytes x, int o)
{
  return maybe<Storage>(Storage(0, WORD, 0));
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
  return Storage(o, MIXED_ARRAY, x);
}