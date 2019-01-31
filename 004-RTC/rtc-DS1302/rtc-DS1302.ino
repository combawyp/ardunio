/* 
 *  读写DS1302 时钟芯片 
 *  @author Yangtf
 *  很棒的文档 http://www.21ic.com/jichuzhishi/datasheet/DS1302/data/185858.html
 *  时序图 http://www.21ic.com/d/file/201307/0a93263a0126e1580cc71c89dce1fda9.jpg
 *  
*/ 
#define RST 7 
#define SCLK 6 
#define IO 5 
//#define L(item) digitalWrite((item),LOW) 
//#define H(item) digitalWrite((item),HIGH) 
#define uchar unsigned char 
void setup() 
{
 
pinMode(RST,OUTPUT);
 pinMode(SCLK,OUTPUT);
 pinMode(IO,OUTPUT);
 Serial.begin(9600);
 attachInterrupt(0, settm, FALLING );
 }
 void writeData(unsigned char addr,unsigned char dat){
 pinMode(IO,OUTPUT);
 digitalWrite(RST,LOW);
 //下拉低，再拉高 digitalWrite(SCLK,LOW) ;
 //SCLK的上升沿， 芯片会读取IO端口 delayMicroseconds(1);
 digitalWrite(RST,HIGH);
 int i;
 for(i =0;
i<8;
i++){
 digitalWrite(SCLK,LOW);
 digitalWrite(IO, addr&1);
 addr =addr>>1;
 digitalWrite(SCLK,HIGH);
 delayMicroseconds(1);
 }
 for(i =0;
i<8;
i++){
 digitalWrite(SCLK,LOW);
 digitalWrite(IO, dat&1);
 dat =dat>>1;
 digitalWrite(SCLK,HIGH);
 delayMicroseconds(1);
 }
 digitalWrite(RST,LOW);
 }
 uchar readData(uchar addr){
 addr = addr | 1;
 //读操作最低位置为1 pinMode(IO,OUTPUT);
 digitalWrite(RST,LOW);
 //下拉低，再拉高 digitalWrite(SCLK,LOW) ;
 //SCLK的上升沿， 芯片会读取IO端口 delayMicroseconds(1);
 digitalWrite(RST,HIGH);
 int i;
 for(i =0;
i<8;
i++){
 digitalWrite(SCLK,LOW);
 digitalWrite(IO, addr&1);
 addr =addr>>1;
 digitalWrite(SCLK,HIGH);
 delayMicroseconds(1);
 }
 pinMode(IO,INPUT);
 int dat = 0;
 for(i =0;
i<8;
i++){
 digitalWrite(SCLK,LOW);
 delayMicroseconds(10);
 uchar b = digitalRead(IO);
 dat = dat >>1;
 //先向右平移 dat = dat | (b<<7);
 //将所得放入最高位 digitalWrite(SCLK,HIGH);
 delayMicroseconds(1);
 }
 digitalWrite(RST,LOW);
 return dat ;
 }
 #define SECOND  0x80 #define MIN 0x82 #define HOUR 0x84 #define DAY 0x86 #define MONTH 0x88 #define YEAR 0x8C #define WEEK 0x8A void writeTimeUnit(uchar TYPE,uchar data){
 uchar high = data / 10;
 uchar low = data % 10;
 uchar d = ((data /10) << 4) | (data % 10);
 writeData(TYPE,data);
 }
 uchar readTimeUnit(uchar TYPE){
 uchar r = readData(TYPE);
 r = 10*(r >> 4)+ (r & 0xf);
 return r;
 }
 void writeAllTm(uchar tm[]){
 uchar s = SECOND;
 for(uchar i=0;
i<5;
i++){
 writeTimeUnit(s,tm[5-i]);
 s+=2;
 }
 writeTimeUnit(YEAR,tm[0]);
 }
 void readAllTm(uchar tm[]){
 uchar s = SECOND;
 for(uchar i=0;
i<5;
i++){
 tm[5-i] = readTimeUnit(s);
 s+=2;
 }
 tm[0] = readTimeUnit(YEAR);
 tm[6] = readTimeUnit(WEEK);
 }
 void printTm(uchar tm[]){
 Serial.print(tm[0]);
 Serial.print("-");
 Serial.print(tm[1]);
 Serial.print("-");
 Serial.print(tm[2]);
 Serial.print(" ");
 Serial.print(tm[3]);
 Serial.print(":");
 Serial.print(tm[4]);
 Serial.print(":");
 Serial.print(tm[5]);
 Serial.print(" week ");
 Serial.print(tm[6]);
 Serial.println();
 }
 uchar st = 0;
 void loop() {
 uchar tm[7] = {
0}
;
 readAllTm(tm);
 printTm(tm);
 delay(1000);
 }
 void settm()//中断函数 {
 uchar tm[] = {
11,12,13,4,5,6 ,0}
;
 // 2011-12-22 3:4:1 Serial.println("set tm ...");
 writeAllTm(tm);
 }
