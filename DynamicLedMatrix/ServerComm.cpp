#include "ServerComm.h"
#include "Secrets.h"

/* --------------- PUBLIC FUNCTIONS --------------- */

ServerComm::ServerComm() {}

void ServerComm::begin() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASS);
  Firebase.reconnectWiFi(true);
}

void ServerComm::update(int temperature) {
  setTemperature(temperature);
}

/* --------------- PRIVATE FUNCTIONS --------------- */

int ServerComm::setTemperature(int value) {
  if (!Firebase.setInt(firebaseData, TemperatureSensorPath + "temp", value)) {
    Serial.print("Unable to send temperature to Firebase server:");
    Serial.println(firebaseData.errorReason());
    return -1;

  } else if (!Firebase.setTimestamp(firebaseData, TemperatureSensorPath + "timestamp")) {
    Serial.print("Unable to set timestamp for the temperature sensor on the Firebase server:");
    Serial.println(firebaseData.errorReason());
    return -1;
  }

  return 0;
}
