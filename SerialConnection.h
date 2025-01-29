#ifndef _SERIAL_CONNECTION_H_
#define _SERIAL_CONNECTION_H_

#include <Arduino.h>
#include <vector>
#include <optional>

#include "storage.h"
#include "ReliableConnection.h"

class SerialConnection
{
  public:
    SerialConnection()
    {
      Serial.begin(115200);
    }

    maybe<Storage> read_storage();
    void write_storage(Storage x);

  private:
    ReliableConnection reliable = ReliableConnection(Serial);
};

#endif