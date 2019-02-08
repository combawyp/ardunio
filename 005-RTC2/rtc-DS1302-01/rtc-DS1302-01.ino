#include <stdio.h> 
#include <DS1302.h> 

namespace { 
const int kCePin = 7; // 复位引脚 
const int kIoPin = 5; // 数据引脚 
const int kSclkPin = 6; // 时钟引脚 
DS1302 rtc(kCePin, kIoPin, kSclkPin); 

String dayAsString(const Time::Day day) 
{ 
	switch (day) { 
	case Time::kSunday: 
		return "Sunday"; 
	case Time::kMonday: 
		return "Monday"; 
	case Time::kTuesday: 
		return "Tuesday"; 
	case Time::kWednesday: 
		return "Wednesday"; 
	case Time::kThursday: 
		return "Thursday"; 
	case Time::kFriday: 
		return "Friday"; 
	case Time::kSaturday: 
		return "Saturday"; 
	} 
	
	return "(unknown day)"; 
} 
void printTime() 
{ 
	// 从模块获得当前时间 
	Time t = rtc.time(); // 星期几？ 
	const String day = dayAsString(t.day); // 格式化时间数据 
	char buf[50]; 
	snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d", day.c_str(), t.yr, t.mon, t.date, t.hr, t.min, t.sec); 
	Serial.println(buf); 
} 
} 
// namespace 
void setup() 
{ 
	Serial.begin(9600); 
	rtc.writeProtect(false); 
	rtc.halt(false); 
	// 设置初始时间为 2018-1-18,17:28:00 星期四 
//	Time t(2019, 2, 8, 18, 51, 0, Time::kThursday); 
//	rtc.time(t); 
} 
void loop() 
{ 
	printTime(); 
	delay(1000); 
}
