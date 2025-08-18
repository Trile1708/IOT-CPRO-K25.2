#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode;

typedef enum {
    PUMP_OFF,
    PUMP_ON
} PumpState;

typedef enum {
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LEDState;

typedef struct {
    int moisture;
    float temperature;
} SensorData;

typedef struct {
    SystemMode mode;
    PumpState pump_state;
    LEDState led_state;
} SystemStatus;

extern SystemStatus system_status;
extern SensorData sensor_data;

#endif