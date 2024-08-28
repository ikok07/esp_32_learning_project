//
// Created by kok on 26.08.24.
//

#ifndef RGB_LED_H
#define RGB_LED_H

// RGB LED GPIOs
#define RGB_LED_RED_GPIO    32
#define RGB_LED_GREEN_GPIO  33
#define RGB_LED_BLUE_GPIO   25

// RGB LED color mix channels
#define RGB_LED_CHANNEL_NUM 3

// RGB LED configuration
typedef struct {
    int channel;
    int gpio;
    int mode;
    int timer_index;
} ledc_info_t;

extern ledc_info_t ledc_ch[RGB_LED_CHANNEL_NUM];

/**
 * Color to indicate WIFI application started
 */
void rgb_led_wifi_app_started(void);

/**
 * Color to indicate HTTP server started
 */

void rgb_led_http_server_started(void);

/**
 * Color to indicate that the ESP32 is connected to an active point
 */

void rgb_led_wifi_connected(void);


#endif //RGB_LED_H
