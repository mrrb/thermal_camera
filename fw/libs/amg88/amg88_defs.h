/**
 * \file            amg88_defs.h
 * \author          Mario Rubio (mario@mrrb.eu)
 * \brief           AMG88xx 8x8 IR sensor lib (defs)
 * \version         0.1
 * \date            2021-08-22
 */

#ifndef AMG88_DEFS_H
#define AMG88_DEFS_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define AMG88_ARRAY_SIZE 64

#define AMG88_I2C_ADDR_LOW  0x68
#define AMG88_I2C_ADDR_HIGH 0x69

#define AMG88_THERMISTOR_RESOLUTION 0.0625
#define AMG88_TEMP_RESOLUTION       0.25

#define AMG88_THERMISTOR_MAX -20
#define AMG88_THERMISTOR_MIN  80

/**
 * \brief           Register Map
 */
typedef enum {
    AMG88_REG_PCTL  = 0x00,                     /*!< Set operating mode（Normal, Sleep etc.） [R/W] */
    AMG88_REG_RST   = 0x01,                     /*!< Software Reset [W] */
    AMG88_REG_FPSC  = 0x02,                     /*!< Frame rate [R/W] */
    AMG88_REG_INTC  = 0x03,                     /*!< Interrupt Function [R/W] */
    AMG88_REG_STAT  = 0x04,                     /*!< Interrupt Flag, low voltage Flag [R] */
    AMG88_REG_SCLR  = 0x05,                     /*!< Interrupt Flag Clear [W] */

    AMG88_REG_AVE   = 0x07,                     /*!< Moving Average Output Mode [R] */
    AMG88_REG_INTHL = 0x08,                     /*!< Interrupt upper value（Upper level） [R/W] */
    AMG88_REG_INTHH = 0x09,                     /*!< Interrupt upper value（Upper level） [R/W] */
    AMG88_REG_INTLL = 0x0A,                     /*!< Interrupt lower value（Lower level） [R/W] */
    AMG88_REG_INTLH = 0x0B,                     /*!< Interrupt lower value（upper level） [R/W] */
    AMG88_REG_IHYSL = 0x0C,                     /*!< Interrupt hysteresis value（Lower level） [R/W]*/
    AMG88_REG_IHYSH = 0x0D,                     /*!< Interrupt hysteresis value（Upper level） [R/W]*/
    AMG88_REG_TTHL  = 0x0E,                     /*!< Thermistor Output Value（Lower level) [R] */
    AMG88_REG_TTHH  = 0x0F,                     /*!< Thermistor Output Value（Upper level) [R] */
    AMG88_REG_INT0  = 0x10,                     /*!< Pixel 1～8   Interrupt Result [R] */
    AMG88_REG_INT1  = 0x11,                     /*!< Pixel 9～16  Interrupt Result [R] */
    AMG88_REG_INT2  = 0x12,                     /*!< Pixel 17～24 Interrupt Result [R] */
    AMG88_REG_INT3  = 0x13,                     /*!< Pixel 25～32 Interrupt Result [R] */
    AMG88_REG_INT4  = 0x14,                     /*!< Pixel 33～40 Interrupt Result [R] */
    AMG88_REG_INT5  = 0x15,                     /*!< Pixel 41～48 Interrupt Result [R] */
    AMG88_REG_INT6  = 0x16,                     /*!< Pixel 49～56 Interrupt Result [R] */
    AMG88_REG_INT7  = 0x17,                     /*!< Pixel 57～64 Interrupt Result [R] */

    AMG88_REG_TL    = 0x80,                     /*!< Base addr pixel Output Value (Lower Level) [R] */
    AMG88_REG_TH    = 0x81,                     /*!< Base addr pixel Output Value (Upper Level) [R] */
} amg88_reg_t;

/**
 * \brief           AMG88 lib error codes
 */
typedef enum {
    AMG88_OK,                                   /*!< Everything is Ok */
    AMG88_ERR,                                  /*!< Generic error */
    AMG88_ERR_I2C,                              /*!< I2C error */
    AMG88_ERR_TIMEOUT,                          /*!< Timeout error */
    AMG88_ERR_INVALID_RESET,                    /*!< Reset type not valid */
} amg88_err_t;

/**
 * \brief           AMG88 operation modes
 */
typedef enum {
    AMG88_OP_NORMAL = 0x00,                     /*!< Normal mode */
    AMG88_OP_SLEEP  = 0x10,                     /*!< Sleep mode */
    AMG88_OP_60     = 0x20,                     /*!< Stand-by mode (60sec intermittence) */
    AMG88_OP_10     = 0x21,                     /*!< Stand-by mode (10sec intermittence) */

    AMG88_OP_NOT_VALID = 0xFF,                  /*!< Obtained operation mode not valid */
} amg88_op_mode_t;

/**
 * \brief           AMG88 reset types
 */
typedef enum {
    AMG88_RESET_FLAG    = 0x30,                 /*!< Clear the Status Register, Interrupt Flag, and Interrupt Table */
    AMG88_RESET_INITIAL = 0x3F,                 /*!< Returns to initial setting */
} amg88_reset_t;

/**
 * \brief           AMG88 frame rate
 */
typedef enum {
    AMG88_FPS_10 = 0x00,                        /*!< 10 FPS */
    AMG88_FPS_1  = 0x01,                        /*!< 1 FPS */

    AMG88_FPS_NOT_VALID = 0xFF,                 /*!< Obtained frame rate not valid */
} amg88_fps_t;
 
/**
 * \brief           I2C abstraction function definition
 * \param[in]       addr: I2C address
 * \param[in]       reg_addr: Sensor register address
 * \param[in]       len: Data bytes to read/write
 * \param[inout]    data_buf: Buffer that stores the data
 * \return          Error code
 */
typedef amg88_err_t (*amg88_i2c_fn)(uint8_t addr, uint8_t reg_addr, size_t len, uint8_t* data_buf);

/**
 * \brief           Sensor handler
 */
typedef struct {
    uint8_t addr;                               /*!< I2C sensor address */

    amg88_i2c_fn read;                          /*!< I2C read function */
    amg88_i2c_fn write;                         /*!< I2C write function */
} amg88_dev_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AMG88_DEFS_H */
