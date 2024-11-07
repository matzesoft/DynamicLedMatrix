#include <Arduino_LSM6DSOX.h>

void setup() {
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  // if (IMU.temperatureAvailable())
  // {
  //   int temperature_deg = 0;
  //   IMU.readTemperature(temperature_deg);

  //   Serial.print("LSM6DSOX Temperature = ");
  //   Serial.print(temperature_deg);
  //   Serial.println(" °C");
  // }

  float x, y, z;

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(", y: ");
    Serial.print(y);
    Serial.print(", z: ");
    Serial.println(z);
  }


  delay(500);
}
