# segmentDriver
 segmentDriver - arduino library that drives common cathode seven segment display
 		directly from microcontroller.
```
      _a
     __
_f |    | _b    Display(int a, int b, int c, int d, int e , int f, int g,
     _g                 int dp, int s1, int s2, int s3, int s4); //initialize a new display
     -- 
_e |    | _c    ShowNuberDec(int number); //displays the number    
     __ . dp    ShowNuber(int address,int number) //displays the number on the selected digit 
                   
     _d         HoldDisplay(), ClearDisplay() //clock signal for the display                           
```          

### Code example:
```
#include "Arduino.h"
#include "SevenSegmentDriver.h"
				
//	        a   b   c   d   e  f  g   dp s1 s2  s3 s4
Display display(D13,D12,D11,D10,D9,D8,D14,D15,D0,D1,D2,D3);

void setup(){

}

void loop(){
	for (int i = 0; i < 10000; ++i)
	{
		display.ShowNuberDec(i);
		display.ClearDisplay();
		delay(2);
		display.HoldDisplay();
		delay(2);		
	}
}
```
