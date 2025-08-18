#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "system_state.h"

void turn_pump_on(void);
void turn_pump_off(void);
void update_led_status(LEDState new_state);

#endif