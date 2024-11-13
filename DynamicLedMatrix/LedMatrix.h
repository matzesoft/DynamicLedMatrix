#ifndef LedMatrix_h
#define LedMatrix_h

#include <Adafruit_Protomatter.h>
#include "EmotionsManager.h"

class LedMatrix {
public:
  LedMatrix();

  void begin();
  void update(int temperature, Emotion emotion);

private:
  void drawNeutralEmotion(int temperature);
  void drawTooLoudEmotion();
  void drawShakyEmotion();
};

#endif /* LedMatrix */