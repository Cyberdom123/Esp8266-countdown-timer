// #include "Arduino.h"
// #include "ESP8266TimerInterrupt.h"
// #define TIMER_INTERRUPT_DEBUG         1
// #define _TIMERINTERRUPT_LOGLEVEL_     1

// // Select a Timer Clock
// #define USING_TIM_DIV1                true           // for shortest and most accurate timer

// #include "ESP8266TimerInterrupt.h"


// volatile bool statusLed = false;
// volatile uint32_t lastMillis = 0;

// #define TIMER_INTERVAL_MS       0.1

// // Init ESP8266 timer 1
// ESP8266Timer ITimer;

// #define din D0
// #define clk D1
// #define rst D2



// void IRAM_ATTR TimerHandler()
// {

// }

// void clk_signal(){
//     digitalWrite(clk, LOW);
//     delayMicroseconds(1);
//     digitalWrite(clk, HIGH);
//     delayMicroseconds(1);
// }

// void clear_data(){
//     digitalWrite(D2, LOW);
//     delayMicroseconds(1000);
//     digitalWrite(D2, HIGH);
// }

// void shift_data(unsigned long data, int size){
//     for (size_t i = 0; i < size; i++)
//     {
//        if(data >> i & 1){
//             digitalWrite(din, HIGH);
//        }else{
//             digitalWrite(din, LOW);
//        }
//        clk_signal();
//     }
// }

// void show_number(int num){

//     unsigned long digit;

// }

// void setup(){
//     pinMode(din, OUTPUT);
//     pinMode(clk, OUTPUT);
//     pinMode(rst, OUTPUT);
//     ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler);
// }

// void loop(){

//     // clear_data();
//     // shift_data(0b1000, 4);
//     // shift_data(0b00000011, 8);
//     // delay(4);

//     // clear_data();
//     // shift_data(0b0100, 4);
//     // shift_data(0b00100101, 8);
//     // delay(4);

//     clear_data();
//     shift_data(0b0010, 4);
//     shift_data(0b00000000, 8);
//     delay(4);

//     clear_data();
//     shift_data(0b0001, 4);
//     shift_data(0b00000000, 8);
//     delay(4);

// }