#include <Arduino.h>

#include "TempReader.h"
#include "VibrationDetection.h"
#include "NoiceDetection.h"
#include "ServerComm.h"

// Loops
unsigned long lastPollingMillis = 0;
const unsigned long pollingInterval = 500;

unsigned long lastServerCommMillis = 0;
const unsigned long serverCommInterval = 60 * 1000;

// Sensor readers and controllers
TempReader tempReader = TempReader();
VibrationDetection vibrationDetection = VibrationDetection();
NoiceDetection noiceDetection = NoiceDetection();
ServerComm serverComm = ServerComm();

/* ------------------ SETUP ------------------ */

void setup(void) {
  tempReader.begin();
  vibrationDetection.begin();
  noiceDetection.begin();
  serverComm.begin();
}

/* ------------------ LOOPS ------------------ */

void loop() {
  unsigned long currentMillis = millis();

  // Polling Loop
  if (currentMillis - lastPollingMillis >= pollingInterval) {
    lastPollingMillis = currentMillis;
    pollingLoop();
  }

  // ServerComm Loop
  if (currentMillis - lastServerCommMillis >= serverCommInterval) {
    lastServerCommMillis = currentMillis;
    serverCommLoop();
  }

  // Regular Loop
}

// Loop which only runs in the specified `pollingInterval`.
// Should be used to read data from sensors.
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

// Loop which only runs in the specified `serverCommInterval`.
// Should be used sync sensor data with the server.
void serverCommLoop() {
  serverComm.update(tempReader.temp);
}
