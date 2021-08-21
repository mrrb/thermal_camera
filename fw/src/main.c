/**
 * \file            main.c
 * \author          Mario Rubio (mario@mrrb.eu)
 * \brief           Main
 * \version         0.1
 * \date            2021-08-21
 */

#include <stdio.h>

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "user_config.h"
#include "uc_init.h"

static char* log_src = "main";

void
app_main(void) {
    /* Set logs verbosity level */
#ifdef DEBUG_PRINT_ENABLE
    esp_log_level_set("*", ESP_LOG_VERBOSE);
#else
    esp_log_level_set("*", ESP_LOG_INFO);
#endif /* DEBUG_PRINT_ENABLE */

    ESP_LOGI(log_src, "uC start");

    ESP_ERROR_CHECK(uc_init_sys());
    ESP_ERROR_CHECK(uc_init_wifi());
}
