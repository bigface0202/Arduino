/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;

//int RECV_PIN2 = 10;

IRrecv irrecv(RECV_PIN);
//IRrecv irrecv(RECV_PIN2);

decode_results results;

void setup()
{
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  digitalWrite(5,LOW);
  if (irrecv.decode(&results)) {
    if (results.decode_type == NEC) {
      Serial.print("NEC: ");
      digitalWrite(5,LOW);
    } else if (results.decode_type == SONY) {
      Serial.print("SONY: ");
      digitalWrite(5,HIGH);
      delay(1000);
    } else if (results.decode_type == RC5) {
      Serial.print("RC5: ");
      digitalWrite(5,LOW);
    } else if (results.decode_type == RC6) {
      Serial.print("RC6: ");
      digitalWrite(5,LOW);
    } else if (results.decode_type == UNKNOWN) {
      Serial.print("UNKNOWN: ");
      digitalWrite(5,LOW);
    }
    //digitalWrite(5,LOW);
    Serial.println(results.value);
    irrecv.resume(); // Receive the next value
    //if (results.value,HEX == "ED30D317")
    //{
    //  digitalWrite(5,HIGH);
    //}    
  }
  delay(100);
}
