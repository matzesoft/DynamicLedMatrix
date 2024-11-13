#include "LedMatrix.h"

/* ------------- PROTOMATTER CONTEXT ------------- */

// Pin definitions
uint8_t rgbPins[] = { 17, 16, 15, 20, 19, 18 };
uint8_t addrPins[] = { 26, 27, 28, 29 };
uint8_t clockPin = 5;
uint8_t latchPin = 4;
uint8_t oePin = 7;

Adafruit_Protomatter matrix(
  32,                         // Width of matrix (or matrix chain) in pixels
  4,                          // Bit depth, 1-6
  1, rgbPins,                 // # of matrix chains, array of 6 RGB pins for each
  4, addrPins,                // # of address pins (height is inferred), array of pins
  clockPin, latchPin, oePin,  // Other matrix control pins
  true                        // HERE IS THE MAGIC FOR DOUBLE-BUFFERING!
);

/* --------------- PUBLIC FUNCTIONS --------------- */

LedMatrix::LedMatrix() {}

void LedMatrix::begin() {
  ProtomatterStatus status = matrix.begin();
  if (status != PROTOMATTER_OK) {
    Serial.print("Protomatter begin() failed with status: ");
    Serial.println((int)status);
  }

  /*
  Due to an old Protomatter library issue, the correct CP437 character codes have to be exlicity set.

  Read about this issue here:
  https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives#extended-characters-cp437-and-a-lurking-bug-3100368
  */
  matrix.cp437(true);
}

void LedMatrix::update(int temperature, Emotion emotion) {
  matrix.fillScreen(0);  // Fill background black

  switch (emotion) {
    case Emotion::NEUTRAL:
      drawNeutralEmotion(temperature);
      break;
    case Emotion::TOO_LOUD:
      drawTooLoudEmotion();
      break;
    case Emotion::SHAKY:
      drawShakyEmotion();
      break;
  }

  matrix.show();
}

/* --------------- PRIVATE FUNCTIONS --------------- */

void LedMatrix::drawNeutralEmotion(int temperature) {
  matrix.setCursor(0, 0);
  matrix.print(temperature);
  matrix.write(0xF8);  // Print the degrees symbol
  matrix.println();

  int16_t x = matrix.width() / 2;
  matrix.fillCircle(x, 20, 8, 0x001F);

  matrix.drawRoundRect(x - 4, 16, 3, 5, 1, 0xFFFF);
  matrix.drawRoundRect(x + 2, 16, 3, 5, 1, 0xFFFF);
}

void LedMatrix::drawTooLoudEmotion() {
  matrix.setCursor(0, 0);
  matrix.println("TOO LOUD");

  // TODO: Implement
}

void LedMatrix::drawShakyEmotion() {
  matrix.setCursor(0, 0);
  matrix.println("SHAKY");

  // TODO: Implement
}
