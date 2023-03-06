#ifndef DISPLAY_DRIVER
#define DISPLAY_DRIVER

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "driver/gpio.h"

typedef struct 
{
    uint8_t din;
    uint8_t clk;
    uint8_t out_en;
    uint8_t rst;

    uint16_t data;
    uint8_t dot;
    uint8_t colon;
} display;


void display_init(display *new_display);

void reset_display(display *display);

void set_display(display *display, uint16_t data, uint8_t dot, uint8_t colon);

void run_display(display *display);

#endif