#include <Stepper.h>

const int stepsPerRevolution = 64; 
Stepper myStepper(stepsPerRevolution, 11,9,10,8); 
void setup() {
  myStepper.setSpeed(50);
}
void loop() {
  if(digitalRead(3)==HIGH){
      delay(2000);
  // 시계 반대 방향으로 한바퀴 회전
  for(int i=0; i<16; i++) {  // 64 * 32 = 2048 한바퀴
    myStepper.step(stepsPerRevolution);
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
