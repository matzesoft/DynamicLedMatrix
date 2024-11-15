#ifndef NoiceDetection_h
#define NoiceDetection_h

/**
  Uses the build in microphone of the Arduino Nano RP2040 Connect
  to detect nearby noices. If the detect noise is about the defined
  `Threshold`, the `activeNoise` variable will be set to true.
*/
class NoiceDetection {
public:
  bool activeNoise = false;

  NoiceDetection();

  void begin();
  void update();

private:
  static constexpr float Threshold = 1400.0;

  float calculateRMS(short *samples, int numSamples);
};

#endif /* NoiceDetection */