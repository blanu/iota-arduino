#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <Arduino.h>
#include <optional>
#include "storage.h"
#include "nouns.h"

class EvalRegister;

class EvalRegister
{
  public:
    static void initialize()
    {
      Nouns::initialize();
    }

    EvalRegister() : i(Word::make(0, INTEGER)), r(std::nullopt) {}
    EvalRegister(Storage i) : i(i), r(std::nullopt) {}

    void store_i(Storage newI);
    Storage fetch_i();
    void load_i(std::vector<byte> data);

    std::optional<Storage> fetch_r();
    std::optional<std::vector<byte>> retrieve_r();

    void eval();

  private:
    Storage i;
    std::optional<Storage> r;
};

#endif