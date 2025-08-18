#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "system_state.h"
#include "sensors.h"
#include "buttons.h"
#include "watering_logic.h"
#include "actuators.h"
#include "config.h"

int main() {
    srand(time(NULL));
    printf("[INIT] Smart Plant Watering System Started.\n");

    while (1) {
        check_buttons();
        read_sensors(&sensor_data);

        if (system_status.mode == MODE_AUTO) {
            handle_auto_mode();
        }

        update_led_status(system_status.led_state);
        sleep(SENSOR_CHECK_INTERVAL);
    }

    return 0;
}