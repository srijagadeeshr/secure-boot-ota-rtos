#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define LOG_BOOT(fmt, ...)     printf("[BOOT] " fmt "\n", ##__VA_ARGS__)
#define LOG_OTA(fmt, ...)      printf("[OTA] " fmt "\n", ##__VA_ARGS__)
#define LOG_SEC(fmt, ...)      printf("[SECURITY] " fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)    printf("[ERROR] " fmt "\n", ##__VA_ARGS__)

#endif