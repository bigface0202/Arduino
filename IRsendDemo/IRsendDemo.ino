/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

IRsend irsend;
const int analogPin = A1;
int outputvalue = 0;

void setup()
{
  Serial.begin(9600);
}

void loop() {
 
	//for (int i = 0; i < 3; i++) {
		//irsend.sendSony(0xa90, 12);
		//delay(40);
	//}
	//delay(5000); //5 second delay between each signal burst

 outputvalue = analogRead(analogPin);
 Serial.print("\n");
 Serial.print(outputvalue);
 //if(outputvalue == 0){
  irsend.sendSony(0x68B90, 20);
    //delay(100);
 //   }
 //   else
   
    //irsend.sendSony(0x68B92, 20);
    delay(100);
    //irsend.sendSony(0x68B92, 20);
    //delay(100);
}
