//
// Created by kok on 30.08.24.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "app_nvs.h"
#include "wifi_app.h"

// Tag for logging to the monitor
const char TAG[] = "nvs";

// NVS namespace used for station mode credentials
const char app_nvs_sta_creds_namespace[] = "stacreds";

esp_err_t app_nvs_save_sta_creds(void) {
    nvs_handle handle;
    esp_err_t esp_err;
    ESP_LOGI(TAG, "app_nvs_save_sta_creds: Saving station mode credentials to flash");
    wifi_config_t *wifi_sta_config = wifi_app_get_wifi_config();
    if (wifi_sta_config) {
        esp_err = nvs_open(app_nvs_sta_creds_namespace, NVS_READWRITE, &handle);
        if (esp_err != ESP_OK) {
            printf("app_nvs_save_sta_creds: Error (%s) opening NVS handle!\n", esp_err_to_name(esp_err));
            return esp_err;
        }

        // Set SSID
        esp_err = nvs_set_blob(handle, "ssid", wifi_sta_config->sta.ssid, MAX_SSID_LEN);
        if (esp_err != ESP_OK) {
            printf("app_nvs_save_sta_creds: Error (%s) setting SSID to NVS!\n", esp_err_to_name(esp_err));
            return esp_err;
        }

        // Set password
        esp_err = nvs_set_blob(handle, "password", wifi_sta_config->sta.password, MAX_PASSWORD_LENGTH);
        if (esp_err != ESP_OK) {
            printf("app_nvs_save_sta_creds: Error (%s) setting password to NVS!\n", esp_err_to_name(esp_err));
            return esp_err;
        }

        // Commit credentials to NVS
        esp_err = nvs_commit(handle);
        if (esp_err != ESP_OK) {
            printf("app_nvs_save_sta_creds: Error (%s) commiting to NVS!\n", esp_err_to_name(esp_err));
            return esp_err;
        }

        nvs_close(handle);
        ESP_LOGI(TAG, "app_nvs_save_sta_creds: wrote wifi_sta_config: Station SSID: %s Password: %s", wifi_sta_config->sta.ssid, wifi_sta_config->sta.password);
    }
    return ESP_OK;
}

bool app_nvs_load_sta_creds(void) {
    nvs_handle handle;
    esp_err_t esp_err;

    ESP_LOGI(TAG, "app_nvs_load_sta_creds: Loading WiFi credentials from flash");
    if (nvs_open(app_nvs_sta_creds_namespace, NVS_READONLY, &handle) == ESP_OK) {
        wifi_config_t *wifi_config = wifi_app_get_wifi_config();
        if (wifi_config == NULL) wifi_config = malloc(sizeof(wifi_config_t));

        // Allocate a buffer
        size_t wifi_config_size = sizeof(wifi_config_t);
        uint8_t *wifi_config_buffer = malloc(sizeof(uint8_t) * wifi_config_size);

        // Load SSID
        wifi_config_size = sizeof(wifi_config->sta.ssid);
        esp_err = nvs_get_blob(handle, "ssid", wifi_config_buffer, &wifi_config_size);
        if (esp_err != ESP_OK) {
            free(wifi_config_buffer);
            printf("app_nvs_load_sta_creds: Error (%s) no station SSID found in NVS\n", esp_err_to_name(esp_err));
            return false;
        }
        memcpy(wifi_config->sta.ssid, wifi_config_buffer, wifi_config_size);

        printf("app_nvs_load_sta_creds: SSID successffuly set\n");

        // Load password
        wifi_config_size = sizeof(wifi_config->sta.password);
        esp_err = nvs_get_blob(handle, "password", wifi_config_buffer, &wifi_config_size);
        if (esp_err != ESP_OK) {
            free(wifi_config_buffer);
            printf("app_nvs_load_sta_creds: Error (%s) no station password found in NVS\n", esp_err_to_name(esp_err));
            return false;
        }
        memcpy(wifi_config->sta.password, wifi_config_buffer, wifi_config_size);

        free(wifi_config_buffer);
        nvs_close(handle);

        printf("app_nvs_load_sta_creds: SSID: %s Password: %s", wifi_config->sta.ssid, wifi_config->sta.password);
        return wifi_config->sta.ssid[0] != '\0';
    }
    return false;
}

esp_err_t app_nvs_clear_sta_creds(void) {
    nvs_handle_t handle;
    esp_err_t esp_err;
    ESP_LOGI(TAG, "app_nvs_clear_sta_creds: Clearing WiFi station mode credentials from flash");

    esp_err = nvs_open(app_nvs_sta_creds_namespace, NVS_READWRITE, &handle);
    if (esp_err != ESP_OK) {
        printf("app_nvs_clear_sta_creds: Error (%s) opening NVS handle!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    esp_err = nvs_erase_all(handle);
    if (esp_err != ESP_OK) {
        printf("app_nvs_clear_sta_creds: Error (%s) erasing station mode credentials!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    esp_err = nvs_commit(handle);
    if (esp_err != ESP_OK) {
        printf("app_nvs_clear_sta_creds: Error (%s) commiting to NVS!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    nvs_close(handle);
    return ESP_OK;
}
