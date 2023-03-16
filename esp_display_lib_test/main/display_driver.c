#include "dispaly_driver.h"
//       _a
//      __
// _f |    | _b    
//      _g         
//      -- 
// _e |    | _c    
//      __ . dp    
                   
//      _d                     

uint8_t dig_temp[3];
uint8_t disp_code[] ={              //common cathode 7 segment code without dp
    0x03, 0x9f, 0x25, 0x0d, 0x99,   //in order to add dot subtract one freom disp_code
    0x49, 0x41, 0x1f, 0x01, 0x09 
};

void display_init(display *new_display){
    unsigned long long GPIO_OUTPUT_PIN_SEL = ((1ULL << new_display->din)|
                (1ULL << new_display->clk)|(1ULL << new_display->out_en)|(1ULL << new_display->rst));

    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}


void reset_display(display *display){ //output register doesnt work, use output enable
    gpio_set_level(display->din, 0);

    // for (size_t i = 0; i <= 16; i++)
    // {
    //     gpio_set_level(display->clk, 1);
    //     vTaskDelay(1/portTICK_RATE_MS);
    //     gpio_set_level(display->clk, 0);
    //     vTaskDelay(1/portTICK_RATE_MS);
    // }
    gpio_set_level(display->rst, 0);

    gpio_set_level(display->out_en, 1);
    //vTaskDelay(1/portTICK_RATE_MS);
    ets_delay_us(5);
    gpio_set_level(display->out_en, 0);
    ets_delay_us(5);
    //vTaskDelay(1/portTICK_RATE_MS);

    gpio_set_level(display->rst, 1);
}

void set_display(display *display, uint16_t data, uint8_t dot, uint8_t colon){
    dig_temp[0] = data%10;
    data /= 10;
    dig_temp[1] = data%10;
    data /= 10;
    dig_temp[2] = data%10;
    data /= 10;
    dig_temp[3] = data%10;
}

void run_display(display *display){
    while (1)
    {    
        for (size_t i = 0; i < 4; i++)
        {
            reset_display(display); //not working
            //gpio_set_level(display->out_en, 0);

            // printf("%d iteration \n", i);


            // printf("disp_code:");
            // for (size_t j = 0; j < 8; j++)
            // {
            //     printf("%d", !!(disp_code[dig_temp[i]] & 1<<(7-j)));
            // }
            // printf("\n");

            uint16_t value = (disp_code[dig_temp[i]] << 8) + (1 << (4+i));
            
            // for (size_t k = 0; k < 16; k++)
            // {
            //     printf("%d", !!(value & 1 << (15-k)));
            // }
            // printf("\n");

            for (size_t l = 0; l < 16; l++)
            {
                //shift data
                //printf("%d\n", !!(value & (1 << l)));
                gpio_set_level(display->din, !!(value & (1 << l)));

                //clk
                gpio_set_level(display->clk, 1);
                //vTaskDelay(1/portTICK_RATE_MS);
                ets_delay_us(5);
                gpio_set_level(display->clk, 0);
                //vTaskDelay(1/portTICK_RATE_MS);
                ets_delay_us(5);
            }
            
            gpio_set_level(display->out_en, 1); //not working
            //vTaskDelay(2/portTICK_RATE_MS);
            ets_delay_us(2000);
            gpio_set_level(display->out_en, 0);
            //vTaskDelay(1/portTICK_RATE_MS);
            
            //gpio_set_level(display->out_en, 1);
            //vTaskDelay(2/portTICK_RATE_MS);

        }
    }
}
