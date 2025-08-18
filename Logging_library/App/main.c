// include header files
#include "logger.h"




// global function definition
int main(void) {//khởi tạo logger: ghi ra file log.txt và lọc từ LOG_INFO trở lên;
  if (logger_init("log.txt", LOG_INFO) != 0) {
    return -1;
  }
    log_message(LOG_DEBUG, "This is a debug message, should not appear with LOG_INFO filter.");
    log_message(LOG_INFO, "Application started successfully.");
    log_message(LOG_WARNING, "Low disk space detected.");
    log_message(LOG_ERROR, "Failed to connect to database.");

//Thay đổi mức lọc để hiển thị debug
  logger_set_level(LOG_DEBUG);
  log_message(LOG_DEBUG, "Now debug logs are visible");
  logger_close();
    return 0;
}


