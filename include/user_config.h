// Debug
#ifndef DEBUG_PRINT_MODE
#define DEBUG_PRINT_MODE
#endif

// UART
#define	BITRATE 115200

// Network
#define SSID     "mrrb_dev"
#define SSID_PW  "WhatTimeIsIt?AdventureTime!-_-"
#define HOSTNAME "thermal-AMG8833"

#define SSID_LENGTH     32
#define SSID_PW_LENGTH  32
#define HOSTNAME_LENGTH 32

// #define WEB_ENABLE

// I2C
// View header $(PROJECT_ROOT)/driver/driver/i2c_master.h

// Status LED
#define STATUS_LED_ENABLE
#define STATUS_LED_TIME_ON  4
#define STATUS_LED_TIME_OFF 30000

// Network
#define SNTP_SERVERNAME_0 "0.es.pool.ntp.org"
#define SNTP_SERVERNAME_1 "1.es.pool.ntp.org"
#define SNTP_TIMEZONE     1

// Other
#define USE_OPTIMIZE_PRINTF
// #define MEMLEAK_DEBUG
