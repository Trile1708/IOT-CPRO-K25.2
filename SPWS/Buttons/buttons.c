#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "system_state.h"
#include "actuators.h"
#include "config.h"

void handle_mode_button(void) {
    if (system_status.mode == MODE_AUTO) {
        system_status.mode = MODE_MANUAL;
        turn_pump_off();
        update_led_status(LED_NORMAL);
        printf("[BUTTON] Switched to MANUAL mode\n");
    } else {
        system_status.mode = MODE_AUTO;
        printf("[BUTTON] Switched to AUTO mode\n");
    }
}

void handle_manual_water_button(void) {
    if (system_status.mode == MODE_MANUAL) {
        printf("[BUTTON] Manual watering for %d seconds\n", MANUAL_WATER_DURATION);
        turn_pump_on();
        update_led_status(LED_WATERING);
        sleep(MANUAL_WATER_DURATION);
        turn_pump_off();
        update_led_status(LED_NORMAL);
    }
}

void check_buttons(void) {
    char input;
    printf("[INPUT] Press 'm' (mode), 'w' (water), or 'Enter' to continue: ");
    input = getchar();
    while (getchar() != '\n');
    if (input == 'm') handle_mode_button();
    else if (input == 'w') handle_manual_water_button();
}