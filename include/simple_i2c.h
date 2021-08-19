/**
 * \file simple_i2c.h
 * \author Mario Rubio (mario@mrrb.eu)
 * \brief Macros to quickly use the SW_I2C communication
 * \version 0.2
 * \date 2021-08-19
 */

#ifndef SIMPLE_I2C_H
#define SIMPLE_I2C_H

#include <c_types.h>
#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define I2C_DELAY i2c_master_wait

typedef enum i2c_start_op {
    I2C_OP_WRITE = 0,
    I2C_OP_READ  = 1,
} i2c_start_op_t;

/**
 * \brief           Init the software I2C bus
 * \param[out]      p_result: Result of the operation
 * \hideinitializer
 */
#define I2C_INIT(p_result) do { \
    i2c_master_gpio_init();     \
    i2c_master_init();          \
    *p_result = 1;              \
} while(0)

/**
 * \brief           Start a I2C transaction
 * \param[in]       addr: I2C slave address
 * \param[in]       op: i2c_start_op_t. I2C operation read/write
 * \param[out]      p_result: Result of the operation
 * \hideinitializer
 */
#define I2C_START(addr, op, p_result) do { \
    i2c_master_start();                    \
    i2c_master_writeByte((addr<<1) + op);  \
    *p_result = i2c_master_checkAck();     \
} while(0)

/**
 * \brief           Start a READ I2C transaction
 * \param[in]       addr: I2C slave address
 * \param[out]      p_result: Result of the operation
 * \hideinitializer
 */
#define I2C_START_READ(addr, p_result) do { \
    I2C_START(addr, I2C_OP_READ, p_result); \
} while(0)

/**
 * \brief           Start a WRITE I2C transaction
 * \param[in]       addr: I2C slave address
 * \param[out]      p_result: Result of the operation
 * \hideinitializer
 */
#define I2C_START_WRITE(addr, p_result) do { \
    I2C_START(addr, I2C_OP_WRITE, p_result); \
} while(0)

/**
 * \brief           Stop the I2C transaction
 * \param[out]      p_result: Result of the operation
 * \hideinitializer
 */
#define I2C_STOP(p_result) do { \
    i2c_master_stop();          \
    *p_result = 1;              \
} while(0)

/**
 * \brief           Send a byte to the I2C slave
 * \param[in]       data: Byte to send
 * \param[out]      p_result: Result of the operation
 * \hideinitializer
 */
#define I2C_WRITE_BYTE(data, p_result) do { \
    i2c_master_writeByte(data);             \
    *p_result = i2c_master_checkAck();      \
} while(0)

/**
 * \brief           Send `data_len` byte(s) to the I2C slave
 * \param[in]       p_data: Byte(s) to send
 * \param[in]       data_len: Number of bytes
 * \param[out]      p_result: Result of the operation
 * \hideinitializer
 */
#define I2C_WRITE_BYTES(p_data, data_len, p_result) do { \
    if (p_data == NULL || data_len < 1) {                \
        *p_result = 0;                                   \
    } else {                                             \
        for (size_t i = 0; i < data_len; ++i) {          \
            I2C_WRITE_BYTE(*(p_data+i), p_result);       \
            if (!(*p_result)) {                          \
                break;                                   \
            }                                            \
        }                                                \
    }                                                    \
} while(0)

/**
 * \brief           Read a byte from the I2C slave
 * \param[in]       p_data: Readed byte
 * \param[out]      p_result: Result of the operation
 * \hideinitializer
 */
#define I2C_READ_BYTE(p_data, p_result) do { \
    if (p_data == NULL) {                    \
        *p_result = 0;                       \
    } else {                                 \
        *p_data = i2c_master_readByte();     \
        i2c_master_send_nack();              \
        *p_result = 1;                       \
    }                                        \
} while(0)

/**
 * \brief           Read `data_len` byte(s) from the I2C slave
 * \param[in]       p_data: Readed bytes(s)
 * \param[in]       data_len: Number of bytes
 * \param[out]      p_result: Result of the operation
 * \hideinitializer
 */
#define I2C_READ_BYTES(p_data, data_len, p_result) do { \
    if (p_data == NULL || data_len < 1) {               \
        *p_result = 0;                                  \
    } else {                                            \
        for (size_t i = 0; i < data_len - 1; ++i) {     \
            p_data[i] = i2c_master_readByte();          \
            i2c_master_send_ack();                      \
        }                                               \
        p_data[data_len-1] = i2c_master_readByte();     \
        i2c_master_send_nack();                         \
        *p_result = 1;                                  \
   }                                                    \
} while(0)


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SIMPLE_I2C_H */
