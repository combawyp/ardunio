#include <Servo.h>
Servo turnLrServvo;
Servo turnUdServvo;
int pos = 0;
int posUD = 0;
void setup() {
  turnLrServvo.attach(9);
  turnUdServvo.attach(10);
}

void loop() {
  for(pos = 0; pos < 180; pos += 1){
    turnLrServvo.write(pos);
    delay(30);
  }
  for(pos = 180; pos>=1; pos-=1) {
    turnLrServvo.write(pos);
    delay(10);
    for(posUD = 90; posUD<110; posUD+=1)
    {
      turnUdServvo.write(posUD);
      delay(15);
    }
    for(posUD = 110; posUD>90; posUD-=1)
    {
      turnUdServvo.write(posUD);
      delay(15);
    }
  }
}
