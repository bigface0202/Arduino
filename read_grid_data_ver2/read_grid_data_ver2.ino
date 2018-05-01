#include <Wire.h>
#include <GridEye.h>

GridEye myeye = GridEye(GridEye_DeviceAddress_1);

void setup(void)
{
  // I2Cバスに参加
  Wire.begin();
  // シリアルポート初期化
  Serial.begin(115200);
  while (!Serial) {
    ; // シリアルポート接続待ち
  }
}

// ピクセル温度データ保存用
int pixel[64];

void loop(void)
{
  // サーミスタ温度読み出し
  int sum=0, sum1=0, sum2=0, sum3=0;
  int temp = myeye.thermistorTemp();
  Serial.print(F("Thermistor Temp: "));
  Serial.println(temp * 0.065); // 1単位 = 0.065度M

  // ピクセル温度データ読み出し
  myeye.pixelOut(pixel);
  //Serial.println(F("Pixel Output: "));
  //for (int i = 0; i < 64; i++) {
  //  if (i && ((i % 8) == 0)) {
  //    Serial.println();
  //  }
  //  Serial.print(pixel[i] * 0.25); // 1単位 = 0.25度
  //  Serial.print(' ');

  for (int i = 0 ; i < 4; i++){
    //sumが左上，sum1が右上,sum2が左下,sum3が右下
    sum = sum + pixel[i]+pixel[i+8]+pixel[i+16]+pixel[i+24];
    sum1 = sum1 + pixel[i+4]+pixel[i+13]+pixel[i+21]+pixel[i+29];
    sum2 = sum2 + pixel[i+32]+pixel[i+40]+pixel[i+48]+pixel[i+56];
    sum3 = sum3 + pixel[i+36]+pixel[i+44]+pixel[i+52]+pixel[i+60];
  }
  int maxsum = max(sum,sum1);
  Serial.print(maxsum);
  int maxsum1 = max(sum2,sum3);
  Serial.println();
  Serial.print(maxsum1);
  int out_maxsum = max(maxsum,maxsum1);
  Serial.println();
  Serial.println();
  Serial.print(out_maxsum);
  Serial.println();
  analogWrite(11, 0);
  analogWrite(10, 0);
  analogWrite(9, 0);
  analogWrite(6, 0);
  if (sum < 1500){
    analogWrite(11, 0);
    analogWrite(10, 0);
    analogWrite(9, 0);
    analogWrite(6, 0);
  }
  else if (sum == out_maxsum){
    //右上
    analogWrite(11, out_maxsum/16);
    //delay(1000);
  }
  else if(sum1 == out_maxsum){
    //左上
    analogWrite(10, out_maxsum/16);
    //delay(1000);
  }
  else if(sum2 == out_maxsum){
    //右下
    analogWrite(9, out_maxsum/16);
    //delay(1000);
  }
  else if(sum3 == out_maxsum){
    //左下
    analogWrite(6, out_maxsum/16);
    //delay(1000);
  }
  //Serial.print(sum/16);
  //Serial.print(' ');
  //Serial.print(sum1/16);
  //Serial.println();
  //Serial.print(sum2/16);
  //Serial.print(' ');
  //Serial.print(sum3/16);
  
  // 1秒待つ
  //delay(1000);
}
