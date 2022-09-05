#include <Arduino.h>
#include "segmentDriver.h"

int currentAddress = 1;
int currentNumber = 1234;

void HoldDisplay(){
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

void ShowNuberDec(int number){
  currentNumber = number;
}

void ShowNuber(int address,int number){
  switch(address){
    case 1:
      digitalWrite(D3, HIGH);
      break;
    case 2:
      digitalWrite(D2, HIGH);
      break;
    case 3:
      digitalWrite(D1, HIGH);
      break;
    case 4:
      digitalWrite(D0, HIGH);
      break;
  }

  switch(number){
    case 0:
      digitalWrite(D8, HIGH);
      digitalWrite(D9, HIGH);
      digitalWrite(D10, HIGH);
      digitalWrite(D11, HIGH);
      digitalWrite(D12, HIGH);
      digitalWrite(D13, HIGH);
      break;
    case 1:
      digitalWrite(D11, HIGH);
      digitalWrite(D12, HIGH);
      break;
    case 2:
      digitalWrite(D9, HIGH);
      digitalWrite(D10, HIGH);
      digitalWrite(D12, HIGH);
      digitalWrite(D13, HIGH);
      digitalWrite(D14, HIGH);
      break;
    case 3:
      digitalWrite(D10, HIGH);
      digitalWrite(D11, HIGH);
      digitalWrite(D12, HIGH);
      digitalWrite(D13, HIGH);
      digitalWrite(D14, HIGH);
      break;
    case 4:
      digitalWrite(D8, HIGH);
      digitalWrite(D11, HIGH);
      digitalWrite(D12, HIGH);
      digitalWrite(D14, HIGH);
      break;
    case 5:
      digitalWrite(D8, HIGH);
      digitalWrite(D10, HIGH);
      digitalWrite(D11, HIGH);
      digitalWrite(D13, HIGH);
      digitalWrite(D14, HIGH);
      break;
    case 6:
      digitalWrite(D8, HIGH);
      digitalWrite(D9, HIGH);
      digitalWrite(D10, HIGH);
      digitalWrite(D11, HIGH);
      digitalWrite(D13, HIGH);
      digitalWrite(D14, HIGH);
      break;
    case 7:
      digitalWrite(D11, HIGH);
      digitalWrite(D12, HIGH);
      digitalWrite(D13, HIGH);
      break;
    case 8:
      digitalWrite(D8, HIGH);
      digitalWrite(D9, HIGH);
      digitalWrite(D10, HIGH);
      digitalWrite(D11, HIGH);
      digitalWrite(D12, HIGH);
      digitalWrite(D13, HIGH);
      digitalWrite(D14, HIGH);
      break;
    case 9:
      digitalWrite(D8, HIGH);
      digitalWrite(D10, HIGH);
      digitalWrite(D11, HIGH);
      digitalWrite(D12, HIGH);
      digitalWrite(D13, HIGH);
      digitalWrite(D14, HIGH);
      break;
  }
}

void ClearDisplay(){
  digitalWrite(D0, LOW);   
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);

  digitalWrite(D8, LOW);
  digitalWrite(D9, LOW);
  digitalWrite(D10, LOW);
  digitalWrite(D11, LOW);
  digitalWrite(D12, LOW);
  digitalWrite(D13, LOW);
  digitalWrite(D14, LOW);
}

void Initialilze() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);

  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(D12, OUTPUT);
  pinMode(D13, OUTPUT);
  pinMode(D14, OUTPUT);
  pinMode(D15, OUTPUT);
}
