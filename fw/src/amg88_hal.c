/**
 * \file            amg88_hal.c
 * \author          Mario Rubio (mario@mrrb.eu)
 * \brief           AMG88 sensor ESP32 HAL
 * \version         0.1
 * \date            2021-08-22
 */

#include "amg88_hal.h"

#include <string.h>

#include "esp_err.h"
#include "driver/i2c.h"

#include "user_config.h"

/* Vars */
// static char* log_src = "amg88_hal";


amg88_err_t
amg88_hal_i2c_read(uint8_t addr, uint8_t reg_addr, size_t len, uint8_t* data_buf) {
    esp_err_t ret;

    ret = i2c_master_write_read_device(0, addr, &reg_addr, 1, data_buf, len, CFG_I2C_TIMEOUT / portTICK_RATE_MS);

    if (ret == ESP_OK) {
        return AMG88_OK;
    } else if (ret == ESP_FAIL || ret == ESP_ERR_INVALID_STATE) {
        return AMG88_ERR_I2C;
    } else if (ret == ESP_ERR_TIMEOUT) {
        return AMG88_ERR_TIMEOUT;
    } else {
        return AMG88_ERR;
    }

    return AMG88_ERR;
}

amg88_err_t
amg88_hal_i2c_write(uint8_t addr, uint8_t reg_addr, size_t len, uint8_t* data_buf) {
    uint8_t all_data_buf[len + 1];
    esp_err_t ret;

    memcpy(all_data_buf + 1, data_buf, sizeof(uint8_t) * len);
    all_data_buf[0] = reg_addr;

    all_data_buf[0] = reg_addr;
    all_data_buf[1] = data_buf[0];

    ret = i2c_master_write_to_device(0, addr, all_data_buf, len + 1, CFG_I2C_TIMEOUT / portTICK_RATE_MS);

    if (ret == ESP_OK) {
        return AMG88_OK;
    } else if (ret == ESP_FAIL || ret == ESP_ERR_INVALID_STATE) {
        return AMG88_ERR_I2C;
    } else if (ret == ESP_ERR_TIMEOUT) {
        return AMG88_ERR_TIMEOUT;
    }

    return AMG88_ERR;
}
