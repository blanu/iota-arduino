#ifndef _SERIAL_CONNECTION_H_
#define _SERIAL_CONNECTION_H_

#include <Arduino.h>
#include <vector>
#include <optional>
#include "storage.h"

class SerialConnection
{
  public:
    SerialConnection()
    {
      Serial.begin(9600);
    }

    std::vector<byte> read(int size);
    void write(std::vector<byte> bs);

    std::optional<Storage> read_storage();
    void write_storage(Storage x);
};

#endif