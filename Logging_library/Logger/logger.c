// include header files
#include "logger.h"
#include <string.h>
#include <stdlib.h>


//Trang thai logger
static FILE *log_file=NULL;
static LogLevel current_level=LOG_DEBUG; // mac dinh in tat ca

//local data type
//ten cac cap do log
static const char *level_names[] = {
    "EMERGENCY",
    "ALERT",
    "CRITICAL",
    "ERROR",
    "WARNING",
    "NOTICE",
    "INFO",
    "DEBUG"
};


// local variables
// Khoi tao logger
int logger_init(const char *file_path, LogLevel min_level){
current_level=min_level;
    if (file_path !=NULL) {
        log_file =fopen(file_path, "a");
        if (!log_file) {
            fprintf(stderr, "[LOGGER] Failed to open log file: %s\n", file_path);
            return -1;
        }
    }
    return 0;
}
//Đóng logger
void logger_close(void) {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

//Thay doi mức lọc log
void logger_set_level(LogLevel level) {
    current_level = level;
}

//Lay timestamp hien tai
static void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

//Ghi Log
void logger_log(LogLevel level, const char *file, int line, const char *fmt,...) {
  if (level>current_level) {
     return;
  }
// local constants
char timestamp[20];
get_timestamp(timestamp, sizeof(timestamp));

char message[1024];
va_list args;
va_start(args, fmt);
vsnprintf(message, sizeof(message), fmt, args);
va_end(args);

//định dạng dòng log
char log_line[1200];
snprintf(log_line, sizeof(log_line), "[%s] [%s] [%s:%d] - %s\n", timestamp, level_names[level], file, line, message);


// global function definition
//Ghi ra console
 if (level <= LOG_ERROR) {
    fprintf(stderr, "%s", log_line); //loi ->stderr
}
 else {
    fprintf(stdout, "%s", log_line); //thong thuong ->stdout
}

//Ghi ra file (neu co)
 if (log_file) {
    fprintf(log_file, "%s", log_line);
    fflush(log_file);
}
}