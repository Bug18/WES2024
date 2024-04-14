#include "sntp_rtc_driver.h"

static void sntp_obtain_time(void)
{
    ESP_LOGI(TAG, "Initializing and starting SNTP");

    /*
     * This is the basic default config with one server and starting the service
     */
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG(CONFIG_SNTP_TIME_SERVER);
    esp_netif_sntp_init(&config);

    // wait for time to be set
    time_t now = 0;
    struct tm timeinfo = { 0 };
    int retry = 0;
    const int retry_count = 15;
    while (esp_netif_sntp_sync_wait(2000 / portTICK_PERIOD_MS) == ESP_ERR_TIMEOUT && ++retry < retry_count) {
        ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
    }
    time(&now);
    localtime_r(&now, &timeinfo);

    esp_netif_sntp_deinit();
}

void sntp_rtc_task(void* parameter)
{
    while(1) {

        time_t now;
        struct tm timeinfo;
        time(&now);
        localtime_r(&now, &timeinfo);

        // Is time set? If not, tm_year will be (1970 - 1900).
        if (timeinfo.tm_year < (2016 - 1900)) {
            ESP_LOGI(TAG, "Time is not set yet. Getting time over NTP.");
            sntp_obtain_time();
            // update 'now' variable with current time
            time(&now);
        }

        // Set timezone to Eastern Standard Time and print local time
        setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1);
        tzset();
        
        localtime_r(&now, &timeinfo);

        // Format the date string (DD:MM:YYYY)
        char dateString[12];
        strftime(dateString, 11, "%d:%m:%Y", &timeinfo);
        
        // Format the time string (HH:MM:SS)
        char timeString[10];
        strftime(timeString, 9, "%H:%M:%S", &timeinfo);
        
        ESP_LOGI(TAG, "The current date/time in Zagreb is: %s %s", dateString, timeString);

        // CHANGE UI
        lv_label_set_text(ui_Date, dateString);
        lv_label_set_text(ui_Hour, timeString);

        lv_label_set_text(ui_Date1, dateString);
        lv_label_set_text(ui_Hour1, timeString);

        lv_label_set_text(ui_Date2, dateString);
        lv_label_set_text(ui_Hour2, timeString);

        lv_label_set_text(ui_Date3, dateString);
        lv_label_set_text(ui_Hour3, timeString);


        if (sntp_get_sync_mode() == SNTP_SYNC_MODE_SMOOTH) {
            struct timeval outdelta;
            while (sntp_get_sync_status() == SNTP_SYNC_STATUS_IN_PROGRESS) {
                adjtime(NULL, &outdelta);
                ESP_LOGI(TAG, "Waiting for adjusting time ... outdelta = %jd sec: %li ms: %li us",
                            (intmax_t)outdelta.tv_sec,
                            outdelta.tv_usec/1000,
                            outdelta.tv_usec%1000);
                vTaskDelay(2000 / portTICK_PERIOD_MS);
            }
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void sntp_rtc_init(void) {
    xTaskCreate(&sntp_rtc_task, "sntp_rtc", 1024*2, NULL, 2, NULL);
}
