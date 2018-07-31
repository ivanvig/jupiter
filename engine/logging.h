#ifndef __LOGGING_H__
#define __LOGGING_H__

#include "board.h"

typedef enum {
    DEBUG = 0,
    INFO,
    ERROR,
} log_priority_t;

#define MAX_PRIORITY_LEN 8
static const char priorities[][MAX_PRIORITY_LEN] = {
    "[DEBUG]",
    "[INFO]",
    "[ERROR]"
};


retval_t logging_init();
void logging(log_priority_t log_level, char *msg);
log_priority_t get_priority_from_string(char *str);

#define LOG(lev, msg)   (logging(lev, msg))

#endif
