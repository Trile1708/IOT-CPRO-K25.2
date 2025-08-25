#ifndef DHT22_H
#define DHT22_H

// include header files
#include <stdbool.h>

//Init,open file data
bool DHT_Init(const char *filename);

//read temperature
bool DHT_Read_Temperature(float *temp);

//read humidity
bool DHT_Read_Humidity(float *humidity);

#endif // DHT22_H

