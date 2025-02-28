#include <Arduino.h>
#include <vector>
#include <variant>
#include <tuple>
#include <stdint.h>

#include "types.h"
#include "storage.h"
#include "squeeze.h"
#include "error.h"

bool Storage::operator==(const Storage& other) const
{
  if(o != other.o)
  {
    return 0;
  }

  if(t != other.t)
  {
    return 0;
  }

  if(std::holds_alternative<int>(i))
  {
    if(std::holds_alternative<int>(other.i))
    {
      int x = std::get<int>(i);
      int y = std::get<int>(other.i);

      return x == y;
    }
    else
    {
      return 0;
    }
  }
  else if (std::holds_alternative<float>(i))
  {
    if(std::holds_alternative<float>(other.i))
    {
      float x = std::get<float>(i);
      float y = std::get<float>(other.i);

      return x == y;
    }
    else
    {
      return 0;
    }
  }
  else if(std::holds_alternative<ints>(i))
  {
    if(std::holds_alternative<ints>(other.i))
    {
      ints xs = std::get<ints>(i);
      ints ys = std::get<ints>(other.i);

      if(xs.size() != ys.size())
      {
        return 0;
      }

      for(int index = 0; index < xs.size(); index++)
      {
        if(xs[index] != ys[index])
        {
          return 0;
        }
      }

      return 1;
    }
    else
    {
      return 0;
    }
  }
  else if(std::holds_alternative<floats>(i))
  {
    if(std::holds_alternative<floats>(other.i))
    {
      floats xs = std::get<floats>(i);
      floats ys = std::get<floats>(other.i);

      if(xs.size() != ys.size())
      {
        return 0;
      }

      for(int index = 0; index < xs.size(); index++)
      {
        if(xs[index] != ys[index])
        {
          return 0;
        }
      }

      return 1;
    }
    else
    {
      return 0;
    }
  }
  else if(std::holds_alternative<mixed>(i))
  {
    if(std::holds_alternative<mixed>(other.i))
    {
      mixed xs = std::get<mixed>(i);
      mixed ys = std::get<mixed>(other.i);

      if(xs.size() != ys.size())
      {
        return 0;
      }

      for(int index = 0; index < xs.size(); index++)
      {
        if(xs[index] == ys[index])
        {
          continue;
        }
        else
        {
          return 0;
        }
      }

      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

Storage Storage::identity(Storage i)
{
  return i;
}

int Storage::truth()
{
  switch(o)
  {
    case NounType::INTEGER:
      switch(t)
      {
        case StorageType::WORD:
          if(std::holds_alternative<int>(i))
          {
            int integer = std::get<int>(i);

            return integer != 0;
          }
          else
          {
            return 0;
          }

        // FIXME - support bigints

        default:
          return 0;
      }

    default:
      return 0;
  }
}

// Word
// Storage::from_bytes decodes a byte array into a Word object
maybe<Storage> Word::from_bytes(bytes x, int o)
{
  varint varinteger = expand_int_from_bytes(x);
  if(std::holds_alternative<int>(varinteger))
  {
    int integer = std::get<int>(varinteger);
    return Word::make(integer, o);
  }
  else
  {
    // varint results for Words are not yet fully implemented
    return std::nullopt;
  }
}

// Encodes a Word into a byte array
// Format: int:i.squeeze
bytes Word::to_bytes(Storage x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int i = std::get<int>(x.i);
    bytes result = squeeze_int(i);
    return result;
  }
  else
  {
    return bytes();
  }
}

maybe<Storage> Word::from_conn(ReliableConnection conn, int o)
{
  varint varinteger = expand_conn(conn);

  if(std::holds_alternative<int>(varinteger))
  {
    int integer = std::get<int>(varinteger);
    return maybe<Storage>(Word::make(integer, o));
  }
  else
  {
    ints integers = std::get<ints>(varinteger);
    return maybe<Storage>(WordArray::make(integers, o));
  }
}

void Word::to_conn(ReliableConnection conn, Storage x)
{
  if(std::holds_alternative<int>(x.i))
  {
    // Always include type in to_conn implementation
    conn.write({(byte)x.t, (byte)x.o});

    int i = std::get<int>(x.i);
    bytes result = squeeze_int(i);

    conn.write(result);
  }
}

Storage Word::make(int x, int o)
{
  return Storage(o, StorageType::WORD, x);
}

// Float
// Storage::from_bytes decodes a byte array into a Float object
maybe<Storage> Float::from_bytes(bytes x, int o)
{
  maybe<floating> maybeFloating = expand_floating(x);

  if(maybeFloating)
  {
    float f;
    if(std::holds_alternative<float>(*maybeFloating))
    {
      f = std::get<float>(*maybeFloating);
    }
    else
    {
      double d = (float)std::get<double>(*maybeFloating);
      f = (float)d;
    }

    return maybe<Storage>(Float::make(f, o));
  }
  else
  {
    return std::nullopt;
  }
}

// Encodes a Float into a byte array
// Format: IEEE Float
maybe<bytes> Float::to_bytes(Storage x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float i = std::get<float>(x.i);

    return maybe<bytes>(squeeze_floating(floating(i)));
  }
  else
  {
    return std::nullopt;
  }
}

maybe<Storage> Float::from_conn(ReliableConnection conn, int o)
{
  maybe<floating> maybeFloating = expand_conn_floating(conn);

  if(maybeFloating)
  {
    if(std::holds_alternative<float>(*maybeFloating))
    {
      float f = std::get<float>(*maybeFloating);

      return maybe<Storage>(Float::make(f, o));
    }
    else
    {
      double d = std::get<double>(*maybeFloating);

      return maybe<Storage>(Float::make((float)d, o));
    }
  }
  else
  {
    return std::nullopt;
  }
}

void Float::to_conn(ReliableConnection conn, Storage x)
{
  if(std::holds_alternative<float>(x.i))
  {
    // Always include type in to_conn implementation
    conn.write({(byte)x.t, (byte)x.o});

    float i = std::get<float>(x.i);

    bytes result = squeeze_floating(floating(i));
    conn.write(result);
  }
}

Storage Float::make(float x, int o)
{
  return Storage(o, StorageType::FLOAT, x);
}

// WordArray
Storage WordArray::nil()
{
  return WordArray::make(ints(), NounType::LIST);
}

// Storage::from_bytes decodes a byte array into a WordArray object
maybe<Storage> WordArray::from_bytes(bytes x, int o)
{
  // FIXME
  return maybe<Storage>(Storage(0, StorageType::WORD, 0));
}

// Encodes a WordArray into a byte array
// Format: {(size x) squeeze) join x} (i each {x squeeze} over join)
bytes WordArray::to_bytes(Storage x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    bytes result = bytes();

    ints i = std::get<ints>(x.i);

    int length = i.size();
    bytes lengthBytes = squeeze_int(length);

    result.insert(result.begin(), lengthBytes.begin(), lengthBytes.end());

    for(int integer : i)
    {
      bytes integerBytes = squeeze_int(integer);
      result.insert(result.end(), integerBytes.begin(), integerBytes.end());
    }

    return result;
  }
  else
  {
    return bytes();
  }
}

