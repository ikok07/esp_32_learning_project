//
// Created by kok on 30.08.24.
//

#ifndef APP_NVS_H
#define APP_NVS_H

#include <stdbool.h>

#include "esp_err.h"

/**
 * Saves station mode WiFi credentials to NVS
 * @return ESP_OK if successful
 */
esp_err_t app_nvs_save_sta_creds(void);

/**
 * Loads the previously saved WiFi credentials from NVS
 * @return true if previosly saved credentials were found
 */
bool app_nvs_load_sta_creds(void);

/*
 * Clears station mode credentials from NVS
 * @return ESP_OK if successful
 */
esp_err_t app_nvs_clear_sta_creds(void);

#endif //APP_NVS_H
