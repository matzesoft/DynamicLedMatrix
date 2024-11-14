#include <sys/_stdint.h>
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
  // Color definitions
  const uint16_t WHITE = 0xFFFF;
  const uint16_t BLACK = 0x0000;
  const uint16_t BLUE = 0x001F;
  const uint16_t RED = 0xF800;
  const uint16_t YELLOW = 0xFFE0;
  const uint16_t GREEN = 0x07E0;

  // General matrix variables
  uint16_t centerX;

  // Schkub matrix variables
  enum SchkubReactions {
    NONE,
    BLINK_EYES,
    LOOK_LEFT,
    LOOK_RIGHT
  };
  const uint8_t SCHKUB_REACTIONS_COUNT = 4;

  const uint16_t SCHKUB_RADIUS = 8;
  const uint16_t SCHKUB_EYE_HEIGHT = 5;
  const uint16_t SCHKUB_EYE_WIDTH = 3;
  const unsigned long SCHKUB_REACTION_DURATION = 1800;
  const unsigned long SCHKUB_REACTION_MIN_INTERVAL = 4000;
  const unsigned long SCHKUB_REACTION_MAX_INTERVAL = 8000;
  SchkubReactions schkub_reaction = SchkubReactions::NONE;
  uint16_t schkub_centerX;
  uint16_t schkub_centerY;
  uint16_t schkub_leftEyeTopX;
  uint16_t schkub_leftEyeTopY;
  uint16_t schkub_rightEyeTopX;
  uint16_t schkub_rightEyeTopY;
  unsigned long schkub_reactionStartedMillis = 0;
  unsigned long schkub_reactionInterval = 0;
  void schkub_drawBackground();
  void schkub_drawEyes();

  // NEUTRAL matrix variables
  uint16_t neutral_statusBarHeight;
  void neutral_drawEmotion(int temperature);
  void neutral_drawTemperature(int temperature);

  // TOO_LOUD matrix variables
  void tooLoud_drawEmotion();

  // SHAKY matrix variables
  void shaky_drawEmotion();
};

#endif /* LedMatrix */