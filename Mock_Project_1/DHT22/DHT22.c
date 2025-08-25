// include header files
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "DHT22.h"
// local constants
static FILE *dataFile =NULL;


//Simulates the intialization of a GPIO pin and prepare data file
bool DHT_Init(const char *filename) {
   dataFile= fopen(filename, "r");
   if (dataFile ==NULL) {
     printf ("Không thể mở file dữ liệu: %s\n", filename);
     return false;
   }
   printf("Khởi tạo DHT22 thành công,file '%s' đã sẵn sàng.\n", filename);
   return true;
}
    

//Function read 40 bit (5 byte) from file
static bool DHT_ReadRaw(uint8_t *data) {
    if(data == NULL) {
        printf ("File chưa mở!\n");
        return false;
    }
  fseek(dataFile, 0, SEEK_SET);  //Reset into 1st line after reading
 int ch;
    for (int i = 0; i < 5; i++) {
        data[i] = 0;
        for (int b = 7; b >= 0; b--) {
            // Bỏ qua xuống dòng / khoảng trắng
            do {
                ch = fgetc(dataFile);
                if (ch == EOF) {
                    printf("EOF khi đọc byte %d, bit %d\n", i, b);
                    return false;
                }
            } while (ch == '\n' || ch == '\r' || ch == ' ');

            if (ch == '1') {
                data[i] |= (1 << b);
            } else if (ch != '0') {
                printf("Ký tự không hợp lệ: %c (0x%02X)\n", ch, ch);
                return false;
            }
        }
    }

    printf("Raw bytes đọc được: %02X %02X %02X %02X %02X\n",
           data[0], data[1], data[2], data[3], data[4]);
        return true;
}

//function define data array and read 2 byte temperature
bool DHT_Read_Temperature(float *temp) {
    uint8_t data[5];
    fseek(dataFile, 0, SEEK_SET);
    if (!DHT_ReadRaw(data)) {
        return false;
    }

     uint8_t hum_high = data[0];
     uint8_t hum_low = data[1];
     uint8_t temp_high = data[2];
     uint8_t temp_low = data[3];
     uint8_t checksum = data[4];

     if (((hum_high + hum_low + temp_high + temp_low) & 0xFF)!=checksum) {
      printf("Checksum lỗi! HumH=%02X HumL=%02X TempH=%02X TempL=%02X Checksum=%02X (expected=%02X)\n",
               hum_high, hum_low, temp_high, temp_low, checksum,
               (hum_high + hum_low + temp_high + temp_low) & 0xFF);
     return false;
   }
   int raw_temp = ((temp_high & 0x7F) <<8) | temp_low;
      *temp= raw_temp / 10.0f;
      
   if (temp_high & 0x80) {
       *temp= -*temp; //negative celsius
   }
   return true;
}
   

//function read humidity
bool DHT_Read_Humidity (float *humidity) {
    uint8_t data[5];
    fseek(dataFile,0,SEEK_SET);
    if (!DHT_ReadRaw(data))
         return false;
     uint8_t hum_high = data[0];
     uint8_t hum_low = data[1];
     uint8_t temp_high = data[2];
     uint8_t temp_low = data[3];
     uint8_t checksum = data[4];

     if (((hum_high + hum_low + temp_high + temp_low) & 0xFF)!=checksum) {
      printf("Checksum lỗi! HumH=%02X HumL=%02X TempH=%02X TempL=%02X Checksum=%02X (expected=%02X)\n",
               hum_high, hum_low, temp_high, temp_low, checksum,
               (hum_high + hum_low + temp_high + temp_low) & 0xFF);
     return false;
     }
     int raw_hum =(hum_high <<8) |hum_low;
     *humidity =raw_hum / 10.0f;
   return true;
}