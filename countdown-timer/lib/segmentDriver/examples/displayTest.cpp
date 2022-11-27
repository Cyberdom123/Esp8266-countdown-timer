#include "Arduino.h"
#include "SevenSegmentDriver.h"
				
//				 a   b   c   d   e  f  g   dp s1 s2  s3 s4
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
