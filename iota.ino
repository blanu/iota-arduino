#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "SerialConnection.h"
#include "register.h"
#include "types.h"
#include "debug.h"

SerialConnection conn = SerialConnection();
EvalRegister eval_register = EvalRegister();

Adafruit_NeoPixel pixels(1, 8, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(D13, OUTPUT);
  while(!Serial)
  {
    blink(255, 255, 255, 1, 200, 200);
  }

  EvalRegister::initialize();
}

void loop()
{
  std::optional<Storage> storage = conn.read_storage();

  if(storage)
  {
    eval_register.store_i(*storage);
    eval_register.eval();
    maybe<Storage> result = eval_register.fetch_r();

    if(result)
    {
      conn.write_storage(*result);
    }
  }
}

void blink(byte r, byte g, byte b, int count, int onTime, int offTime)
{
  for(int x=0; x<count; x++)
  {
    digitalWrite(D13, HIGH);
    pixels.setPixelColor(0, pixels.Color(r, g, b));
    pixels.show();
    delay(onTime);

    digitalWrite(D13, LOW);
    delay(offTime);
  }
}