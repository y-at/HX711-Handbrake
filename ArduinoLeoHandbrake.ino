#include "Joystick.h"
#include "HX711.h"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

void setup() {
  Serial.begin(115200);
  Joystick.begin();
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();    
  scale.tare();
}

void setThrottleIf(int in) {
  
}

void loop() {
  int reading = scale.get_units(1) * -0.1;
  Serial.print("Unmapped reading: ");
  Serial.println(reading);
  int readingMapped = map(reading,15000,245000,0,248);
  if (readingMapped < 20)
    readingMapped = 0;
  Joystick.setThrottle(readingMapped);
  Serial.print("Mapped reading: ");
  Serial.println(readingMapped);
}
