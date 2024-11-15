#include <sys/_types.h>
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

  // Calc general matrix constants
  centerX = matrix.width() / 2;

  // Calc constants for NEUTRAL emtotion
  matrix.getTextBounds("20", 0, 0, nullptr, nullptr, nullptr, &neutral_statusBarHeight);  // Use 20°C as height reference for temperatures

  // Calc constants for Schkub
  schkub_centerX = centerX;
  schkub_centerY = ((matrix.height() - neutral_statusBarHeight) / 2) + neutral_statusBarHeight;
  schkub_leftEyeTopX = schkub_centerX - SCHKUB_EYE_WIDTH - 1;
  schkub_rightEyeTopX = schkub_centerX + 2;
  schkub_leftEyeTopY = schkub_centerY - SCHKUB_EYE_HEIGHT + 1;
  schkub_rightEyeTopY = schkub_centerY - SCHKUB_EYE_HEIGHT + 1;
}

void LedMatrix::update(int temperature, Emotion emotion) {
  matrix.fillScreen(0);  // Fill background black

  switch (emotion) {
    case Emotion::NEUTRAL:
      neutral_drawEmotion(temperature);
      break;
    case Emotion::TOO_LOUD:
      tooLoud_drawEmotion();
      break;
    case Emotion::SHAKY:
      shaky_drawEmotion();
      break;
    case Emotion::SLEEP:
      sleep_drawEmotion();
      break;
  }

  matrix.show();
}

/* --------------- PRIVATE FUNCTIONS --------------- */

void LedMatrix::schkub_drawBackground() {
  matrix.fillCircle(schkub_centerX, schkub_centerY, SCHKUB_RADIUS, BLUE);
}

void LedMatrix::schkub_drawEyes() {
  unsigned long currentMillis = millis();
  unsigned long millisSinceReactionStarted = currentMillis - schkub_reactionStartedMillis;

  // Start new reaction
  if (millisSinceReactionStarted >= schkub_reactionInterval) {
    randomSeed(currentMillis);

    schkub_reactionStartedMillis = currentMillis;
    schkub_reactionInterval = random(SCHKUB_REACTION_MIN_INTERVAL, SCHKUB_REACTION_MAX_INTERVAL);

    // Change reaction type
    schkub_reaction = static_cast<SchkubReactions>(random(0, SCHKUB_REACTIONS_COUNT));

    // End current reaction
  } else if (millisSinceReactionStarted >= SCHKUB_REACTION_DURATION) {
    schkub_reaction = SchkubReactions::NONE;
  }

  // Update current reaction
  switch (schkub_reaction) {
    case SchkubReactions::BLINK_EYES:
      matrix.fillRoundRect(schkub_leftEyeTopX, schkub_leftEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);
      matrix.fillRoundRect(schkub_rightEyeTopX, schkub_rightEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);
      break;

    case SchkubReactions::LOOK_LEFT:
      matrix.fillRoundRect(schkub_leftEyeTopX - 1, schkub_leftEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, BLACK);
      matrix.fillRoundRect(schkub_rightEyeTopX - 1, schkub_rightEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, BLACK);
      matrix.drawRoundRect(schkub_leftEyeTopX - 1, schkub_leftEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);
      matrix.drawRoundRect(schkub_rightEyeTopX - 1, schkub_rightEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);
      break;

    case SchkubReactions::LOOK_RIGHT:
      matrix.fillRoundRect(schkub_leftEyeTopX + 1, schkub_leftEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, BLACK);
      matrix.fillRoundRect(schkub_rightEyeTopX + 1, schkub_rightEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, BLACK);
      matrix.drawRoundRect(schkub_leftEyeTopX + 1, schkub_leftEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);
      matrix.drawRoundRect(schkub_rightEyeTopX + 1, schkub_rightEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);
      break;

    default:
      matrix.fillRoundRect(schkub_leftEyeTopX, schkub_leftEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, BLACK);
      matrix.fillRoundRect(schkub_rightEyeTopX, schkub_rightEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, BLACK);
      matrix.drawRoundRect(schkub_leftEyeTopX, schkub_leftEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);
      matrix.drawRoundRect(schkub_rightEyeTopX, schkub_rightEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);
      break;
  }
}


