//
// Created by kok on 27.08.24.
//

#ifndef PCNT_APP_H
#define PCNT_APP_H

#include "driver/pulse_cnt.h"

#define ENC_A_GPIO 32
#define ENC_B_GPIO 33

#define PULSE_MIN_VAL -1
#define PULSE_MAX_VAL 512

extern bool pcnt_ready;
extern pcnt_unit_handle_t pcnt_unit;
extern pcnt_channel_handle_t pcnt_chan;

void pcnt_start();
int pcnt_get_value();

#endif //PCNT_APP_H
