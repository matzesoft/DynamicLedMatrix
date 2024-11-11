#include <Arduino_LSM6DSOX.h>

#include "VibrationDetection.h"

/* --- PUBLIC FUNCTIONS --- */
VibrationDetection::VibrationDetection() {}

void VibrationDetection::begin() {
  IMU.begin();
}

void VibrationDetection::update() {
  if (IMU.accelerationAvailable()) {
    float x, y, z;
    IMU.readAcceleration(x, y, z);

    activeVib = accelerationsOverThreshold(x, y, z);
  }
}

/* --- PRIVATE FUNCTIONS --- */

boolean VibrationDetection::accelerationsOverThreshold(float x, float y, float z) {
  return x > VibrationDetection::Threshold || y > VibrationDetection::Threshold || z > VibrationDetection::Threshold;
}

void serialPrintAcclerations(float x, float y, float z) {
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.print(z);
  Serial.println("");
}
