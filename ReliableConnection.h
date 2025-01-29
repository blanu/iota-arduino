#ifndef _RELIABLE_CONNECTION_H_
#define _RELIABLE_CONNECTION_H_

#include <Arduino.h>
#include <vector>

#include "types.h"

class ReliableConnection
{
  public:
    ReliableConnection(SerialUSB serial) : serial(serial) {}

    byte readOne();
    bytes read(int size);
    void write(bytes bs);

  private:
    SerialUSB serial;
};

#endif