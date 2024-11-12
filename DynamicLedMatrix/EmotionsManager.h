#ifndef EmotionsManager_h
#define EmotionsManager_h

enum Emotion {
  NEUTRAL,
  TOO_LOUD,
  SHAKY
};

class EmotionsManager {
public:
  Emotion emotion = Emotion::NEUTRAL;

  EmotionsManager();

  void begin();
  void update(int temperature, bool activeNoise, bool activeVibration);

private:
};

#endif /* EmotionsManager */
