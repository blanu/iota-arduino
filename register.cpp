#include <optional>
#include "register.h"
#include "storage.h"
#include "symbols.h"
#include "noun.h"

void EvalRegister::store_i(Storage newI)
{
  i = newI;
}

Storage EvalRegister::fetch_i()
{
  return i;
}

void EvalRegister::load_i(std::vector<byte> data)
{
  std::optional<Storage> maybeResult = Storage::from_bytes(data);
  if(maybeResult)
  {
    i = *maybeResult;
  }
}

std::optional<Storage> EvalRegister::fetch_r()
{
  return r;
}

std::optional<std::vector<byte>> EvalRegister::retrieve_r()
{
  if(r)
  {
    Storage value = *r;
    return std::optional<std::vector<byte>>(Storage::to_bytes(value));
  }
  else
  {
    return std::nullopt;
  }
}

void EvalRegister::eval()
{
  r = Noun::dispatchMonad(i, Word::make(Monads::evaluate, BUILTIN_MONAD));
}

