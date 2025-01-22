#include "SerialConnection.h"

#include <tuple>
#include <optional>

#include "squeeze.h"
#include "storage.h"

std::vector<byte> SerialConnection::read(int size)
{
  std::vector<byte> r = std::vector<byte>();

  while(r.size() < size)
  {
    // Wait for serial port to be ready
    while(!Serial || !Serial.available())
    {
      delay(0.1);
    }

    byte b = Serial.read();
    r.push_back(b);
  }

  return r;
}

std::optional<Storage> SerialConnection::read_storage()
{
  std::vector<byte> prefixBytes = read(3);
  if(prefixBytes.size() != 3)
  {
    return std::nullopt;
  }

  int type = prefixBytes.at(0);
  int object = prefixBytes.at(1);
  int length = prefixBytes.at(2);

  switch(type)
  {
    case WORD:
    {
      if(length == 0)
      {
        return std::optional<Storage>(Word::make(0, object));
      }
      else if(length & 0x80)
      {
        length = length & 0x7F;
        std::vector<byte> integerBytes = read(length);
        std::optional<Storage> maybeWord = Word::from_bytes(integerBytes, object);
        if(maybeWord)
        {
          I i = (*maybeWord).i;
          int o = (*maybeWord).o;

          int integer = std::get<int>(i);

          Storage negated = Word::make(-integer, o);
          return std::optional<Storage>(negated);
        }
        else
        {
          return std::nullopt;          
        }
      }
      else
      {
        std::vector<byte> integerBytes = read(length);
        return Word::from_bytes(integerBytes, object);
      }
    }

    // case FLOAT:
    // case WORD_ARRAY:
    // case FLOAT_ARRAY:
    // case MIXED_ARRAY:
    default:
      return std::nullopt;
  }
}

void SerialConnection::write(std::vector<byte> bs)
{
  for (byte b : bs)
  {
    Serial.write(b); // Send each byte
  }
}

void SerialConnection::write_storage(Storage x)
{
  std::vector<byte> bytes = Storage::to_bytes(x);
  write(bytes);
}