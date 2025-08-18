#ifndef LOGGER_H
#define LOGGER_H

// include header files
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

//local data type
// Cap do log (theo syslog)
typedef enum {
    LOG_EMERGENCY= 0,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

// local variables
//Khoi tao Logger
int logger_init(const char *file_path, LogLevel min_level);

// Dong logger
void logger_close(void);

//Thay doi muc loc logger
void logger_set_level(LogLevel level);

//Ghi log (noi bo)
void logger_log(LogLevel level, const char *file, int line, const char *fmt,...);

//Macro tien loi
#define log_message(level, fmt, ...) \
logger_log(level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)






#endif // LOGGER_H

