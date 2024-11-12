#include <Arduino.h>

#include "TempReader.h"
#include "VibrationDetection.h"
#include "NoiceDetection.h"

unsigned long lastPollingMillis = 0;
const unsigned long pollingInterval = 500;

TempReader tempReader = TempReader();
VibrationDetection vibrationDetection = VibrationDetection();
NoiceDetection noiceDetection = NoiceDetection();

void setup(void) {
  tempReader.begin();
  vibrationDetection.begin();
  noiceDetection.begin();
}

void loop() {
  // Polling Loop
  unsigned long currentMillis = millis();
  if (currentMillis - lastPollingMillis >= pollingInterval) {
    lastPollingMillis = currentMillis;
    pollingLoop();
  }

  // Regular Loop
}

// Loop which only runs in the specified `pollingInterval`.
void pollingLoop() {
  tempReader.update();
  vibrationDetection.update();
  noiceDetection.update();

  Serial.print("Sourrounding Temperature = ");
  Serial.print(tempReader.temp);
  Serial.println(" °C");
  Serial.print("Noice Detection = ");
  Serial.println(noiceDetection.activeNoise);

  Serial.print("Active Vibrations = ");
  Serial.println(vibrationDetection.activeVib);
}
