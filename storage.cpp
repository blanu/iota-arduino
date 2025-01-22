#include <vector>
#include <variant>
#include <tuple>
#include <Arduino.h>
#include <stdint.h>

#include "storage.h"
#include "squeeze.h"
#include "error.h"
#include <optional>

// Storage::from_bytes decodes a byte array into a Storage object by delegating to each Storage subclass's decoder
std::optional<Storage> Storage::from_bytes(std::vector<byte> x)
{
  int storageType = (int)x.at(0);
  int objectType = (int)x.at(1);
  std::vector<byte> untypedData(x.begin() + 2, x.end());

  switch (storageType)
  {
    case WORD:
    {
      return std::optional<Storage>(Word::from_bytes(untypedData, objectType));
    }

    case FLOAT:
    {
      return std::optional<Storage>(Float::from_bytes(untypedData, objectType));
    }

    case WORD_ARRAY:
    {
      return std::optional<Storage>(WordArray::from_bytes(untypedData, objectType));
    }

    case FLOAT_ARRAY:
    {
      return std::optional<Storage>(FloatArray::from_bytes(untypedData, objectType));
    }

    case MIXED_ARRAY:
    {
      return std::optional<Storage>(MixedArray::from_bytes(untypedData, objectType));
    }

    default:
      return std::nullopt;
  }
}

// Encodes a Storage into a byte array by delegating to each subclass
// Format: byte:t byte:o [byte]:subclass.from_bytes(i)
std::vector<byte> Storage::to_bytes(Storage x)
{
  std::vector<byte> typeBytes = {(byte)x.t, (byte)x.o};

  std::vector<byte> valueBytes = std::vector<byte>();
  switch(x.t)
  {
    case WORD:
    {
      valueBytes = Word::to_bytes(x);
      break;
    }

    case FLOAT:
    {
      valueBytes = Float::to_bytes(x);
      break;
    }

    case WORD_ARRAY:
    {
      valueBytes = WordArray::to_bytes(x);
      break;
    }

    case FLOAT_ARRAY:
    {
      valueBytes = FloatArray::to_bytes(x);
      break;
    }

    case MIXED_ARRAY:
    {
      valueBytes = MixedArray::to_bytes(x);
      break;
    }

    default:
      return std::vector<byte>();
  }

  std::vector<byte> result(typeBytes.begin(), typeBytes.end());
  result.insert(result.end(), valueBytes.begin(), valueBytes.end());
  return result;
}

Storage Storage::identity(Storage i)
{
  return i;
}

// Word
// Storage::from_bytes decodes a byte array into a Word object
std::optional<Storage> Word::from_bytes(std::vector<byte> x, int o)
{
  int integer = expand_int_from_bytes(x);
  return Word::make(integer, o);
}

// Encodes a Word into a byte array
// Format: int:i.squeeze
std::vector<byte> Word::to_bytes(Storage x)
{
  if(std::holds_alternative<int>(x.i))
  {
    int i = std::get<int>(x.i);
    std::vector<byte> result = squeeze_int(i);
    return result;
  }
  else
  {
    return std::vector<byte>();
  }
}

Storage Word::make(int x, int o)
{
  return Storage(o, WORD, x);
}

// Float
// Storage::from_bytes decodes a byte array into a Float object
std::optional<Storage> Float::from_bytes(std::vector<byte> x, int o)
{
  std::tuple<int, std::vector<byte>> expanded = expand_int(x);
  int integer = std::get<0>(expanded);

  return std::optional(Storage(o, WORD, integer));
}

// Encodes a Float into a byte array
// Format: i.IEEE<32|64> - FIXME - relies on sizeof(float)
std::vector<byte> Float::to_bytes(Storage x)
{
  if(std::holds_alternative<float>(x.i))
  {
    float i = std::get<float>(x.i);
    return squeeze_float(i);
  }
  else
  {
    return std::vector<byte>();
  }
}

Storage Float::make(float x, int o)
{
  return Storage(o, FLOAT, x);
}

// WordArray
// Storage::from_bytes decodes a byte array into a WordArray object
std::optional<Storage> WordArray::from_bytes(std::vector<byte> x, int o)
{
  return std::optional(Storage(0, WORD, 0));
}

// Encodes a WordArray into a byte array
// Format: {(size x) squeeze) join x} (i each {x squeeze} over join)
std::vector<byte> WordArray::to_bytes(Storage x)
{
  if(std::holds_alternative<std::vector<int>>(x.i))
  {
    std::vector<int> i = std::get<std::vector<int>>(x.i);
    return squeeze_ints(i);
  }
  else
  {
    return std::vector<byte>();
  }
}

Storage WordArray::make(std::vector<int> x, int o)
{
  return Storage(o, WORD_ARRAY, x);
}

// FloatArray
std::optional<Storage> FloatArray::from_bytes(std::vector<byte> x, int o)
{
  return std::optional(Storage(0, WORD, 0));
}

// Encodes a FloatArray into a byte array
// Format: {(size x) squeeze) join x} (i each {x IEEE<32|64>} over join)
std::vector<byte> FloatArray::to_bytes(Storage x)
{
  if(std::holds_alternative<std::vector<int>>(x.i))
  {
    std::vector<float> i = std::get<std::vector<float>>(x.i);
    return squeeze_floats(i);
  }
  else
  {
    return std::vector<byte>();
  }
}

Storage FloatArray::make(std::vector<float> x, int o)
{
  return Storage(o, FLOAT_ARRAY, x);
}

// MixedArray
// Storage::from_bytes decodes a byte array into a MixedArray object
std::optional<Storage> MixedArray::from_bytes(std::vector<byte> x, int o)
{
  return std::optional(Storage(0, WORD, 0));
}

// Encodes a MixedArray into a byte array
// Format: {(size x) squeeze) join x} (i each {x to_bytes} over join)
std::vector<byte> MixedArray::to_bytes(Storage x)
{
  if(std::holds_alternative<std::vector<Storage>>(x.i))
  {
    std::vector<byte> r = {(byte)x.t, (byte)x.o};

    std::vector<Storage> i = std::get<std::vector<Storage>>(x.i);

    // The only case where the length can be zero is for the number 0.
    if(i.size() == 0)
    {
      return r;
    }

  int size = i.size();
  std::vector<byte> sizeBytes = squeeze_int(size);

  r.insert(r.begin(), sizeBytes.begin(), sizeBytes.end());

  for(Storage y : i)
  {
    std::vector<byte> valueBytes = Storage::to_bytes(y);
    r.insert(r.end(), valueBytes.begin(), valueBytes.end());
  }

  return r;



    std::vector<byte> valueBytes(sizeof(float));
    memcpy(valueBytes.data(), &i, sizeof(float));
    
    r.insert(r.begin(), valueBytes.begin(), valueBytes.end());
    return r;
  }
  else
  {
    return std::vector<byte>();
  }
}

Storage MixedArray::make(std::vector<Storage> x, int o)
{
  return Storage(o, MIXED_ARRAY, x);
}
