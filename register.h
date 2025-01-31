#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <Arduino.h>
#include <optional>
#include "storage.h"
#include "noun.h"
#include "debug.h"

class EvalRegister;

class EvalRegister
{
  public:
    static void initialize();

    EvalRegister() : i(Word::make(0, NounType::INTEGER)), r(std::nullopt) {}
    EvalRegister(Storage i) : i(i), r(std::nullopt) {}

    void store_i(Storage newI);
    Storage fetch_i();
    void load_i(bytes data);

    maybe<Storage> fetch_r();
    maybe<bytes> retrieve_r();

    void eval();

  private:
    Storage i;
    maybe<Storage> r;
};

#endif