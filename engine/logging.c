#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "logging.h"
#include "config.h"

static bool initialized = false;

#define MAX_TIME_STR_LEN    80

static void get_time_str(char *buffer)
{
    time_t rawtime;
    struct tm *info;

    time( &rawtime );
    info = localtime( &rawtime );
    strftime(buffer, MAX_TIME_STR_LEN,"%x - %I:%M%p", info);
}

log_priority_t get_priority_from_string(char *str)
{
    if (strncmp(str, priorities[DEBUG], strlen(priorities[DEBUG]))) {
        return DEBUG;
    } 
    if (strncmp(str, priorities[INFO], strlen(priorities[INFO]))) {
        return INFO;
    }
    if (strncmp(str, priorities[ERROR], strlen(priorities[ERROR]))) {
        return ERROR;
    }

    /* Should not reach here.
     * returns defaulr value */
    return INFO;
}

retval_t logging_init()
{
    FILE *f = fopen(config.log_file, "w");
    if (f != NULL) {
        initialized = true;
        fclose(f);
        return RV_SUCCESS;
    } else {
        printf("Could not open logging file %s\n", config.log_file);
        printf("Using default file: %s\n", DEFAULT_LOG_FILE);
        strcpy(config.log_file, DEFAULT_LOG_FILE);
    }

    return RV_ERROR;
}

void logging(log_priority_t log_level, char *msg)
{
    if (!initialized) {
        return;
    }

    if (log_level < config.log_level) {
        return;
    }

    char time_str[MAX_TIME_STR_LEN];
    get_time_str(time_str);
    
    FILE *f = fopen(config.log_file, "a+");
    if (f) {
        fprintf(f, "[%s] - %s\t%s\n", time_str, priorities[log_level], msg);
        fclose(f);
    }
}