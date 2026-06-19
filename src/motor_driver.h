#pragma once

#include <gpio_hal.h>

// motor pins
#define MOTOR_INT1 13
#define MOTOR_INT2 12
#define MOTOR_INT3 14
#define MOTOR_INT4 27

// motor commands
#define MOTOR_COMM_STOP 0
#define MOTOR_COMM_FWD 1
#define MOTOR_COMM_BKWD 2
#define MOTOR_COMM_LEFT 3
#define MOTOR_COMM_RIGHT 4
#define MOTOR_COMM_ROTATE_LEFT 5
#define MOTOR_COMM_ROTATE_RIGHT 6

#ifdef __cplusplus
extern "C" {
#endif

typedef enum motor_command_t {
  OFF,
  FORWARD,
  BACKWARD,
} motor_command_t;

typedef enum motor_type_t {
  LEFT,
  RIGHT,
} motor_type_t;

static void motors_config() {
  gpio_configure_and_set(MOTOR_INT1, GPIO_MODE_OUTPUT, 0);
  gpio_configure_and_set(MOTOR_INT2, GPIO_MODE_OUTPUT, 0);
  gpio_configure_and_set(MOTOR_INT3, GPIO_MODE_OUTPUT, 0);
  gpio_configure_and_set(MOTOR_INT4, GPIO_MODE_OUTPUT, 0);
}

static void motor_send_command(motor_type_t type, motor_command_t command) {
  static uint8_t pin1, pin2;

  switch (type) {
    case LEFT:
      pin1 = MOTOR_INT1;
      pin2 = MOTOR_INT2;
      break;

    default:
      pin1 = MOTOR_INT4;
      pin2 = MOTOR_INT3;
      break;
  }

  switch (command) {
    case FORWARD:
      gpio_set(pin1, 0);
      gpio_set(pin2, 1);
      break;

    case BACKWARD:
      gpio_set(pin1, 1);
      gpio_set(pin2, 0);
      break;

    default:
      gpio_set(pin1, 0);
      gpio_set(pin2, 0);
      break;
  }
}

/**
 * @brief send command to 2 motors
 * @param command check available commands in MOTOR_COMM_* definitions
 */
static void motors_send_command(uint8_t command) {
  switch (command) {
    case MOTOR_COMM_FWD:
      motor_send_command(LEFT, FORWARD);
      motor_send_command(RIGHT, FORWARD);
      break;

    case MOTOR_COMM_BKWD:
      motor_send_command(LEFT, BACKWARD);
      motor_send_command(RIGHT, BACKWARD);
      break;

    case MOTOR_COMM_LEFT:
      motor_send_command(LEFT, FORWARD);
      motor_send_command(RIGHT, BACKWARD);
      break;

    case MOTOR_COMM_RIGHT:
      motor_send_command(LEFT, BACKWARD);
      motor_send_command(RIGHT, FORWARD);
      break;

    case MOTOR_COMM_ROTATE_LEFT:
      motor_send_command(LEFT, OFF);
      motor_send_command(RIGHT, FORWARD);
      break;

    case MOTOR_COMM_ROTATE_RIGHT:
      motor_send_command(RIGHT, OFF);
      motor_send_command(LEFT, FORWARD);
      break;

    default:
      motor_send_command(LEFT, OFF);
      motor_send_command(RIGHT, OFF);
      break;
  }
}

#ifdef __cplusplus
}
#endif
