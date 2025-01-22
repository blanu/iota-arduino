#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
// #include "error.h"
// #include "squeeze.h"
// #include "storage.h"
#include "SerialConnection.h"
#include "register.h"
// #include <optional>

SerialConnection conn = SerialConnection();
// EvalRegister eval_register = EvalRegister();

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
    conn.write_storage(*storage);
  }
  else
  {
    blink(255, 255, 255, 3, 300, 100);
  }

//   blink();
//   eval_register.load_i(i_data);
//   blink();

//   blink();
//   eval_register.eval();
//   blink();

//   blink();
//   std::optional<std::vector<byte>> maybeResult = eval_register.retrieve_r();
//   if(maybeResult)
//   {
//     conn.write(*maybeResult);    
//   }
//   else
//   {
//     conn.write(std::vector<byte>({0}));
//   }
//   blink();
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