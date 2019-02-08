#include <Servo.h>
Servo turnLrServvo;
Servo turnUdServvo;

int JoyStick_X = 0; //定义PS2摇杆的X轴，ANALOG IN的Pin0
int JoyStick_Y = 1; //定义PS2摇杆的Y轴，ANALOG IN的Pin1
int JoyStick_Z = 3; //定义PS2摇杆的Z轴，接在DIGITAL区域的Pin3

int pos = 90;
int posUD = 100;
void setup() {
  turnLrServvo.attach(9);
  turnUdServvo.attach(10);
  pinMode(JoyStick_Z, INPUT); //定义PS2的Z轴为输入
}

void loop() {
  int x,y,z;
  
  x=analogRead(JoyStick_X);
  y=analogRead(JoyStick_Y);
  z=digitalRead(JoyStick_Z);

  if(250>x) pos = (pos>180) ? 180:(pos+1);
  if(750<x) pos = (pos<2) ? 2:(pos-1);
  
  if(250>y) posUD = (posUD>130) ? 130:(posUD+1);
  if(750<y) posUD = (posUD<80) ? 80:(posUD-1);
  
  if(0==z)
  {
    pos = 90;
    posUD = 100;
  }
  
  turnLrServvo.write(pos);
  turnUdServvo.write(posUD);
 
  delay(30);
}
