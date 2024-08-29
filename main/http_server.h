//
// Created by kok on 28.08.24.
//

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "portmacro.h"

#define OTA_UPDATE_PENDING 0
#define OTA_UPDATE_SUCCESSFULL 1
#define OTA_UPDATE_FAILED -1

/**
 * Connection statuses for WiFi
 */
typedef enum {
  NONE = 0,
  HTTP_WIFI_STATUS_CONNECTING,
  HTTP_WIFI_STATUS_CONNECT_FAILED,
  HTTP_WIFI_STATUS_CONNECT_SUCCESS
} http_server_wifi_connect_status_e;

/**
 * Messages for the HTTP monitor
 */
typedef enum {
 HTTP_MSG_WIFI_CONNECT_INIT = 0,
 HTTP_MSG_WIFI_CONNECT_SUCCESS,
 HTTP_MSG_WIFI_CONNECT_FAIL,
 HTTP_MSG_OTA_UPDATE_SUCCESSFULL,
 HTTP_MSG_OTA_UPDATE_FAILED,
} http_server_message_e;

/**
 * Structure for the message queue
 */
typedef struct {
 http_server_message_e msgID;
} http_server_queue_msg_t;

/**
 * Sends a message to the queue
 * @param msgID message ID from the http_server_message_e enum
 * @return pdTRUE if an item was successfully sent to the queue, otherwise pdFALSE
 */
BaseType_t http_server_monitor_send_message(http_server_message_e msgID);

/**
 * Starts the HTTP server
 */
void http_server_start(void);

/**
 * Stops the HTTP server
 */
void http_server_stop(void);

/**
 * Timer callback function which calls esp_restart upon successfull firmware update
 */
void http_fw_update_reset_callback(void *arg);

#endif //HTTP_SERVER_H
