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

/**
  The measured temperature is based on sensor build in the microcontroller.
  The microcontroller operation can increase its temperature, causing the reading 
  to be higher than the actual surrounding temperature. Adjust by subtracting 5.

  TODO: Find a more precise algorithm to treasure the sourrounding temperature. 
*/
int TempReader::internalToSourroundingTemp(int internalTemp) {
  return internalTemp - 5;
}
