#include "noun.h"
#include "error.h"

std::map<Specialization3, Monad> Noun::monads;
std::map<Specialization5, Dyad> Noun::dyads;
std::map<Specialization5, Triad> Noun::triads;
std::map<Specialization3, MonadicAdverb> Noun::monadicAdverbs;
std::map<Specialization5, DyadicAdverb> Noun::dyadicAdverbs;

// Dispatch
Storage Noun::dispatchMonad(Storage i, Storage f)
{
  if(i.o == ERROR)
  {
    return i;
  }

  if(f.t != WORD)
  {
    return Word::make(BAD_OPERATION, ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization3 specialization = Specialization3(i.t, i.o, fi);
  if (monads.find(specialization) == monads.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, ERROR);
  }

  Monad verb = monads[specialization];
  return verb(i);
}

Storage Noun::dispatchDyad(Storage i, Storage f, Storage x)
{
  if(i.o == ERROR)
  {
    return i;
  }

  if(x.o == ERROR)
  {
    return x;
  }

  if(f.t != WORD)
  {
    return Word::make(BAD_OPERATION, ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (dyads.find(specialization) == dyads.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, ERROR);
  }

  Dyad verb = dyads[specialization];
  return verb(i, x);
}

Storage Noun::dispatchTriad(Storage i, Storage f, Storage x, Storage y)
{
  if(i.o == ERROR)
  {
    return i;
  }

  if(x.o == ERROR)
  {
    return x;
  }

  if(f.t != WORD)
  {
    return Word::make(BAD_OPERATION, ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (triads.find(specialization) == triads.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, ERROR);
  }

  Triad verb = triads[specialization];
  return verb(i, x, y);
}

Storage Noun::dispatchMonadicAdverb(Storage i, Storage f, Storage g)
{
  if(i.o == ERROR)
  {
    return i;
  }

  if(f.t != WORD)
  {
    return Word::make(BAD_OPERATION, ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization3 specialization = Specialization3(i.t, i.o, fi);
  if (monadicAdverbs.find(specialization) == monadicAdverbs.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, ERROR);
  }

  MonadicAdverb adverb = monadicAdverbs[specialization];
  return adverb(i, g);
}

Storage Noun::dispatchDyadicAdverb(Storage i, Storage f, Storage g, Storage x)
{
  if(i.o == ERROR)
  {
    return i;
  }

  if(x.o == ERROR)
  {
    return x;
  }

  if(f.t != WORD)
  {
    return Word::make(BAD_OPERATION, ERROR);
  }

  int fi = std::get<int>(f.i);

  Specialization5 specialization = Specialization5(i.t, i.o, fi, x.t, x.o);
  if (dyadicAdverbs.find(specialization) == dyadicAdverbs.end())
  {
    return Word::make(UNSUPPORTED_OBJECT, ERROR);
  }

  DyadicAdverb adverb = dyadicAdverbs[specialization];
  return adverb(i, g, x);
}

// Registration

void Noun::registerMonad(Symbol it, Symbol io, Symbol f, Storage (*m)(Storage))
{
  Noun::monads[Specialization3(it, io, f)] = m;
}

void Noun::registerDyad(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*d)(Storage, Storage))
{
  Noun::dyads[Specialization5(it, io, f, xt, xo)] = d;
}

void Noun::registerTriad(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*t)(Storage, Storage, Storage))
{
  Noun::triads[Specialization5(it, io, f, xt, xo)] = t;
}

void Noun::registerMonadicAdverb(Symbol it, Symbol io, Symbol f, Storage (*a)(Storage, Storage))
{
  Noun::monadicAdverbs[Specialization3(it, io, f)] = a;
}

void Noun::registerDyadicAdverb(Symbol it, Symbol io, Symbol f, Symbol xt, Symbol xo, Storage (*a)(Storage, Storage, Storage))
{
  Noun::dyadicAdverbs[Specialization5(it, io, f, xt, xo)] = a;
}

