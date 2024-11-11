#ifndef VibrationDetection_h
#define VibrationDetection_h

class VibrationDetection {
  public:
  boolean activeVib = false;

  VibrationDetection();

  void begin();
  void update();

  private:
  static constexpr float Threshold = 1.5;

  boolean accelerationsOverThreshold(float x, float y, float z);
  void serialPrintAcclerations(float x, float y, float z);
};

#endif /* VibrationDetection */
