#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "joystic_config.h"
#include "motor_driver.h"

// contains one of MOTOR_COMM_* values
uint8_t move_command = MOTOR_COMM_STOP;

void joystick_task(void* arg);
void motors_task(void* arg);

void app_main() {
  ESP_LOGI("DEMO", "start!");
  xTaskCreate(joystick_task, "joystick task", 4096, NULL, 10, NULL);
  xTaskCreate(motors_task, "motors task", 4096, NULL, 9, NULL);
}

void joystick_task(void* arg) {
  adc_oneshot_unit_handle_t adc_unit_handle_xy;
  int x, y;

  adc_oneshot_create_unit(ADC_XY_UNIT, &adc_unit_handle_xy);

  // configure adc channels for x & y
  adc_oneshot_configure(adc_unit_handle_xy, ADC_X_CHAN, ADC_BITWIDTH_9,
                        ADC_ATTEN_DB_12);

  adc_oneshot_configure(adc_unit_handle_xy, ADC_Y_CHAN, ADC_BITWIDTH_9,
                        ADC_ATTEN_DB_12);

  while (1) {
    adb_oneshot_read_value(adc_unit_handle_xy, ADC_X_CHAN, &x);
    adb_oneshot_read_value(adc_unit_handle_xy, ADC_Y_CHAN, &y);

    move_command = MOTOR_COMM_STOP;

    if (y >= joystick_high_threshold) {
      move_command = MOTOR_COMM_FWD;
    } else if (y <= joystick_low_threshold) {
      move_command = MOTOR_COMM_BKWD;
    }

    if (x >= joystick_high_threshold) {
      move_command = MOTOR_COMM_ROTATE_LEFT;
    } else if (x <= joystick_low_threshold) {
      move_command = MOTOR_COMM_ROTATE_RIGHT;
    }

    vTaskDelay(pdMS_TO_TICKS(100));
  }

  // cleanup adc handle
  adc_oneshot_destroy_unit(adc_unit_handle_xy);
}

void motors_task(void* arg) {
  motors_config();

  while (1) {
    motors_send_command(move_command);
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}