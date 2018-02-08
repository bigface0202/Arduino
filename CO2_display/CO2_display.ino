#include <Wire.h>

#define LCD_ADRS 0x3E
#define PWM_PIN 3

int prev_val = LOW;
long high_level_start = 0L;
long high_level_end = 0L;
long low_level_start = 0L;
long low_level_end = 0L;
int ppm = 0;

boolean is_output_ready = false;

char moji[] = "CO2 = ";

void writeData(byte t_data) {
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x40);
  Wire.write(t_data);
  Wire.endTransmission();
  delay(1);
}

void writeCommand(byte t_command) {
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x00);
  Wire.write(t_command);
  Wire.endTransmission();
  delay(10);
}

void init_LCD() {
  delay(100);
  writeCommand(0x38);
  delay(20);
  writeCommand(0x39);
  delay(20);
  writeCommand(0x14);
  delay(20);
  writeCommand(0x73);
  delay(20);
  writeCommand(0x52);
  delay(20);
  writeCommand(0x6C);
  delay(20);
  writeCommand(0x38);
  delay(20);
  writeCommand(0x01);
  delay(20);
  writeCommand(0x0C);
  delay(20);
}

void setup() {
  Serial.begin(9600);
  pinMode(PWM_PIN, INPUT);
  Wire.begin();
  init_LCD();
}

void loop() {
  long cycle_start_time = millis();
  int pin_in = digitalRead(PWM_PIN);

  if (pin_in == HIGH) {
    if (prev_val == LOW) {
      long time_high = high_level_end - high_level_start;
      long time_low = low_level_end - low_level_start;
      ppm = 5000 * (time_high - 0.002) / (time_high + time_low - 0.004);
      is_output_ready = true;
      
      high_level_start = cycle_start_time;
      prev_val = HIGH;
    } else {
      high_level_end = cycle_start_time;
    }
  } else {
    if (prev_val == HIGH) {
      low_level_start = cycle_start_time;
      prev_val = LOW;
    } else {
      low_level_end = cycle_start_time;
    }
  }

  if (is_output_ready) {
    writeCommand(0x00 + 0x01);
    for (int i = 0; i < 6; i++) {
      writeData(moji[i]);
    }
    String ppm_text = String(ppm);
    char ppm_print[4];
    ppm_text.toCharArray(ppm_print, 4);
    for (int i = 0 ; i < 4 ; i++) {
      writeData(ppm_text[i]);
    }
    is_output_ready = false;
  }
}
