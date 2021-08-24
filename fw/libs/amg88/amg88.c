/**
 * \file            amg88.c
 * \author          Mario Rubio (mario@mrrb.eu)
 * \brief           AMG88xx 8x8 IR sensor lib
 * \version         0.1
 * \date            2021-08-22
 */

#include "amg88.h"

#include <stdint.h>

#include "amg88_defs.h"

amg88_op_mode_t
amg88_get_op_mode(amg88_dev_t* p_dev) {
    uint8_t read_buff;

    if (p_dev->read(p_dev->addr, AMG88_REG_PCTL, 1, &read_buff) != AMG88_OK) {
        return AMG88_OP_NOT_VALID;
    } else {
        return (amg88_op_mode_t) read_buff;
    }
}

amg88_err_t
amg88_set_op_mode(amg88_dev_t* p_dev, amg88_op_mode_t mode) {
    return p_dev->write(p_dev->addr, AMG88_REG_PCTL, 1, (uint8_t*) (&mode));
}

amg88_err_t
amg88_reset(amg88_dev_t* p_dev, amg88_reset_t type) {
    if (type != AMG88_RESET_FLAG && type != AMG88_RESET_INITIAL) {
        return AMG88_ERR_INVALID_RESET;
    }

    return p_dev->write(p_dev->addr, AMG88_REG_RST, 1, (uint8_t*) (&type));
}

amg88_fps_t
amg88_get_frame_rate(amg88_dev_t* p_dev) {
    uint8_t read_buff = 0;

    if (p_dev->read(p_dev->addr, AMG88_REG_FPSC, 1, &read_buff) != AMG88_OK) {
        return AMG88_FPS_NOT_VALID;
    } else {
        return (amg88_op_mode_t) read_buff;
    }
}

amg88_err_t
amg88_set_frame_rate(amg88_dev_t* p_dev, amg88_fps_t mode) {
    return p_dev->write(p_dev->addr, AMG88_REG_FPSC, 1, (uint8_t*) (&mode));
}

float
amg88_get_thermistor(amg88_dev_t* p_dev) {
    uint8_t buff[2] = { 0 };

    if (p_dev->read(p_dev->addr, AMG88_REG_TTHL, 1, buff) != AMG88_OK) {
        return -99.99;
    }
    if (p_dev->read(p_dev->addr, AMG88_REG_TTHH, 1, buff + 1) != AMG88_OK) {
        return -99.99;
    }

    return AMG88_THERMISTOR_2_TEMP(buff);
}

float
amg88_get_pixel(amg88_dev_t* p_dev, uint8_t row, uint8_t col) {
    uint8_t buff[2] = { 0 };

    if (row >= 8 || col >= 8) {
        return -99.99;
    }

    if (p_dev->read(p_dev->addr, AMG88_REG_TL + 2 * (row * 8 + col), 1, buff) != AMG88_OK) {
        return -99.99;
    }
    if (p_dev->read(p_dev->addr, AMG88_REG_TH + 2 * (row * 8 + col), 1, buff + 1) != AMG88_OK) {
        return -99.99;
    }

    return AMG88_PIXEL_2_TEMP(buff);
}

amg88_err_t
amg88_get_array(amg88_dev_t* p_dev, float* array) {
    for (size_t r = 0; r < 8; ++r) {
        for (size_t c = 0; c < 8; ++c) {
            array[r * 8 + c] = amg88_get_pixel(p_dev, r, c);
        }
    }

    return AMG88_OK;
}


