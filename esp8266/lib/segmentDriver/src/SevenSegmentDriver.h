/*
  segmentDriver.h -  arduino library that drives common cathode seven 
                     segment display directly from microcontroller.
  Created by Dominik Michalczyk, September 11, 2022.
  Released into the public domain.
*/
/*
     _a
     __
_f |    | _b
     _g     
     -- 
_e |    | _c
     __ . dp

     _d

*/

#ifndef SEVENSEGMENTDRIVER_H
#define SEVENSEGMENTDRIVER_H

#include "Arduino.h"

class Display
{
  public:
    Display(int a, int b, int c, int d, int e , int f, int g,
            int dp, int s1, int s2, int s3, int s4);
    
    void ShowNuberDec(int number);

    void ShowNuber(int address,int number);

    void HoldDisplay();

    void ClearDisplay();
  private:
    int _a;
    int _b;
    int _c;
    int _d;
    int _e;
    int _f;
    int _g;
    int _dp;
    int _s1;
    int _s2;
    int _s3;
    int _s4;
};

#endif
