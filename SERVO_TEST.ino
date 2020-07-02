/* The Arduino code for establishing the communication between MATLAB and Arduino 
To illustrate the main ideas, we use an example of receiving the data for controlling the servo motor. 

The Arduino code receives the sequence:
a -> Servo1 control
b -> Servo2 control

For example,
a 13 means angle of servo1 will be 13;

Author: Enes Alp
Date: July 2020
Gaziantep University
*/


#include <Servo.h>

#define mavi 2
#define sari 3
#define kirmizi 4
#define high LOW
#define low HIGH
Servo myServo1, myServo2;
const byte servo1 = 9;
const byte servo2 = 10;
float oku,temp;
void setup() 
{
  Serial.begin(115200);
  while (!Serial) { // Serial portun hazır olmasını bekle.
    ;
  }
  myServo1.attach(servo1);
  myServo2.attach(servo2);
  pinMode(mavi,OUTPUT);
  pinMode(sari,OUTPUT);
  pinMode(kirmizi,OUTPUT);
}

void loop()
{
  if(Serial.available()>0)
  {
      char S = (char)Serial.read();
      delay(10);
      switch(S){
        case 'a':
          digitalWrite(kirmizi,low);
          digitalWrite(mavi,high);
          digitalWrite(sari,low);
          Servo1_don();
          break;
        case 'b':
          digitalWrite(kirmizi,low);
          digitalWrite(mavi,low);
          digitalWrite(sari,high);
          Servo2_don();
          break;
      }
          digitalWrite(kirmizi,high);
          digitalWrite(mavi,low);
          digitalWrite(sari,low);
  }

}

void Servo1_don()
{
    Serial.write("S1'e girdi!!\r");
    delay(50);
    temp = 0.f;
    while(true)
    {
    oku = Serial.parseFloat(); //Serial haberleşme ile okunan değer 0-180 deger arasında olmalı.
    if(oku>0)
    temp = oku;
    if(temp >= 0 && temp <= 180.f)
    {
      myServo1.write(temp); 
    }
    else
    break;
    }
}

void Servo2_don()
{
  Serial.write("S2'e girdi!!\r");
  delay(10);
  temp = 0.f;
    while(true)
    {
    oku = Serial.parseFloat(); //Serial haberleşme ile okunan değer 0-180 deger arasında olmalı.
    if(oku>0)
    temp = oku;
    if(temp >= 0 && temp <= 180.f)
    {
      if (temp>=155)
      {
        temp = 155;
      }
      myServo2.write(temp); 
    }
    else
    break;
    }
}
