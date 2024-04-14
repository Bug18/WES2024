#include "mqtt_driver.h"


esp_mqtt_client_handle_t client;


void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE("MQTT", "Last error %s: 0x%x", message, error_code);
    }
}


void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD("MQTT", "Event dispatched from event loop base=%s, event_id=%" PRIi32 "", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI("MQTT", "MQTT_EVENT_CONNECTED");
            // msg_id = send_sensor_message(0.f, 0.f, {0.f, 0.f, 0.f});
            // ESP_LOGI("MQTT", "sent publish successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, "WES/Venus/game", 0);
            ESP_LOGI("MQTT", "sent subscribe successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI("MQTT", "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI("MQTT", "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            // msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
            // ESP_LOGI("MQTT", "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI("MQTT", "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI("MQTT", "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI("MQTT", "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            parse_subscriber_message(event);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI("MQTT", "MQTT_EVENT_ERROR");
            if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
                log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
                log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
                log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
                ESP_LOGI("MQTT", "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));

            }
            break;
        default:
            ESP_LOGI("MQTT", "Other event id:%d", event->event_id);
            break;
    }
}


void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://4gpc.l.time4vps.cloud",
    };
#if CONFIG_BROKER_URL_FROM_STDIN
    char line[128];

    if (strcmp(mqtt_cfg.broker.address.uri, "FROM_STDIN") == 0) {
        int count = 0;
        printf("Please enter url of mqtt broker\n");
        while (count < 128) {
            int c = fgetc(stdin);
            if (c == '\n') {
                line[count] = '\0';
                break;
            } else if (c > 0 && c < 127) {
                line[count] = c;
                ++count;
            }
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        mqtt_cfg.broker.address.uri = line;
        printf("Broker url: %s\n", line);
    } else {
        ESP_LOGE("MQTT", "Configuration mismatch: wrong broker url");
        abort();
    }
#endif /* CONFIG_BROKER_URL_FROM_STDIN */

    client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}


int send_sensor_message(float temp, float hum, float *acc){
    int message_id;

	cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "temp", temp);
    cJSON_AddNumberToObject(root, "hum", hum);
    cJSON *accArray = cJSON_CreateObject();
    cJSON_AddNumberToObject(accArray, "x", acc[0]);
    cJSON_AddNumberToObject(accArray, "y", acc[1]);
    cJSON_AddNumberToObject(accArray, "z", acc[2]);
    cJSON_AddItemToObject(root, "acc", accArray);
    char *jsonMessage = cJSON_PrintUnformatted(root);

    // Publish JSON message on MQTT
    message_id = esp_mqtt_client_publish(client, "WES/Venus/sensors", jsonMessage, 0, 1, 0);

    // Free memory
    free(jsonMessage);
    cJSON_Delete(root);

    return message_id;
}


int send_game_message(char *turn, char *game_array){
    int message_id;

    cJSON *root = cJSON_CreateObject();
    cJSON *xArray = cJSON_CreateArray();
    cJSON *oArray = cJSON_CreateArray();
    
    for (int i = 0; i < 9; i++){
        if (game_array[i] == 'x')
            cJSON_AddItemToArray(xArray, cJSON_CreateNumber(i));
        else if (game_array[i] == 'o')
            cJSON_AddItemToArray(oArray, cJSON_CreateNumber(i));
    }
    
    cJSON_AddItemToObject(root, "indexX", xArray);
    cJSON_AddItemToObject(root, "indexY", oArray);

    char *jsonMessage = cJSON_PrintUnformatted(root);
    
    message_id = esp_mqtt_client_publish(client, "WES/Venus/game", jsonMessage, 0, 1, 0);

    free(jsonMessage);
    cJSON_Delete(root);

    return message_id;
}
 

void parse_subscriber_message(esp_mqtt_event_handle_t event){
    cJSON *raw, *turn, *xArray, *oArray, *item;

    lv_obj_t *xObj[9] = {ui_X0, ui_X1, ui_X2, ui_X3, ui_X4, ui_X5, ui_X6, ui_X7, ui_X8}; 
    lv_obj_t *oObj[9] = {ui_O0, ui_O1, ui_O2, ui_O3, ui_O4, ui_O5, ui_O6, ui_O7, ui_O8};

    if (!strcmp(event->topic, "WES/Venus/game")){
        char *game = get_game_array();
        raw = cJSON_Parse(event->data);
        if (raw != NULL){
            turn = cJSON_GetObjectItemCaseSensitive(raw, "turn");
            if (!strcmp(turn->valuestring, "device")){
                xArray = cJSON_GetObjectItemCaseSensitive(raw, "indexX");
                oArray = cJSON_GetObjectItemCaseSensitive(raw, "indexO");

                cJSON_Delete(raw);

                for (int i = 0; i < cJSON_GetArraySize(xArray); i++){
                    item = cJSON_GetArrayItem(xArray, i);
                    
                    if (game[item->valueint] != 0) {
                        lv_obj_clear_flag(xObj[i], LV_OBJ_FLAG_HIDDEN);

                        game_status m = makeMove('x', i);

                        if (m == GAME_WON) {
                            lv_obj_clear_flag(ui_LoseLabel, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_add_flag(ui_WinLabel, LV_OBJ_FLAG_HIDDEN);
                            _ui_screen_change(&ui_EndGameScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_EndGameScreen_screen_init);
                            clearGui();
                        }else if (m == GAME_ENDED) {
                            lv_label_set_text(ui_LoseLabel, "Game ended in a draw!");
                            lv_obj_clear_flag(ui_LoseLabel, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_add_flag(ui_WinLabel, LV_OBJ_FLAG_HIDDEN);
                            _ui_screen_change(&ui_EndGameScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_EndGameScreen_screen_init);
                            clearGui();
		                }

                        break;
                    }

                    game[item->valueint] = 'x';                
                }

                for (int j = 0; j < cJSON_GetArraySize(oArray); j++){
                    item = cJSON_GetArrayItem(oArray, j);

                    if (game[item->valueint] != 0) {
                        lv_obj_clear_flag(oObj[j], LV_OBJ_FLAG_HIDDEN);

                        if (game[item->valueint] != 0) {
                        lv_obj_clear_flag(oObj[j], LV_OBJ_FLAG_HIDDEN);

                        game_status m = makeMove('o', j);

                        if (m == GAME_WON) {
                            lv_obj_clear_flag(ui_LoseLabel, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_add_flag(ui_WinLabel, LV_OBJ_FLAG_HIDDEN);
                            _ui_screen_change(&ui_EndGameScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_EndGameScreen_screen_init);
                            clearGui();
                        }else if (m == GAME_ENDED) {
                            lv_label_set_text(ui_LoseLabel, "Game ended in a draw!");
                            lv_obj_clear_flag(ui_LoseLabel, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_add_flag(ui_WinLabel, LV_OBJ_FLAG_HIDDEN);
                            _ui_screen_change(&ui_EndGameScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_EndGameScreen_screen_init);
                            clearGui();
		                }
                        
                        break;
                    }
                    }

                    game[item->valueint] = 'o';                
                }
            }
        }
    }
}
