#include "HX711.h"
#include "Joystick.h"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
long reading, mappedReading = 0;
HX711 scale;

void setup() {
  Serial.begin(38400);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Joystick.begin();
  scale.set_scale();
  scale.tare();
}

void sendOutput(long input) {
    mappedReading = map(input ,9000 ,300000,0,248);
    if (mappedReading < 0)
      mappedReading = 0;
    if (mappedReading > 248)
      mappedReading = 248;
    Joystick.setThrottle(mappedReading);
    //Serial.print(mappedReading);
    //Serial.print("\n");
}

void loop() {
  if (scale.is_ready()){
    reading = scale.get_units();
    sendOutput(reading);
    //Serial.print(reading);
    //Serial.print("\n");
  }
}
