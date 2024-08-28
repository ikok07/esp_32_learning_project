//
// Created by kok on 27.08.24.
//

#include "pcnt_app.h"
#include "esp_task.h"

#include "esp_log.h"

const char TAG[] = "pcnt";
pcnt_unit_handle_t pcnt_unit = NULL;
pcnt_channel_handle_t pcnt_chan = NULL;
bool pcnt_ready = false;
int pcnt_val = 0;

/**
 * Initialize PCNT unit
 */
static void pcnt_unit_init() {
      pcnt_unit_config_t pulse_config = {
       .low_limit = PULSE_MIN_VAL,
       .high_limit = PULSE_MAX_VAL,
       .intr_priority = 0,
      };
      ESP_ERROR_CHECK(pcnt_new_unit(&pulse_config, &pcnt_unit));
}


/**
 * Initialize the psnt channel
 */
static void pcnt_channel_init() {
    pcnt_chan_config_t config = {
        .edge_gpio_num = ENC_A_GPIO,
        .level_gpio_num = ENC_B_GPIO
    };
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &config, &pcnt_chan));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
}

/**
 * Start the pcnt application
 */
void pcnt_start() {

    // Configure the PCNT unit
    pcnt_unit_init();
    ESP_LOGI(TAG, "PCNT Unit initialized successfully!");

    // Configure the PCNT channel
    pcnt_channel_init();
    ESP_LOGI(TAG, "PCNT Channel initialized successfully!");

    // Enable PCNT unit
    ESP_ERROR_CHECK(pcnt_unit_enable(pcnt_unit));
    ESP_ERROR_CHECK(pcnt_unit_start(pcnt_unit));
    ESP_LOGI(TAG, "PCNT enabled successfully!");
    pcnt_ready = true;
}

int pcnt_get_value() {
    pcnt_unit_get_count(pcnt_unit, &pcnt_val);
    return pcnt_val;
}
