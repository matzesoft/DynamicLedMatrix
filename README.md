# DynamicLedMatrix
DynamicLedMatrix is an IoT student project to dynamically display sensor data on an Adafruit RGB Matrix and web dashboard.

### Architecture
The system contains of four components:

```
 [ Next.js Webapp ]
         |
         |
[ Firebase Server ]
         |        
         |        
⎡   Arduino Nano   ⎤ <---> [ LED Matrix ]
⎜ ---------------- ⎟
⎜    Temp Sensor   ⎟
⎜ Acclerate Sensor ⎟
⎣    Microphone    ⎦
```

**Arduino Nano:** Sends the sensor data to the Firebase Server and communicates with the LED Matrix. The sensor data contains of: Temperature, Noice via microphone and Vibrations via acclerate sensor. All three sensors are build into the microcontroller.

**LED Matrix:** Displays the sensor data in a funny way. For example: If the microcontroller detects loud noice in the sourround, there will be presented a funny message on the LED Matrix with a cute character complaining.

**Firebase Server:** Stores the data temperature, noice and vibration data via the Realtime Database.

**Next.js Webapp:** Allows to see an curve of the last temperature values. Aswell there is a bar chart showing the noice and vibration data.

## Hardware
**Arduino:** Arduino Nano RP2040 Connect ([docs.arduino.cc](https://docs.arduino.cc/hardware/nano-rp2040-connect/)) \
**LED Matrix:** 32x32 RGB LED Matrix Panel ([berrybase.de](https://www.berrybase.de/32x32-rgb-led-matrix-panel-5mm-raster))

### Arduino Nano RP2040 Connect with Protomatter Library
Follow these steps to use the [Arduino Nano RP2040 Connect](https://docs.arduino.cc/hardware/nano-rp2040-connect/) with the [Protomatter](https://github.com/adafruit/Adafruit_Protomatter) Library from Adafruit: [gist.github.com](https://gist.github.com/matzesoft/b794ab7975aec84a40eef546e0827b2a)
