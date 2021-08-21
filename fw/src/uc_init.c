/**
 * \file            uc_init.c
 * \author          Mario Rubio (mario@mrrb.eu)
 * \brief           uC init stuff
 * \version         0.1
 * \date            2021-08-21
 */

#include "uc_init.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_err.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "user_config.h"

/* Vars */
static char* log_src = "uc_init";
static EventGroupHandle_t wifi_event_group;


static void
wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    static int retry_num = 0;

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (retry_num < CFG_WIFI_MAX_RETRY) {
            esp_wifi_connect();
            retry_num++;
            ESP_LOGI(log_src, "Retrying connection to AP");
        } else {
            xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
        }

        ESP_LOGI(log_src,"Connection to the AP failed");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(log_src, "Got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        retry_num = 0;
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

esp_err_t
uc_init_wifi() {
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_event_handler_instance_t instance_any_id, instance_got_ip;

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = CFG_WIFI_SSID,
            .password = CFG_WIFI_PASSWORD,
	        .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {
                .capable = true,
                .required = false
            },
        },
    };

    esp_netif_t* p_netif;

    wifi_event_group = xEventGroupCreate();

    UC_RETURN_FAIL(esp_netif_init());

    UC_RETURN_FAIL(esp_event_loop_create_default());
    p_netif = esp_netif_create_default_wifi_sta();
    UC_RETURN_FAIL(esp_netif_set_hostname(p_netif, CFG_WIFI_HOSTNAME));

    UC_RETURN_FAIL(esp_wifi_init(&cfg));

    UC_RETURN_FAIL(
        esp_event_handler_instance_register(WIFI_EVENT,
                                            ESP_EVENT_ANY_ID,
                                            &wifi_event_handler,
                                            NULL,
                                            &instance_any_id)
    );
    UC_RETURN_FAIL(
        esp_event_handler_instance_register(IP_EVENT,
                                            IP_EVENT_STA_GOT_IP,
                                            &wifi_event_handler,
                                            NULL,
                                            &instance_got_ip)
    );

    UC_RETURN_FAIL(esp_wifi_set_mode(WIFI_MODE_STA));
    UC_RETURN_FAIL(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    UC_RETURN_FAIL(esp_wifi_start());

    EventBits_t bits = xEventGroupWaitBits(
        wifi_event_group,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY
    );

    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(log_src, "Connected to %s", CFG_WIFI_SSID);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(log_src, "Failed to connect to %s", CFG_WIFI_SSID);
    } else {
        ESP_LOGE(log_src, "UNEXPECTED EVENT");
    }

    /* The event will not be processed after unregister */
    UC_RETURN_FAIL(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
    UC_RETURN_FAIL(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
    vEventGroupDelete(wifi_event_group);

    return ESP_OK;
}

esp_err_t
uc_init_sys() {
    /* NVS */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      UC_RETURN_FAIL(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    UC_RETURN_FAIL(ret);

    return ESP_OK;
}
