#ifndef EmotionsManager_h
#define EmotionsManager_h

enum Emotion {
  // Neutral emotion
  NEUTRAL,

  // Active emotions
  TOO_LOUD,
  SHAKY
};

class EmotionsManager {
public:
  Emotion emotion = Emotion::NEUTRAL;

  EmotionsManager();

  void begin();
  void update(bool activeNoise, bool activeVibration);

private:
  /*
  Timeline: Sequence of an emotion getting actived and going back to NEUTRAL.

  |---------- HoldEmotionMillis --------->|---- StayNeutralAfterEmotionMillis --->|
  |                ACTIVE                 |                NEUTRAL                |
  |                                                                               |
  |-------------------------- ReallowActiveEmotionsMillis ----------------------->| 

  */

  // Defines how long an active emotion should be presented before resetting back to NEUTRAL.
  const unsigned long HoldEmotionMillis = 10 * 1000;  // 10 sec

  // Defines how long to stay in NEUTRAL after there was an active emotion.
  const unsigned long StayNeutralAfterEmotionMillis = 6 * 1000;  // 6 sec

  // Defines how long to wait before a new emotion can be activated, after the previous one started.
  const unsigned long ReallowActiveEmotionsMillis = HoldEmotionMillis + StayNeutralAfterEmotionMillis;

  // The millis value since the emotion was changed from NEUTRAL to another one.
  unsigned long lastEmotionChangeMillis = 0;

  void checkForActiveEmotion(bool activeNoise, bool activeVibration);
  Emotion getEmotionBasedOnSensorData(bool activeNoise, bool activeVibration);
};

#endif /* EmotionsManager */
