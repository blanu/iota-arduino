#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

// Monads
class Monads
{
  public:
    static const int atom = 0;
    static const int ichar = 1;
    static const int complementation = 2;
    static const int enclose = 3;
    static const int enumerate = 4;
    static const int first = 5;
    static const int floor = 6;
    static const int format = 7;
    static const int gradeDown = 8;
    static const int gradeUp = 9;
    static const int group = 10;
    static const int negate = 11;
    static const int reciprocal = 12;
    static const int reverse = 13;
    static const int shape = 14;
    static const int size = 15;
    static const int transpose = 16;
    static const int unique = 17;
    static const int count = 18;

    static const int evaluate = 19;
    static const int erase = 20;
    static const int truth = 21;
};

// Dyads
class Dyads
{
  public:
    static const int amend = 22;
    static const int cut = 23;
    static const int divide = 24;
    static const int drop = 25;
    static const int equal = 26;
    static const int expand = 27;
    static const int find = 28;
    static const int form = 29;
    static const int format2 = 30;
    static const int index = 31;
    static const int indexInDepth = 32;
    static const int integerDivide = 33;
    static const int join = 34;
    static const int less = 35;
    static const int match = 36;
    static const int max = 37;
    static const int min = 38;
    static const int minus = 39;
    static const int more = 40;
    static const int plus = 41;
    static const int power = 42;
    static const int remainder = 43;
    static const int reshape = 44;
    static const int rotate = 45;
    static const int split = 46;
    static const int take = 47;
    static const int times = 48;

    static const int applyMonad = 49;
    static const int retype = 50;
};

// Triads
class Triads
{
  public:
    static const int applyDyad = 51;
};

// MonadicAdverbs
class MonadicAdverbs
{
  public:
    static const int converge = 52;
    static const int each = 53;
    static const int eachPair = 54;
    static const int over = 55;
    static const int scanConverging = 56;
    static const int scanOver = 57;
};

// Dyadic Adverbs
class DyadicAdverbs
{
  public:
    static const int each2 = 58;
    static const int eachLeft = 59;
    static const int eachRight = 60;
    static const int overNeutral = 61;
    static const int whileOne = 62;
    static const int iterate = 63;
    static const int scanOverNeutral = 64;
    static const int scanWhileOne = 65;
    static const int scanIterating = 66;
};

#endif