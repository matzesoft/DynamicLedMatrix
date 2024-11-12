#include <Arduino.h>

#include "TempReader.h"
#include "VibrationDetection.h"

unsigned long lastPollingMillis = 0;
const unsigned long pollingInterval = 500;

TempReader tempReader = TempReader();
VibrationDetection vibrationDetection = VibrationDetection();

void setup(void) {
  tempReader.begin();
  vibrationDetection.begin();
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

  Serial.print("Sourrounding Temperature = ");
  Serial.print(tempReader.temp);
  Serial.println(" °C");

  Serial.print("Active Vibrations = ");
  Serial.println(vibrationDetection.activeVib);
}
