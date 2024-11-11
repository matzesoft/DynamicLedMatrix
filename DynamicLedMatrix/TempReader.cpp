#include <Arduino_LSM6DSOX.h>

#include "TempReader.h"

/* --- PUBLIC FUNCTIONS --- */

TempReader::TempReader() {}

void TempReader::begin() {
  IMU.begin();
}

void TempReader::update() {
  if (IMU.temperatureAvailable()) {
    int internalTemp = 0;
    IMU.readTemperature(internalTemp);

    temp = internalToSourroundingTemp(internalTemp);
  }
}

/* --- PRIVATE FUNCTIONS --- */

int TempReader::internalToSourroundingTemp(int internalTemp) {
  return internalTemp - 5;
}
