#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

#include "cJSON.h"

static const char *CONFIG_BROKER_URL = "mqtt://192.168.254.6";

void log_error_if_nonzero(const char *message, int error_code);
void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
esp_mqtt_client_handle_t *mqtt_app_start(void);
esp_err_t example_connect(void);
int send_sensor_message(esp_mqtt_client_handle_t *client, float temp, float hum, float *acc);
send_game_message(esp_mqtt_client_handle_t *client, char *turn, int *indexX, int oLen, int *indexO, int xLen);
