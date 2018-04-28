#include <Arduino.h>
#include <IRremote.h>

//Functions
void Laser_Sensor();
void repeatEMG();
void IR_Receptor();
void IndicateCharging();

//Laser receptor
const int LSpin = 4;// Pin to read the laser sensor
int points = 0;
int LaserValue = 0;

//EMG Sensor
const int emgPin = 2;// Pin to read the EMG sensor
int emg = 0;
int emgfullcharge = 8;//led to indicate full charge
int emg_counter = 0;
int emgchargeLED1 = 27;
int emgchargeLED2 = 26;
int emgchargeLED3 = 32;
int emgchargeLED4 = 33;


// IR receptor
int IR_receptorPin = 11;//Pin used to read IR values
IRrecv irrecv(IR_receptorPin);//Create an object
decode_results results;
//int IR_Impact = 5;
int IR_counter = 0;

//Death variable
int end = 0;

void setup() {
        // initialize serial communication at 38400 bits per second:
        Serial.begin(115200);
        irrecv.enableIRIn(); // Start the receiver
        pinMode(5,OUTPUT);
}

void loop() {
        //IR reding
        IR_Receptor();
        digitalWrite(5,LOW);
        Serial.println("Signal detected!!");

}


//Decode the IR pulse
void IR_Receptor() {
        //digitalWrite(IR_Impact,LOW);
        if (irrecv.decode(&results)) {
                if (results.decode_type == SONY) {
                        //Serial.write('3');
                        digitalWrite(5,HIGH);
                        delay(1000);
                }
                irrecv.resume(); // Receive the next value
        }
}