#ifndef VibrationDetection_h
#define VibrationDetection_h

/**
  Uses the build in accelerate sensor of the Arduino Nano RP2040 Connect
  to detect vibrations. If the detect vibration is about the defined
  `Threshold`, the `activeVib` variable will be set to true.
*/
class VibrationDetection {
public:
  boolean activeVib = false;

  VibrationDetection();

  void begin();
  void update();

private:
  static constexpr float Threshold = 1.1;

  boolean accelerationsOverThreshold(float x, float y, float z);
  void serialPrintAcclerations(float x, float y, float z);
};

#endif /* VibrationDetection */
