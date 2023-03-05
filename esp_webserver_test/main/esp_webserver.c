#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs.h"
#include "nvs_flash.h"
#include <esp_http_server.h>

#include "lwip/err.h"
#include "lwip/sys.h"
#include <lwip/sockets.h>
#include <lwip/api.h>
#include <lwip/netdb.h>

#include "driver/gpio.h"

#define EXAMPLE_ESP_WIFI_SSID      "Phone_1_8560"
#define EXAMPLE_ESP_WIFI_PASS      "5rj4n97hci4ga2"
#define EXAMPLE_ESP_MAXIMUM_RETRY  CONFIG_ESP_MAXIMUM_RETRY

#define GPIO_OUTPUT_IO_0    2
#define GPIO_OUTPUT_PIN_SEL     (1ULL << GPIO_OUTPUT_IO_0)

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static const char *TAG = "wifi station";

static int s_retry_num = 0;

void gpio_init(){
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    
    gpio_set_level(GPIO_OUTPUT_IO_0, 1);
}

void blink_led(){
    while(1){
        gpio_set_level(GPIO_OUTPUT_IO_0, 1);
        printf("led high \n");
        vTaskDelay(1000/portTICK_RATE_MS);
        gpio_set_level(GPIO_OUTPUT_IO_0, 0);
        printf("led low \n");
        vTaskDelay(1000/portTICK_RATE_MS);

    }
}

static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void wifi_init_sta(void)
{
    s_wifi_event_group = xEventGroupCreate();

    tcpip_adapter_init();

    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .password = EXAMPLE_ESP_WIFI_PASS
        },
    };

    /* Setting a password implies station will connect to all security modes including WEP/WPA.
        * However these modes are deprecated and not advisable to be used. Incase your Access point
        * doesn't support WPA2, these mode can be enabled by commenting below line */

    if (strlen((char *)wifi_config.sta.password)) {
        wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
     * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
     * happened. */
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }

    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler));
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler));
    vEventGroupDelete(s_wifi_event_group);
}

esp_err_t get_webpage_handler(httpd_req_t *req){
    /* Send http response */
    const char resp[] = "URI GET Response";
    httpd_resp_send(req, resp, strlen(resp));
    return ESP_OK;
}

esp_err_t led_on_handler(httpd_req_t *req){
    /* Send http response */
    const char resp[] = "LED on";
    httpd_resp_send(req, resp, strlen(resp));
    gpio_set_level(GPIO_OUTPUT_IO_0, 0);
    printf("led high \n");
    return ESP_OK;
}

esp_err_t led_off_handler(httpd_req_t *req){
    /* Send http response */
    const char resp[] = "led of";
    httpd_resp_send(req, resp, strlen(resp));
    gpio_set_level(GPIO_OUTPUT_IO_0, 1);
    printf("led low \n");
    return ESP_OK;
}



httpd_uri_t uri_get = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = get_webpage_handler,
    .user_ctx = NULL
};

httpd_uri_t uri_led_on = {
    .uri = "/on",
    .method = HTTP_GET,
    .handler = led_on_handler,
    .user_ctx = NULL
};

httpd_uri_t uri_led_off = {
    .uri = "/off",
    .method = HTTP_GET,
    .handler = led_off_handler,
    .user_ctx = NULL
};

httpd_handle_t setup_server(){
    /* Generate default configuration */
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    /* Start the httpd server */
    if (httpd_start(&server, &config) == ESP_OK) {
        /* Register URI handlers */
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &uri_led_on);
        httpd_register_uri_handler(server, &uri_led_off);

    }
    /* If server failed to start, handle will be NULL */
    return server;   
}

void app_main()
{
    gpio_init();
    ESP_ERROR_CHECK(nvs_flash_init());

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();

    ESP_LOGI(TAG, "Web Server is running ... ...\n");
    setup_server();
}