maybe<Storage> WordArray::from_conn(ReliableConnection conn, int o)
{
  varint varsize = expand_conn(conn);
  if(std::holds_alternative<int>(varsize))
  {
    int size = std::get<int>(varsize);

    ints i = ints();

    for(int y=0; y<size; y++)
    {
      varint varinteger = expand_conn(conn);
      if(std::holds_alternative<int>(varinteger))
      {
        int integer = std::get<int>(varinteger);
        i.push_back(integer);
      }
      else
      {
        // Varint elemenets in Word arrays not yet supported
        return std::nullopt;
      }
    }

    return WordArray::make(i, o);
  }
  else
  {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void WordArray::to_conn(ReliableConnection conn, Storage x)
{
  if(std::holds_alternative<ints>(x.i))
  {
    // Always include type in to_conn implementation
    conn.write({(byte)x.t, (byte)x.o});

    ints i = std::get<ints>(x.i);

    int length = i.size();
    bytes lengthBytes = squeeze_int(length);

    conn.write(lengthBytes);

    for(int integer : i)
    {
      bytes integerBytes = squeeze_int(integer);
      conn.write(integerBytes);
    }
  }
}

Storage WordArray::make(ints x, int o)
{
  return Storage(o, StorageType::WORD_ARRAY, x);
}

// FloatArray
maybe<Storage> FloatArray::from_bytes(bytes x, int o)
{
  // FIXME
  return std::nullopt;
}

// Encodes a FloatArray into a byte array
// Format: {(size x) squeeze) join x} (i each {x IEEE<32|64>} over join)
bytes FloatArray::to_bytes(Storage x)
{
  if(std::holds_alternative<floats>(x.i))
  {
    bytes result = bytes();

    floats i = std::get<floats>(x.i);

    int length = i.size();
    bytes lengthBytes = squeeze_int(length);

    result.insert(result.begin(), lengthBytes.begin(), lengthBytes.end());

    for(float f : i)
    {
      bytes integerBytes = squeeze_floating(floating(f));
      result.insert(result.end(), integerBytes.begin(), integerBytes.end());
    }

    return result;
  }
  else
  {
    return bytes();
  }
}

maybe<Storage> FloatArray::from_conn(ReliableConnection conn, int o)
{
  varint varsize = expand_conn(conn);
  if(std::holds_alternative<int>(varsize))
  {
    int size = std::get<int>(varsize);

    floats fs = floats();

    for(int y=0; y<size; y++)
    {
      maybe<floating> maybeFloating = expand_conn_floating(conn);
      
      if(maybeFloating)
      {
        if(std::holds_alternative<float>(*maybeFloating))
        {
          float f = std::get<float>(*maybeFloating);
          fs.push_back(f);
        }
        else
        {
          double d = std::get<double>(*maybeFloating);
          fs.push_back((float)d);
        }
      }
      else
      {
        return std::nullopt;
      }
    }

    return FloatArray::make(fs, o);
  }
  else
  {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void FloatArray::to_conn(ReliableConnection conn, Storage x)
{
  if(std::holds_alternative<ints>(x.i))
  {    
    ints i = std::get<ints>(x.i);

    // Always include type in to_conn implementation
    conn.write({(byte)x.t, (byte)x.o});

    int length = i.size();
    bytes lengthBytes = squeeze_int(length);

    conn.write(lengthBytes);

    for(int integer : i)
    {
      bytes integerBytes = squeeze_int(integer);
      conn.write(integerBytes);
    }
  }
}

Storage FloatArray::make(floats x, int o)
{
  return Storage(o, StorageType::FLOAT_ARRAY, x);
}

// Note: MixedArray is defined in noun.h because it needs access to the Noun serialization API
