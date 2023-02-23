// #include "Arduino.h"

// #define din D0
// #define clk D1
// #define rst D2
// #define oe D3


// void clk_signal(){
//     digitalWrite(clk, LOW);
//     delayMicroseconds(8);
//     digitalWrite(clk, HIGH);
//     delayMicroseconds(8);
// }

// void clear_data(){
//     digitalWrite(rst, LOW);
//     digitalWrite(oe, HIGH);

//     delayMicroseconds(100); 
//     clk_signal();
//     delayMicroseconds(100);

//     digitalWrite(oe, LOW);
//     digitalWrite(rst, HIGH);

// }

// void shift_data(unsigned long data, size_t size){
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

// void output_enable(){
//     digitalWrite(oe, HIGH);
//     delayMicroseconds(100); 
//     digitalWrite(oe, LOW);
// }

// void setup(){
//     pinMode(din, OUTPUT);
//     pinMode(clk, OUTPUT);
//     pinMode(rst, OUTPUT);
//     pinMode(oe, OUTPUT);
// }

// void loop(){

//     clear_data(); //2 not working
//     shift_data(0b10000, 5);
//     shift_data(0b10011111, 8);
//     output_enable();
//     delay(1.5);

//     clear_data(); //2 not working
//     shift_data(0b00100, 5);
//     shift_data(0b00000000, 8);
//     output_enable();
//     delay(1.5);

//     clear_data(); //2 not working
//     shift_data(0b00010, 5);
//     shift_data(0b10011111, 8);
//     output_enable();
//     delay(1.5);

//     clear_data(); //2 not working
//     shift_data(0b00001, 5);
//     shift_data(0b00100101, 8);
//     output_enable();
//     delay(1.5);
// }