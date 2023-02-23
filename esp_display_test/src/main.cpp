#include "Arduino.h"

#define din D0
#define clk D1
#define rst D2
#define oe D3 //RCLK D-output-register 


void clk_signal(){  
    digitalWrite(clk, LOW);
    delayMicroseconds(8);
    digitalWrite(clk, HIGH);
    delayMicroseconds(8);
}

void clear_data(){
    digitalWrite(rst, LOW);
    digitalWrite(oe, HIGH);

    delayMicroseconds(100); 
    clk_signal();
    delayMicroseconds(100);

    digitalWrite(oe, LOW);
    digitalWrite(rst, HIGH);

}

void shift_data(unsigned long data, size_t size){
    for (size_t i = 0; i < size; i++)
    {
        digitalWrite(din, data >> i & 1);
        clk_signal();
    }
}

void output_enable(){
    digitalWrite(oe, HIGH);
    delayMicroseconds(100); 
    digitalWrite(oe, LOW);
}

void setup(){
    pinMode(din, OUTPUT);
    pinMode(clk, OUTPUT);
    pinMode(rst, OUTPUT);
    pinMode(oe, OUTPUT);
}

void loop(){

    clear_data(); //2 not working
    // shift_data(0b10000, 5);
    // shift_data(0b10011111, 8);
    // output_enable();
    // delay(1.5);

    shift_data((0b10011111 << 5) | 0b10000, 13);
    output_enable();
    delay(1.5);

    clear_data(); //2 not working
    shift_data((0b00000000 << 5) | 0b00100, 13);
    output_enable();
    delay(1.5);

    clear_data(); //2 not working
    shift_data((0b10011111 << 5) | 0b00010, 13);
    output_enable();
    delay(1.5);

    clear_data(); //2 not working
    shift_data((0b00100101 << 5) | 0b00001, 13);
    output_enable();
    delay(1.5);
}