void LedMatrix::neutral_drawEmotion(int temperature) {
  neutral_drawTemperature(temperature);

  schkub_drawBackground();
  schkub_drawEyes();
}

void LedMatrix::neutral_drawTemperature(int temperature) {
  matrix.setCursor(8, 0);
  matrix.setTextColor(WHITE);
  matrix.print(temperature);
  matrix.write(0xF8);  // Print the degrees symbol
  matrix.println();
}

void LedMatrix::tooLoud_drawEmotion() {
  matrix.setCursor(4, 0);
  matrix.setTextColor(YELLOW);
  matrix.println("LOUD");

  matrix.fillCircle(schkub_centerX, schkub_centerY + 7, SCHKUB_RADIUS, BLUE);
  matrix.fillRoundRect(schkub_leftEyeTopX, schkub_leftEyeTopY + 6, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT + 1, 1, WHITE);
  matrix.fillRoundRect(schkub_rightEyeTopX, schkub_rightEyeTopY + 6, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT + 1, 1, WHITE);

  matrix.setCursor(schkub_centerX - 2, schkub_centerY - SCHKUB_RADIUS - 1);
  matrix.setTextColor(WHITE);
  matrix.print("!");
}

void LedMatrix::shaky_drawEmotion() {
  matrix.setCursor(1, 0);
  matrix.setTextColor(YELLOW);
  matrix.println("SHAKY");

  matrix.fillCircle(schkub_centerX, schkub_centerY + 2, SCHKUB_RADIUS, BLUE);
  matrix.fillRoundRect(schkub_leftEyeTopX, schkub_leftEyeTopY + 4, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT - 1, 1, WHITE);
  matrix.fillRoundRect(schkub_rightEyeTopX, schkub_rightEyeTopY + 4, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT - 1, 1, WHITE);

  matrix.drawLine(schkub_centerX - 3, schkub_centerY - SCHKUB_RADIUS + 1 - 3, schkub_centerX + 3, schkub_centerY - SCHKUB_RADIUS + 1 + 3, RED);
  matrix.drawLine(schkub_centerX - 3, schkub_centerY - SCHKUB_RADIUS + 1 + 3, schkub_centerX + 3, schkub_centerY - SCHKUB_RADIUS + 1 - 3, RED);
}

void LedMatrix::sleep_drawEmotion() {
  matrix.setTextColor(WHITE);
  matrix.setTextSize(1);
  matrix.setCursor(0, 0);
  matrix.print("SLEEP");

  matrix.fillCircle(schkub_centerX, schkub_centerY, SCHKUB_RADIUS, BLUE);
  matrix.fillRoundRect(schkub_leftEyeTopX, schkub_leftEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);
  matrix.fillRoundRect(schkub_rightEyeTopX, schkub_rightEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);

  matrix.fillRoundRect(schkub_leftEyeTopX, schkub_leftEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);
  matrix.fillRoundRect(schkub_rightEyeTopX, schkub_rightEyeTopY, SCHKUB_EYE_WIDTH, SCHKUB_EYE_HEIGHT, 1, WHITE);
  matrix.setTextColor(WHITE);
  matrix.setTextSize(1);
  matrix.setCursor(schkub_centerX - SCHKUB_RADIUS - 3, schkub_centerY - 11);
  matrix.print("Z");
  matrix.setCursor(schkub_centerX - SCHKUB_RADIUS - 5, schkub_centerY - 3);
  matrix.print("Z");
  matrix.setCursor(schkub_centerX - SCHKUB_RADIUS - 7, schkub_centerY + 5);
  matrix.print("Z");
}
