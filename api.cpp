#include "api.h"
#include "error.h"
#include "storage.h"
#include "symbols.h"
#include "noun.h"

const int SymbolType::i;
const int SymbolType::x;
const int SymbolType::y;
const int SymbolType::z;
const int SymbolType::f;
const int SymbolType::undefined;

Storage e()
{
  return Word::make(0, 0);
}

Storage c()
{
  return Word::make(0, 0);
}

Storage test_error()
{
  return Word::make(TEST_ERROR, NounType::ERROR);
}

const char *error_to_string(Storage e)
{
  if(e.o != NounType::ERROR)
  {
    return NULL;
  }

  if(e.t != StorageType::WORD)
  {
    return NULL;
  }

  if(std::holds_alternative<int>(e.i))
  {
    int i = std::get<int>(e.i);

    switch(i)
    {
      case BAD_INDEX_TYPE:
        return "unsupported index type";

      case BAD_INITIALIZATION:
        return "bad initialization value";

      case BAD_STORAGE:
        return "this object type does not support this storage type";

      case BAD_OPERATION:
        return "this operation is not supported by this object type with this storage type";

      case EMPTY:
        return "empty";

      case INVALID_ARGUMENT:
        return "invalid argument type";

      case INVALID_ADVERB_ARGUMENT:
        return "invalid adverb argument";

      case OUT_OF_BOUNDS:
        return "out of bounds";

      case SHAPE_MISMATCH:
        return "mismatched shapes";

      case TEST_ERROR:
        return "test error";

      case UNSUPPORTED_OBJECT:
        return "operation is not supported by this object type";

      case UNSUPPORTED_SUBJECT:
        return "unsupported subject type";

      case UNKNOWN_KEY:
        return "unknown key";

      case UNEQUAL_ARRAY_LENGTHS:
        return "unequal array lengths";

      case DIVISION_BY_ZERO:
        return "division by zero";

      default:
        return "unknown error";
    }
  }
  else
  {
    return NULL;
  }
}
