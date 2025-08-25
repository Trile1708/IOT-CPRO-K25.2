// include header files
#include <stdio.h>
#include <stdint.h>
#include "Test.h"
#include <math.h>

// generates a data file for testing
void Create_Data_Test(const char *filename, float temp, float humidity)
{
  FILE *fp= fopen(filename, "w");
   if(fp == NULL){
       perror("Không thể tạo file test");
         return;
   }

   //converting humidity and temperature by protocol DHT22
    uint16_t hum_val= (uint16_t)(humidity * 10);
    uint16_t temp_val= (uint16_t)(fabs(temp) * 10);

    uint8_t hum_high = (hum_val >> 8) & 0xFF;
    uint8_t hum_low = hum_val & 0xFF;

    uint8_t temp_high = (temp_val >> 8) & 0x7F;
    uint8_t temp_low = temp_val & 0xFF;

    // If temp is negavtive,set bit MSB at temp_high
    if (temp<0) {
        temp_high |= 0x80; //set MSB=1
    }
    uint8_t checksum= (hum_high + hum_low + temp_high + temp_low) & 0xFF;
     
    //Pack data into arrays (40 line)
    uint8_t data[5]= {hum_high, hum_low, temp_high, temp_low, checksum};

    //Debug print data byte after create
    printf("Bytes trước khi ghi: %02X %02X %02X %02X %02X\n",
           data[0], data[1], data[2], data[3], data[4]);

    for (int i=0;i<5;i++) {
        for (int b=7; b>=0; b--) {
            int bit =(data[i] >>b) & 1;
            fprintf(fp, "%d\n", bit);
        }
    }
    fclose(fp);
    printf("File test '%s' đã được tạo thành công với %d dòng.\n", filename, 5 * 8);
}
