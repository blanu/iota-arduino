#include "debug.h"

void d(byte b)
{
  Serial.write((byte)0x80);
  Serial.write(b);
}
