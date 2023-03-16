#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <esp_log.h>

#include "driver/gpio.h"
#include "dispaly_driver.h"

#define GPIO_OUTPUT_IO_4    2
#define GPIO_OUTPUT_PIN_SEL     (1ULL << GPIO_OUTPUT_IO_0)

#define GPIO_OUTPUT_IO_0 16
#define GPIO_OUTPUT_IO_1 5 
#define GPIO_OUTPUT_IO_2 4
#define GPIO_OUTPUT_IO_3 0

void gpio_init(){
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}

void blink_task(){
    char* task_label = pcTaskGetTaskName(NULL);
    
    while(1){
        // gpio_set_level(GPIO_OUTPUT_IO_4, 1);
        // printf("led high \n");
        // vTaskDelay(1000/portTICK_RATE_MS);
        // gpio_set_level(GPIO_OUTPUT_IO_4, 0);
        // printf("led low \n");
        vTaskDelay(1000/portTICK_RATE_MS);
        ESP_LOGI(task_label, "OK");
    }
}


void display_test(){
    display disp0;

    disp0.din = GPIO_OUTPUT_IO_0;
    disp0.clk = GPIO_OUTPUT_IO_1;
    disp0.out_en = GPIO_OUTPUT_IO_2;
    disp0.rst = GPIO_OUTPUT_IO_3;

    display_init(&disp0);

    //reset_display(&disp0);
    set_display(&disp0, 693, 0, 0);

    run_display(&disp0);

}

void app_main()
{
    gpio_init();
    //display_test();
    //xTaskCreate(blink_task, "blink", 2048, NULL, 2, NULL);
    xTaskCreate(display_test, "display", 4096, NULL, 1, NULL);
}
