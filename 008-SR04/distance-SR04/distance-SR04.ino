const int ting = 12;	// 设定SR04连接到Arduino引脚
const int echo = 13;	// 设定SR04连接到Arduino引脚
float distance;				// 定义一个浮点型的变量

void setup()
{
  Serial.begin(9600);										// 设置波特率
  pinMode(ting, OUTPUT);								// 连接SR04的引脚
  pinMode(echo, INPUT);									//设置输入状态
  Serial.println("ultrasonic sensor");	//
}

void loop()
{
  //产生一个10US的高脉冲去触发Trigpin
  digitalWrite(ting, LOW);
  delayMicroseconds(2);
  digitalWrite(ting, HIGH);
  delayMicroseconds(10);
  digitalWrite(ting, LOW);
  
  distance = pulseIn(echo, HIGH) / 58.00;	//检测脉冲宽度，并计算出距离    
   
  Serial.print(distance);	//打印
  Serial.print("cm");			//打印
  Serial.println();				//打印
  
  delay(1000);
}
