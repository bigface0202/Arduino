#include <SoftwareSerial.h>
int bluetoothRx = 12;  // RX-I of bluetooth
int bluetoothTx = 13;  // TX-O of bluetooth

SoftwareSerial mySerial(bluetoothRx, bluetoothTx); // RX, TX
int rsvData = 0;
int led = 13;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    rsvData = Serial.read();
    if (rsvData == '1') {
      digitalWrite(13, HIGH);
      Serial.println("LED on");
    } else if (rsvData == '0') {
      digitalWrite(13, LOW);
      Serial.println("LED off");
    }
    delay(100);
  }
}
