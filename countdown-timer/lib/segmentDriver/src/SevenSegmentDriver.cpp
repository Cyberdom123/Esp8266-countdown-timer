/*
  segmentDriver.h -  arduino library that drives common cathode seven 
                     segment display directly from microcontroller.
  Created by Dominik Michalczyk, September 11, 2022.
  Released into the public domain.
*/

#include "Arduino.h"
#include "SevenSegmentDriver.h"

int currentAddress = 1;
int currentNumber = 8888;

Display::Display(int a, int b, int c, int d, int e , int f, int g,
            int dp, int s1, int s2, int s3, int s4)
{
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);

  _a = a;
  _b = b;
  _c = c;
  _d = d;
  _e = e;
  _f = f;
  _g = g;
  _dp = dp;
  _s1 = s1;
  _s2 = s2;
  _s3 = s3;
  _s4 = s4;
}


void Display::HoldDisplay(){
  switch(currentAddress){
    case 1:
      ShowNuber(1, currentNumber % 10);
      break;
    case 2:
      ShowNuber(2, floor((currentNumber % 100)/10));
      break;
    case 3:
      ShowNuber(3, floor((currentNumber % 1000)/100));
      break;
    case 4:
      ShowNuber(4, floor((currentNumber % 10000)/1000));
      break;
  }
  currentAddress ++;
  if(currentAddress == 5)
  {
    currentAddress = 1;
  }  
}

void Display::ShowNuberDec(int number){
  currentNumber = number;
}

void Display::ShowNuber(int address,int number){
  switch(address){
    case 1:
      digitalWrite(_s4, HIGH);
      break;
    case 2:
      digitalWrite(_s3, HIGH);
      break;
    case 3:
      digitalWrite(_s2, HIGH);
      break;
    case 4:
      digitalWrite(_s1, HIGH);
      break;
  }

  switch(number){
    case 0:
      digitalWrite(_f, HIGH);
      digitalWrite(_e, HIGH);
      digitalWrite(_d, HIGH);
      digitalWrite(_c, HIGH);
      digitalWrite(_b, HIGH);
      digitalWrite(_a, HIGH);
      break;
    case 1:
      digitalWrite(_c, HIGH);
      digitalWrite(_b, HIGH);
      break;
    case 2:
      digitalWrite(_e, HIGH);
      digitalWrite(_d, HIGH);
      digitalWrite(_b, HIGH);
      digitalWrite(_a, HIGH);
      digitalWrite(_g, HIGH);
      break;
    case 3:
      digitalWrite(_d, HIGH);
      digitalWrite(_c, HIGH);
      digitalWrite(_b, HIGH);
      digitalWrite(_a, HIGH);
      digitalWrite(_g, HIGH);
      break;
    case 4:
      digitalWrite(_f, HIGH);
      digitalWrite(_c, HIGH);
      digitalWrite(_b, HIGH);
      digitalWrite(_g, HIGH);
      break;
    case 5:
      digitalWrite(_f, HIGH);
      digitalWrite(_d, HIGH);
      digitalWrite(_c, HIGH);
      digitalWrite(_a, HIGH);
      digitalWrite(_g, HIGH);
      break;
    case 6:
      digitalWrite(_f, HIGH);
      digitalWrite(_e, HIGH);
      digitalWrite(_d, HIGH);
      digitalWrite(_c, HIGH);
      digitalWrite(_a, HIGH);
      digitalWrite(_g, HIGH);
      break;
    case 7:
      digitalWrite(_c, HIGH);
      digitalWrite(_b, HIGH);
      digitalWrite(_a, HIGH);
      break;
    case 8:
      digitalWrite(_f, HIGH);
      digitalWrite(_e, HIGH);
      digitalWrite(_d, HIGH);
      digitalWrite(_c, HIGH);
      digitalWrite(_b, HIGH);
      digitalWrite(_a, HIGH);
      digitalWrite(_g, HIGH);
      break;
    case 9:
      digitalWrite(_f, HIGH);
      digitalWrite(_d, HIGH);
      digitalWrite(_c, HIGH);
      digitalWrite(_b, HIGH);
      digitalWrite(_a, HIGH);
      digitalWrite(_g, HIGH);
      break;
  }
}

void Display::ClearDisplay(){
  digitalWrite(_s1, LOW);   
  digitalWrite(_s2, LOW);
  digitalWrite(_s3, LOW);
  digitalWrite(_s4, LOW);

  digitalWrite(_f, LOW);
  digitalWrite(_e, LOW);
  digitalWrite(_d, LOW);
  digitalWrite(_c, LOW);
  digitalWrite(_b, LOW);
  digitalWrite(_a, LOW);
  digitalWrite(_g, LOW);
  digitalWrite(_dp, LOW);
}
