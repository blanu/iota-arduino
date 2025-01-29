#include "SerialConnection.h"

#include <tuple>
#include <optional>

#include "squeeze.h"
#include "noun.h"

maybe<Storage> SerialConnection::read_storage()
{
  return Noun::from_conn(reliable);
}

void SerialConnection::write_storage(Storage x)
{
  Noun::to_conn(reliable, x);
}
