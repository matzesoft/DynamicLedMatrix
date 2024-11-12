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

// Uploads the temperature to the Firebase server with the current timestamp as the key.
// The current timestamp is loaded via the `updateLastSyncTimestamp`-function.
// Returns -1 if an error occured.
int ServerComm::setTemperature(int value) {
  unsigned long long currentTimestamp = updateLastSyncTimestamp();
  if (currentTimestamp <= 0) {
    return -1;
  }

  String currentTimestampAsString = convertUInt64ToString(currentTimestamp);
  String tempDataPath = TemperatureSensorPath + currentTimestampAsString;

  if (!Firebase.setInt(firebaseData, tempDataPath, value)) {
    Serial.print("Unable to send temperature to Firebase server:");
    Serial.println(firebaseData.errorReason());
    return -1;
  }

  return 0;
}

// Updates the 'last-sync-timestamp' value to the current time and returns the timestamp.
// On errors the return value will be 0.
unsigned long long ServerComm::updateLastSyncTimestamp() {
  if (!Firebase.setTimestamp(firebaseData, LastSyncTimestampKey)) {
    return 0;
  }

  if (Firebase.getInt(firebaseData, LastSyncTimestampKey)) {
    if (firebaseData.dataType() == "uint64") {
      return firebaseData.uint64Data();
    }
  } else {
    Serial.print("Unable to last sync timestamp: ");
    Serial.println(firebaseData.errorReason());
  }

  return 0;
}

String ServerComm::convertUInt64ToString(unsigned long long value) {
  char buffer[32];
  sprintf(buffer, "%llu", value);

  return String(buffer);
}
