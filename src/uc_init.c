/**
 * \file uc_init.c
 * \author Mario Rubio (mario@mrrb.eu)
 * \brief uC init stuff
 * \version 0.1
 * \date 2021-08-19
 */

#include <sntp.h>
#include <osapi.h>
#include <user_interface.h>

#include "uc_init.h"
#include "fast_gpio.h"
#include "simple_i2c.h"
#include "user_config.h"
#include "driver/uart.h"


status_t ICACHE_FLASH_ATTR
uc_init_uart() {
    uart_div_modify(UART0, UART_CLK_FREQ / BITRATE);
    os_delay_us(1000);

#ifdef DEBUG_PRINT_MODE
    os_printf("UART init - Ok\n");
#endif
    return STA_OK;
}

status_t ICACHE_FLASH_ATTR
uc_init_wifi() {
    station_config_t sta_cfg;
    uint8_t ssid[SSID_LENGTH] = SSID;
    uint8_t ssid_pw[SSID_PW_LENGTH] = SSID_PW;
    uint8_t hostname[HOSTNAME_LENGTH] = HOSTNAME;

    if(wifi_get_opmode() != STATION_MODE) {
        if (!wifi_set_opmode(STATION_MODE)) {
            return STA_ERR;
        }
	}	

    os_memcpy(&sta_cfg.ssid, ssid, SSID_LENGTH);
    os_memcpy(&sta_cfg.password, ssid_pw, SSID_PW_LENGTH);

    if (!wifi_station_set_config(&sta_cfg)) {
        return STA_ERR;
    }
    if (!wifi_station_set_hostname((char*)&hostname)) {
        return STA_ERR;
    }
    if (!wifi_station_connect()) {
        return STA_ERR;
    }
    os_delay_us(1000);

    wifi_set_sleep_type(MODEM_SLEEP_T);

#ifdef DEBUG_PRINT_MODE
    os_printf("WiFi init - Ok\n");
#endif
    return STA_OK;
}

status_t ICACHE_FLASH_ATTR
uc_init_gpio() {
    // GPIO2_OUTPUT_SET;

#ifdef DEBUG_PRINT_MODE
    os_printf("GPIO init - Ok\n");
#endif
    return STA_OK;
}

status_t ICACHE_FLASH_ATTR
uc_init_i2c() {
    uint8_t result;
    I2C_INIT(&result);

#ifdef DEBUG_PRINT_MODE
    os_printf("I2C init - Ok\n");
#endif
    return STA_OK;
}

status_t ICACHE_FLASH_ATTR
uc_init_sntp() {
#ifdef SNTP_SERVERNAME_0
    sntp_setservername(0, SNTP_SERVERNAME_0);
#endif

#ifdef SNTP_SERVERNAME_1
    sntp_setservername(1, SNTP_SERVERNAME_1);
#endif

#ifdef SNTP_SERVERNAME_2
    sntp_setservername(2, SNTP_SERVERNAME_2);
#endif

    sntp_set_timezone(SNTP_TIMEZONE);
    sntp_init();

#ifdef DEBUG_PRINT_MODE
    os_printf("SNTP init - Ok\n");
#endif
    return STA_OK;
}
