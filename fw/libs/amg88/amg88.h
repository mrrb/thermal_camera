/**
 * \file            amg88.h
 * \author          Mario Rubio (mario@mrrb.eu)
 * \brief           AMG88xx 8x8 IR sensor lib
 * \version         0.1
 * \date            2021-08-22
 */

#ifndef AMG88_H
#define AMG88_H

#include "amg88_defs.h"

#include <stdio.h> // ! Remove

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// TODO Add interrupts

/**
 * \brief           Calculate the thermistor temperature from the sensor raw data
 * \param[in]       data: Raw thermistor array
 * \param[in]       res: Thermistor resolution
 * \return          Thermistor temperature
 * \hideinitializer
 */
#define AMG88_THERMISTOR_2_TEMP_RES(data, res) ({  \
    float _temp;                                   \
    uint8_t _neg;                                  \
    uint16_t _raw_temp;                            \
    _neg = (data[1] & 0x08) > 1;                   \
    _raw_temp = data[0] | ((data[1] & 0x07) << 8); \
    _temp = _raw_temp * res * (_neg ? -1 : 1);     \
    _temp;                                         \
})

/**
 * \brief           Calculate the thermistor temperature from the sensor raw data using default resolution
 * \param[in]       data: Raw thermistor array
 * \return          Thermistor temperature
 * \hideinitializer
 */
#define AMG88_THERMISTOR_2_TEMP(data) (AMG88_THERMISTOR_2_TEMP_RES(data, AMG88_THERMISTOR_RESOLUTION))

/**
 * \brief           Calculate the IR pixel temperature from the sensor raw data
 * \param[in]       data: Raw pixel array
 * \param[in]       res: IR sensor resolution
 * \return          IR pixel temperature
 * \hideinitializer
 */
#define AMG88_PIXEL_2_TEMP_RES(data, res) ({        \
    float _temp;                                    \
    uint16_t _raw_temp;                             \
    _raw_temp = data[0] | ((data[1] & 0x07) << 8);  \
    if ((data[1] & 0x08) > 1) {                     \
        _temp = ~(_raw_temp - 1) & 0x7FF;           \
    } else {                                        \
        _temp = _raw_temp;                          \
    }                                               \
    _temp = _temp * res;                            \
    _temp;                                          \
})

/**
 * \brief           Calculate the IR pixel temperature from the sensor raw data using default resolution
 * \param[in]       data: Raw pixel array
 * \return          IR pixel temperature
 * \hideinitializer
 */
#define AMG88_PIXEL_2_TEMP(data) (AMG88_PIXEL_2_TEMP_RES(data, AMG88_TEMP_RESOLUTION))

/**
 * \brief           Find maximum value in the array
 * \param[in]       array: Input array
 * \param[in]       len: Length of the array
 * \return          Maximum value
 * \hideinitializer
 */
#define AMG88_ARRAY_MAX_LEN(array, len) ({  \
    float _max = -99.99;                    \
    for (size_t i = 0; i < len; i++) {      \
        if (array[i] > _max) {              \
            _max = array[i];                \
        }                                   \
    }                                       \
    _max;                                   \
})

/**
 * \brief           Find maximum value in the array using default size
 * \param[in]       array: Input array
 * \return          Maximum value
 * \hideinitializer
 */
#define AMG88_ARRAY_MAX(array) AMG88_ARRAY_MAX_LEN(array, AMG88_ARRAY_SIZE)

/**
 * \brief           Find minimum value in the array
 * \param[in]       array: Input array
 * \param[in]       len: Length of the array
 * \return          Minimum value
 * \hideinitializer
 */
#define AMG88_ARRAY_MIN_LEN(array, len) ({  \
    float _min = -99.99;                    \
    for (size_t i = 0; i < len; i++) {      \
        if (array[i] < _min) {              \
            _min = array[i];                \
        }                                   \
    }                                       \
    _min;                                   \
})

/**
 * \brief           Find minimum value in the array using default size
 * \param[in]       array: Input array
 * \return          Minimum value
 * \hideinitializer
 */
#define AMG88_ARRAY_MIN(array) AMG88_ARRAY_MIN_LEN(array, AMG88_ARRAY_SIZE)

/**
 * \brief           Compute the mean of the array
 * \param[in]       array: Input array
 * \param[in]       len: Length of the array
 * \return          Array mean value
 * \hideinitializer
 */
#define AMG88_ARRAY_MEAN_LEN(array, len) ({         \
    float _mean, _index;                            \
    _mean = (float) array[0];                       \
    for (size_t i = 1; i < len; i++) {              \
        _index = (float) i;                         \
        _mean *= (_index / (_index + 1));           \
        _mean += (float) array[i] / (_index + 1);   \
    }                                               \
    _mean;                                          \
})

/**
 * \brief           Compute the mean of the array using default size
 * \param[in]       array: Input array
 * \return          Array mean value
 * \hideinitializer
 */
#define AMG88_ARRAY_MEAN(array) AMG88_ARRAY_MEAN_LEN(array, AMG88_ARRAY_SIZE)

/**
 * \brief           Get sensor operation mode
 * \param[in]       p_dev: Pointer to sensor handler
 * \return          Operation mode, \ref AMG88_OP_NOT_VALID on error
 */
amg88_op_mode_t amg88_get_op_mode(amg88_dev_t* p_dev);

/**
 * \brief           Set sensor operation mode
 * \param[in]       p_dev: Pointer to sensor handler
 * \param[in]       mode: New operation mode
 * \return          \ref AMG88_OK on success, a member of \ref amg88_err_t otherwise
 */
amg88_err_t amg88_set_op_mode(amg88_dev_t* p_dev, amg88_op_mode_t mode);

/**
 * \brief           Reset the sensor
 * \param[in]       p_dev: Pointer to sensor handler
 * \param[in]       type: Reset type
 * \return          \ref AMG88_OK on success, a member of \ref amg88_err_t otherwise
 */
amg88_err_t amg88_reset(amg88_dev_t* p_dev, amg88_reset_t type);

/**
 * \brief           Get sensor frame rate
 * \param[in]       p_dev: Pointer to sensor handler
 * \return          Frame rate, \ref AMG88_FPS_NOT_VALID on error
 */
amg88_fps_t amg88_get_frame_rate(amg88_dev_t* p_dev);

/**
 * \brief           Set sensor frame rate
 * \param[in]       p_dev: Pointer to sensor handler
 * \param[in]       mode: New frame rate
 * \return          \ref AMG88_OK on success, a member of \ref amg88_err_t otherwise
 */
amg88_err_t amg88_set_frame_rate(amg88_dev_t* p_dev, amg88_fps_t mode);

/**
 * \brief           Get internal thermistor value
 * \param[in]       p_dev: Pointer to sensor handler
 * \return          Thermistor temperature
 */
float amg88_get_thermistor(amg88_dev_t* p_dev);

/**
 * \brief           Get pixel temperature
 * \param[in]       p_dev: Pointer to sensor handler
 * \param[in]       row: Pixel row
 * \param[in]       col: Pixel column
 * \return          Pixel temperature
 */
float amg88_get_pixel(amg88_dev_t* p_dev, uint8_t row, uint8_t col);

/**
 * \brief           Get IR temperature array
 * \param[in]       p_dev: Pointer to sensor handler
 * \param[out]      array: IR points temperature
 * \return          \ref AMG88_OK on success, a member of \ref amg88_err_t otherwise
 */
amg88_err_t amg88_get_array(amg88_dev_t* p_dev, float* array);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AMG88_H */
