#include <Arduino.h>

#include "TempReader.h"

TempReader tempReader = TempReader();

void setup(void) {
  tempReader.begin();
}

void loop() {
  tempReader.update();

  Serial.print("Sourrounding Temperature = ");
  Serial.print(tempReader.temp);
  Serial.println(" °C");

  delay(500);
}
