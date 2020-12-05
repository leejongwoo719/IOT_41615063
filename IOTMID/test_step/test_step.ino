#include <Stepper.h>

const int stepsPerRevolution = 32; 
Stepper Step1 (stepsPerRevolution, 14,13,12,15); 
Stepper Step2 (stepsPerRevolution, 15,12,13,14); 

void setup() {
  Step1.setSpeed(300);
  Step2.setSpeed(300);
}
void loop() {
  
   delay(2000);
  // 시계 반대 방향으로 한바퀴 회전
  for(int i=0; i<64; i++) {  // 64 * 32 = 2048 한바퀴
    Step1.step(stepsPerRevolution);
    if(i==64) {
    delay(2000);
    Step2.step(stepsPerRevolution);}
  }
  delay(2000);

}

