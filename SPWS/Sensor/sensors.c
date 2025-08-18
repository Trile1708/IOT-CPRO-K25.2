#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sensors.h"

void read_sensors(SensorData *data) {
    data->moisture = rand() % 101;
    data->temperature = 25.0 + (rand() % 1000) / 100.0f;  // 25.00 - 35.00°C
    printf("[SENSOR] Moisture: %d%%, Temp: %.2f°C\n", data->moisture, data->temperature);
}