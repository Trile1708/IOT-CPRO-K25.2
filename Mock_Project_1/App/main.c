// include header files
#include <stdio.h>
#include "Test.h"
#include "DHT22.h"


// global function definition
int main(void) {
const char *filename = "testdata.txt";

//original value
float temp_in =-100.4;
float hum_in = 10.3;

//create file data test
Create_Data_Test(filename, temp_in, hum_in);

//Create DHT22
if (!DHT_Init(filename))
   return -1;

//define data type
float temp_out=0.0f;
float hum_out=0.0f;

//Read data
if(DHT_Read_Temperature(&temp_out) && DHT_Read_Humidity(&hum_out)) {
      printf("Giá trị gốc: T=%.1f°C, H=%.1f %%\n", temp_in, hum_in);
        printf("Giá trị đọc được: T=%.1f°C, H=%.1f %%\n", temp_out, hum_out);
    } 
else {
        printf("Đọc dữ liệu thất bại!\n");
    }
    return 0;
}


