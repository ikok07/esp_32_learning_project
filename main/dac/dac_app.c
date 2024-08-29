//
// Created by kok on 27.08.24.
//
#include "esp_log.h"
#include "esp_task.h"
#include "FreeRTOSConfig.h"
#include "esp_adc/adc_oneshot.h"

#include "dac_app.h"
#include "./pcnt/pcnt_app.h"

dac_continuous_handle_t dac_handle = NULL;

/**
 * Create DAC background task
 * @param arg optional task arguments
 */
static void dac_task(void *arg) {
    while (true) {
        uint8_t data = pcnt_get_value() / 2;
        ESP_ERROR_CHECK(dac_continuous_write_cyclically(dac_handle, &data, sizeof(data), NULL));
        ESP_LOGI("dac", "%d", data);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void dac_start() {
    // Start PCNT application if not already active
    if (!pcnt_ready) pcnt_start();

    const dac_continuous_config_t config = {
        .chan_mask = DAC_CHAN_MASK,
        .desc_num = DAC_DESC_NUM,
        .buf_size = DAC_BUFF_SIZE,
        .freq_hz = DAC_FREQ,
        .offset = DAC_OFFSET,
        .clk_src = DAC_CLK_SRC,
    };
    ESP_ERROR_CHECK(dac_continuous_new_channels(&config, &dac_handle));
    ESP_ERROR_CHECK(dac_continuous_enable(dac_handle));
    xTaskCreate(&dac_task, "dac_task", DAC_TASK_STACK_SIZE, NULL, DAC_TASK_PRIORITY, NULL);
}
