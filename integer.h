#ifndef _INTEGER_H_
#define _INTEGER_H_

#include "noun.h"
#include "storage.h"
#include "symbols.h"

class Integer
{
  public:
    static void initialize()
    {
      Noun::registerMonad(WORD, INTEGER, Monads::evaluate, Storage::identity);
    }
};

#endif