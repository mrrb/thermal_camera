/**
 * \file uc_init.h
 * \author Mario Rubio (mario@mrrb.eu)
 * \brief uC init stuff
 * \version 0.1
 * \date 2021-08-19
 */

#ifndef UC_INIT_H
#define UC_INIT_H

#include "c_types.h"

#include "user_interface.h"
#include "fast_gpio.h"
#include "ets_sys.h"
#include "os_type.h"
#include "espconn.h"
#include "osapi.h"
#include "mem.h"

#include "status.h"
#include "user_config.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct station_config station_config_t;
typedef struct softap_config softap_config_t;

status_t uc_init_uart();
status_t uc_init_wifi();
status_t uc_init_gpio();
status_t uc_init_i2c();
status_t uc_init_sntp();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UC_INIT_H */
