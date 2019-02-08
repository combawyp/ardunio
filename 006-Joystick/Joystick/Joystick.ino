int JoyStick_X = 0; //定义PS2摇杆的X轴，ANALOG IN的Pin0
int JoyStick_Y = 1 //定义PS2摇杆的Y轴，ANALOG IN的Pin1
int JoyStick_Z = 3; //定义PS2摇杆的Z轴，是按下时触发LED灯亮起的条件，接在DIGITAL区域的Pin3
int ledPin = 12; //定义LED等的接口，接在DIGITAL区域的Pin12
int val; //定义数字变量val

void setup()
{
	pinMode(JoyStick_Z, INPUT); //定义PS2的Z轴为输入，按下时触发LED灯亮起的条件
	pinMode(ledPin,OUTPUT); //定义ledPin接口为输出
	Serial.begin(115200);
}
void loop()
{
	int x,y,z;
	
	x=analogRead(JoyStick_X);
	y=analogRead(JoyStick_Y);
	z=digitalRead(JoyStick_Z);
	
	Serial.print(x ,DEC);
	Serial.print(",");
	Serial.print(y ,DEC);
	Serial.print(",");
	Serial.println(z ,DEC);
	
	delay(100);
	
	val=digitalRead(JoyStick_Z);
	if(val==LOW)
	{
		digitalWrite(ledPin,HIGH);
	}
	else
	{
		digitalWrite(ledPin,LOW);
	}
}
