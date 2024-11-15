#include <Arduino.h>

#include "TempReader.h"
#include "VibrationDetection.h"
#include "NoiceDetection.h"
#include "EmotionsManager.h"
#include "ServerComm.h"
#include "LedMatrix.h"

// Loops
unsigned long lastPollingMillis = 0;
const unsigned long pollingInterval = 500;

unsigned long lastServerCommMillis = 0;
const unsigned long serverCommInterval = 60 * 1000;

unsigned long lastLedMatrixUpdateMillis = 0;
const unsigned long ledMatrixUpdateInterval = 20;

// Sensor readers and controllers
TempReader tempReader = TempReader();
VibrationDetection vibrationDetection = VibrationDetection();
NoiceDetection noiceDetection = NoiceDetection();
EmotionsManager emotionsManager = EmotionsManager();
ServerComm serverComm = ServerComm();
LedMatrix ledMatrix = LedMatrix();

/* ------------------ SETUP ------------------ */

void setup(void) {
  tempReader.begin();
  vibrationDetection.begin();
  noiceDetection.begin();
  emotionsManager.begin();
  serverComm.begin();
  ledMatrix.begin();
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

  // LedMatrix Update Loop
    if (currentMillis - lastLedMatrixUpdateMillis >= ledMatrixUpdateInterval) {
    lastLedMatrixUpdateMillis = currentMillis;
    ledMatrixUpdateLoop();
  }
}

// Loop which only runs in the specified `pollingInterval`. Should be used to read
// data from sensors and update controllers based on that data.
void pollingLoop() {
  tempReader.update();
  vibrationDetection.update();
  noiceDetection.update();
  emotionsManager.update(noiceDetection.activeNoise, vibrationDetection.activeVib);
  serverComm.updateSensorData(noiceDetection.activeNoise, vibrationDetection.activeVib);
}

// Loop which only runs in the specified `serverCommInterval`.
// Should be used sync sensor data with the server.
void serverCommLoop() {
  serverComm.updateTempData(tempReader.temp);
}

// Loop which only runs in the specified `ledMatrixUpdateInterval`.
// Should be used to update the pixels of the Led Matrix.
void ledMatrixUpdateLoop() {
  ledMatrix.update(tempReader.temp, emotionsManager.emotion);
}
