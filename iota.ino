#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "SerialConnection.h"
#include "register.h"
#include "types.h"

SerialConnection conn = SerialConnection();
EvalRegister eval_register = EvalRegister();

Adafruit_NeoPixel pixels(1, 8, NEO_GRB + NEO_KHZ800);

void setup()
{
  EvalRegister::initialize();

  pixels.begin();
  pixels.setBrightness(50);

  pinMode(D13, OUTPUT);
  blink(255, 255, 255, 1, 5000, 1000);
}

void loop()
{
  blink(255, 255, 255, 2, 450, 100);

  std::optional<Storage> storage = conn.read_storage();

  if(storage)
  {
    blink(255, 255, 255, 5, 150, 50);

    eval_register.store_i(*storage);
    eval_register.eval();
    maybe<Storage> result = eval_register.fetch_r();

    if(result)
    {
      conn.write_storage(*result);
    }
  }
  else
  {
    blink(255, 255, 255, 3, 300, 100);
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