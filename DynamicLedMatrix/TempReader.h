#ifndef TempReader_h
#define TempReader_h

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
