/**
 * \file            uc_init.h
 * \author          Mario Rubio (mario@mrrb.eu)
 * \brief           uC init stuff
 * \version         0.1
 * \date            2021-08-21
 */

#ifndef UC_INIT_H
#define UC_INIT_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

/**
 * \brief           Return on failure
 * \param[in]       err: Error code
 * \hideinitializer
 */
/*
#define UC_RETURN_FAIL(err) do {    \
    esp_err_t _err_tmp = err;       \
    if (_err_tmp != ESP_OK) {       \
        return _err_tmp;            \
    }                               \
} while (0)
*/
#define UC_RETURN_FAIL ESP_ERROR_CHECK

/**
 * \brief           Init uC wifi comms
 * \return          Result 
 */
esp_err_t uc_init_wifi();

/**
 * \brief           Init uC system
 * \return          Result 
 */
esp_err_t uc_init_sys();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UC_INIT_H */