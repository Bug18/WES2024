//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief It's a callback function that is called when an event occurs.
 *
 * @param [in] p_arg This is a pointer to the argument passed to the event handler.
 * @param [in] event_base The event base that the event is associated with.
 * @param [in] event_id The event ID.
 * @param [in] p_event_data This is the data that is passed to the event handler.
 */
void _event_handler(void *p_arg, esp_event_base_t event_base, int32_t event_id, void *p_event_data);

/**
 * @brief It sets up the ESP32 as a station.
 *
 * @return The error code of the last function call.
 */
esp_err_t _wifi_init_sta(void);

/**
 * @brief If the NVS partition is not initialized, initialize it.
 *
 * @return The return value is the bitwise OR of the return values of nvs_flash_erase() and
 * nvs_flash_init().
 */
esp_err_t _nvs_init(void);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static const char *TAG = "WIFI";

