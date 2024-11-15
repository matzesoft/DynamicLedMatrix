#include <Arduino.h>

#include "EmotionsManager.h"

/* --- PUBLIC FUNCTIONS --- */

EmotionsManager::EmotionsManager() {}

void EmotionsManager::begin() {
}

void EmotionsManager::update(bool activeNoise, bool activeVibration) {
  unsigned long currentMillis = millis();

    if (activeNoise || activeVibration) {
        lastActivityMillis = currentMillis;
    }
    
    // Enter sleep state after 3 minutes of inactivity
    if (currentMillis - lastActivityMillis >= InactivityBeforeSleepMillis) { 
        emotion = Emotion::SLEEP;
        return;
    }

  if (currentMillis - lastEmotionChangeMillis >= ReallowActiveEmotionsMillis) {
    checkForActiveEmotion(activeNoise, activeVibration);

  } else if (currentMillis - lastEmotionChangeMillis >= HoldEmotionMillis) {
    emotion = Emotion::NEUTRAL;
  }
}

/* --- PRIVATE FUNCTIONS --- */

void EmotionsManager::checkForActiveEmotion(bool activeNoise, bool activeVibration) {
  emotion = getEmotionBasedOnSensorData(activeNoise, activeVibration);

  if (emotion != Emotion::NEUTRAL) {
    lastEmotionChangeMillis = millis();
  }
}

Emotion EmotionsManager::getEmotionBasedOnSensorData(bool activeNoise, bool activeVibration) {
  if (activeVibration) {
    return Emotion::SHAKY;
  }

  if (activeNoise) {
    return Emotion::TOO_LOUD;
  }

  return Emotion::NEUTRAL;
}