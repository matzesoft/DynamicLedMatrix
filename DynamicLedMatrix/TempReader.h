#ifndef TempReader_h
#define TempReader_h

/**
  Provides the temperature via the build in temperature sensor of the
  Arduino Nano RP2040 Connect. The temperature can be read via the
  `temp` variable. If there was an error reading the temperature,
  the value will be set to -255.
*/
class TempReader {
public:
  static const int ErrorTempValue = -255;
  int temp = ErrorTempValue;

  TempReader();

  void begin();
  void update();

private:
  int internalToSourroundingTemp(int internalTemp);
};

#endif /* TempReader */
