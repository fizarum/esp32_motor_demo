### Demo of motor usage on esp32.

This demo shows implementation of simple locomotion based on ESP32, 2 motors and analog joystick.
Tested on `L298N` driver and mini `N20` motors, but should be ok for other configuration.

### Pinout

#### Input part:

| Joystick |  ESP32  |
|---------:|:-------:|
|        X | GPIO 25 |
|        Y | GPIO 26 |
|      GND |   GND   |
|      VCC |   3V3   |



#### Locomotive part:

| L298N |  ESP32  |
|------:|:-------:|
|  INT1 | GPIO 13 |
|  INT2 | GPIO 12 |
|  INT3 | GPIO 14 |
|  INT4 | GPIO 27 |


### Dependencies
This project uses `mini_hal_esp32` (https://github.com/fizarum/mini_hal_esp32.git) library for GPIO and ADC (joystick) API. 