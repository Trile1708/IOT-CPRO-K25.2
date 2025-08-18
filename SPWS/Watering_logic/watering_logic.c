#include <stdio.h>
#include <unistd.h>
#include "watering_logic.h"
#include "system_state.h"
#include "actuators.h"
#include "config.h"

void handle_auto_mode(void) {
    if (sensor_data.moisture < MOISTURE_MIN_THRESHOLD) {
        printf("[LOGIC] Moisture too low, starting watering.\n");
        turn_pump_on();
        update_led_status(LED_WATERING);
        sleep(MAX_WATERING_TIME);
        turn_pump_off();
        if (sensor_data.moisture < MOISTURE_MIN_THRESHOLD) {
            update_led_status(LED_LOW_MOISTURE_ALERT);
        } else {
            update_led_status(LED_NORMAL);
        }
    }
}