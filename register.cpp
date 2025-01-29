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

void EvalRegister::load_i(bytes data)
{
  maybe<Storage> maybeResult = Noun::from_bytes(data);
  if(maybeResult)
  {
    i = *maybeResult;
  }
}

maybe<Storage> EvalRegister::fetch_r()
{
  return r;
}

maybe<bytes> EvalRegister::retrieve_r()
{
  if(r)
  {
    Storage value = *r;
    return maybe<bytes>(Noun::to_bytes(value));
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

