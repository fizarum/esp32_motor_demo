#pragma once

#include <adc_hal.h>

// for x (GPIO_25): ADC2_CH8
// for y (GPIO_26): ADC2_CH9
#define ADC_XY_UNIT ADC_UNIT_2
#define ADC_X_CHAN ADC_CHANNEL_8
#define ADC_Y_CHAN ADC_CHANNEL_9

// because we have ADC_BITWIDTH_9 as 9 bytes (max value 512)
const uint16_t joystick_idle_val = 512 / 2;
const uint16_t joystick_threshold = 70;
const uint16_t joystick_low_threshold = joystick_idle_val - joystick_threshold;
const uint16_t joystick_high_threshold = joystick_idle_val + joystick_threshold;