#include <PDM.h>

#include "NoiceDetection.h"

/* ----------------- ISR CONTEXT ----------------- */

/**
The PDM library uses an ISR to get samples from the microphone.
This requires these variables and functions to be static in the file.

TODO: Currently it is possible to create multiple instances of the NoiceDetection class.
This can cause issues when using static variables. Possible solution: Singelton
**/

static const char Channels = 1;
static const int Frequency = 16000;

static short sampleBuffer[512];
static volatile int samplesRead;

// Callback function to process the data from the PDM microphone.
void onPDMdata() {
  int bytesAvailable = PDM.available();
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}

/* --------------- PUBLIC FUNCTIONS --------------- */

NoiceDetection::NoiceDetection() {}

void NoiceDetection::begin() {
  PDM.onReceive(onPDMdata);

  if (!PDM.begin(Channels, Frequency)) {
    Serial.println("Failed to start NoiceDetection!");
  }
}

void NoiceDetection::update() {

  if (samplesRead) {
    float averageLoudness = calculateRMS(sampleBuffer, samplesRead);
    activeNoise = (averageLoudness > Threshold);

    samplesRead = 0;
  }
}

/* --------------- PRIVATE FUNCTIONS --------------- */

// Calculates the Root Mean Square (RMS) of an array of audio samples,
// which represents the signal's average energy or loudness.
float NoiceDetection::calculateRMS(short *samples, int numSamples) {
  long sum = 0;
  for (int i = 0; i < numSamples; i++) {
    sum += (long)samples[i] * samples[i];
  }
  return sqrt((float)sum / numSamples);
}
