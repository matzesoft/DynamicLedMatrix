# DynamicLedMatrix

### Arduino Nano RP2040 Connect with Protomatter Library
Follow these steps to use the [Arduino Nano RP2040 Connect](https://docs.arduino.cc/hardware/nano-rp2040-connect/) with the [Protomatter](https://github.com/adafruit/Adafruit_Protomatter) Library from Adafruit. You have to use the [arduino-pico device support package](https://github.com/earlephilhower/arduino-pico). The official Arduino Mbed OS Nano Boards **will not** work.

#### 1️⃣ Locate the file
Locate the [file](https://github.com/earlephilhower/arduino-pico/blob/master/variants/arduino_nano_connect/pins_arduino.h) for the hardware pins definition. On macOS this could be located here:
`~/Library/Arduino15/packages/rp2040/hardware/rp2040/4.2.0/variants/arduino_nano_connect/pins_arduino.h`

#### 2️⃣ Add Arduino Header include
Add `#include "Arduino.h"` right after `pragma once` in the _pins_aduino.h_ file:
```
...
#pragma once

#include "Arduino.h" // <--- ADD THIS LINE TO THE FILE
```

#### 3️⃣ Remove NinaPins include
Go the _bottom_ of the file and remove or comment the include for the `nina-pins.h`:
```
...
#define CRYPTO_WIRE Wire

#define USB_MAX_POWER (500)
// #include "nina_pins.h" // <--- REMOVE OR COMMENT THIS LINE
```

#### Wait before updating the device library!
When you update the device library these changes will be reverted and you have to redo them. This guide should be only applied if you already have an Arduino Nano RP2040 Connect and still want to use the Protomatter library. These changes could also cause other libraries to not function correct anymore.
