#include <Stepper.h>

const int steps = 64; 
Stepper stepper(steps, 11,9,10,8); 
void setup() {
  stepper.setSpeed(50);
}
void loop() {
  if(digitalRead(3)==HIGH){
      delay(2000);
  for(int i=0; i<16; i++) {  // 64 * 32 = 2048 한바퀴
    stepper.step(steps);
  }
  delay(5000);
  }
  else{
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }
}
