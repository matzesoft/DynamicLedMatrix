#ifndef NoiceDetection_h
#define NoiceDetection_h

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