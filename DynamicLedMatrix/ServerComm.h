#ifndef ServerComm_h
#define ServerComm_h

#include <Arduino.h>
#include <WiFiNINA.h>
#include "Firebase_Arduino_WiFiNINA.h"

/**
  Handles the communication via Wifi between the Firebase Server and the
  microcontroller.
*/
class ServerComm {
public:
  ServerComm();

  void begin();
  void updateTempData(int temperature);
  void updateSensorData(bool activeNoice, bool activeVib);

private:
  const String TemperatureSensorPath = "temperature-sensor/";
  const String NoiceDetectionPath = "noise-detection/";
  const String VibrationDetectionPath = "vibration-detection/";
  const String LastSyncTimestampKey = "last-sync-timestamp";

  unsigned long lastPushToServerMillis = 0;
  FirebaseData firebaseData;

  int setTemperature(int value);
  int setNoiceDetectionActive(unsigned long long timestamp);
  int setVibDetectionActive(unsigned long long timestamp);
  unsigned long long updateLastSyncTimestamp();
  String convertUInt64ToString(unsigned long long value);
};

#endif /* ServerComm */