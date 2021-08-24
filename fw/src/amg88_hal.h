/**
 * \file            amg88_hal.h
 * \author          Mario Rubio (mario@mrrb.eu)
 * \brief           AMG88 sensor ESP32 HAL
 * \version         0.1
 * \date            2021-08-22
 */

#ifndef AMG88_HAL_H
#define AMG88_HAL_H

#include <stdint.h>
#include <stddef.h>

#include "amg88/amg88_defs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           I2C read
 * \param[in]       addr: 7-bit I2C slave address of the AMG device
 * \param[in]       reg_addr: address of internal register to read
 * \param[in]       len: number of bytes to read
 * \param[out]      data_buf: pointer to the read data value
 * \return          error code
 */
amg88_err_t amg88_hal_i2c_read(uint8_t addr, uint8_t reg_addr, size_t len, uint8_t* data_buf);

/**
 * \brief           I2C write
 * \param[in]       addr: 7-bit I2C slave address of the AMG device
 * \param[in]       reg_addr: address of internal register to write
 * \param[in]       len: number of bytes to write
 * \param[in]       data_buf: pointer to the write data value
 * \return          error code
 */
amg88_err_t amg88_hal_i2c_write(uint8_t addr, uint8_t reg_addr, size_t len, uint8_t* data_buf);

/**
 * \brief           Fill the dev struct with the HW related stuff
 * \param[in]       p_dev: Device struct pointer
 * \hideinitializer
 */
#define AMG88_HAL_HW_INIT(p_dev) {           \
    (p_dev)->write    = amg88_hal_i2c_write; \
    (p_dev)->read     = amg88_hal_i2c_read;  \
} while (0)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AMG88_HAL_H */