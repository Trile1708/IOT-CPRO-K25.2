#include <stdio.h>
#include "actuators.h"

void turn_pump_on(void) {
    system_status.pump_state = PUMP_ON;
    printf("[ACTUATOR] Pump ON\n");
}

void turn_pump_off(void) {
    system_status.pump_state = PUMP_OFF;
    printf("[ACTUATOR] Pump OFF\n");
}

void update_led_status(LEDState new_state) {
    system_status.led_state = new_state;
    switch (new_state) {
        case LED_NORMAL: printf("[LED] GREEN - Normal\n"); break;
        case LED_WATERING: printf("[LED] YELLOW - Watering\n"); break;
        case LED_LOW_MOISTURE_ALERT: printf("[LED] RED - Low Moisture\n"); break;
        case LED_ERROR: printf("[LED] RED BLINK - ERROR\n"); break;
    }
}