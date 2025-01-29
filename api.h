#ifndef _API_H_
#define _API_H_

#include "storage.h"
#include "types.h"

// SymbolType
class SymbolType
{
  public:
    static const int i = 0;
    static const int x = 1;
    static const int y = 2;
    static const int z = 3;
    static const int f = 4;
    static const int undefined = 5;
};

const int i = SymbolType::i;
const int x = SymbolType::x;
const int y = SymbolType::y;
const int z = SymbolType::z;
const int f = SymbolType::f;
const int undefined = SymbolType::undefined;

Storage e();
Storage c();

Storage test_error();
const char *error_to_string(Storage error);

maybe<Storage> eval(Storage x);

#endif