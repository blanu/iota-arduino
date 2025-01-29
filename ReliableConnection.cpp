#include "ReliableConnection.h"

// ReliableConnection
byte ReliableConnection::readOne()
{
  // Wait for serial port to be ready
  while(!Serial || !Serial.available())
  {
    delay(0.01);
  }

  int b = -1;
  while(b == -1)
  {
    b = Serial.read();
  }

  return (byte)b;
}

bytes ReliableConnection::read(int size)
{
  bytes r = bytes();

  while(r.size() < size)
  {
    byte b = readOne();
    r.push_back(b);
  }

  return r;
}

void ReliableConnection::write(bytes bs)
{
  for (byte b : bs)
  {
    Serial.write(b); // Send each byte
  }
}

