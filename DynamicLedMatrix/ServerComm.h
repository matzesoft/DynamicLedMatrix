#ifndef ServerComm_h
#define ServerComm_h

#include <Arduino.h>
#include <WiFiNINA.h>
#include "Firebase_Arduino_WiFiNINA.h"

class ServerComm {
public:
  ServerComm();

  void begin();
  void update(int temperature);

private:
  const String TemperatureSensorPath = "temperature-sensor/";
  unsigned long lastPushToServerMillis = 0;
  FirebaseData firebaseData;

  int setTemperature(int value);
};

#endif /* ServerComm */