#include "Joystick.h"
#include "HX711.h"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

void setup() {
  Serial.begin(9600);
  Joystick.begin();
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();    
  scale.tare();
}

void loop() {
  # Invert reading and decrease reading values
  int reading = scale.get_units(1) * -0.1;
  # For debugging purposes, slows readings when not reading serial monitor
  #Serial.print("Unmapped reading: ");
  #Serial.println(reading);
  # Map reading to 0-248, else windows controller reading loops back to 0
  int readingMapped = map(reading,15000,245000,0,248);
  Joystick.setThrottle(readingMapped);
  #Serial.print("Mapped reading: ");
  #Serial.println(readingMapped);
}
