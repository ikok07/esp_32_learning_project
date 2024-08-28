//
// Created by kok on 27.08.24.
//

#ifndef DAC_APP_H
#define DAC_APP_H

#include "driver/dac_continuous.h"

#define DAC_CHAN_MASK           DAC_CHANNEL_MASK_CH0
#define DAC_DESC_NUM            8
#define DAC_BUFF_SIZE           2048
#define DAC_FREQ                20000
#define DAC_OFFSET              0
#define DAC_CLK_SRC             DAC_DIGI_CLK_SRC_DEFAULT

#define DAC_TASK_STACK_SIZE     4096
#define DAC_TASK_PRIORITY       5

extern dac_continuous_handle_t dac_handle;

/**
 * Initialize the DAC appliation and start background task
 */
void dac_start();

#endif //DAC_APP_H
