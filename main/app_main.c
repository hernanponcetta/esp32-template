#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "app_main";

void app_main(void)
{
    ESP_LOGI(TAG, "Hello from ESP32-C6 (esp32-template)");

    uint32_t uptime_sec = 0;
    while (1) {
        ESP_LOGI(TAG, "Uptime: %lu s", (unsigned long)uptime_sec);
        vTaskDelay(pdMS_TO_TICKS(1000));
        uptime_sec++;
    }
}
