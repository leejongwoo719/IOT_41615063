#include <Servo.h>        //서보모터 헤더파일
#include <Stepper.h>      //스탭모터 헤더파일

int i = 0;                 //

//서보모터 전역변수
Servo servo1;             //서보모터 1번
Servo servo2;             //서보모터 2번
//스탭모터 전역변수
const int steps = 64;                 //스탭 초기값 설정
Stepper stepper(steps, 11,9,10,8);   //스탭모터 구동 포트 설정

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(50); //스탭모터 속도
  servo1.write(0);      //서보모터 1번 초기 각도
  servo2.write(0);      //서보모터 2번 초기 각도
  servo1.attach(6);     //서보모터 1번 신호 출력 포트 설정
  servo2.attach(7);     //서보모터 2번 신호 출력 포트 설정
  //포트 I/O 설정
  pinMode(2,INPUT);     //"servo_test" 명령 하달
  pinMode(3,INPUT);     //"step_test" 명령 하달
  pinMode(4,INPUT);     //"AllStop!" 명령 하달
  pinMode(5,INPUT);     //"BOB!!!" 명령 하달
  pinMode(6,OUTPUT);    //출력-> 1번 서보모터
  pinMode(7,OUTPUT);    //출력-> 2번 서보모터
  pinMode(8,OUTPUT);    //출력-> 스탭모터 INT1
  pinMode(9,OUTPUT);    //출력-> 스탭모터 INT2
  pinMode(10,OUTPUT);   //출력-> 스탭모터 INT3
  pinMode(11,OUTPUT);   //출력-> 스탭모터 INT4
}

void loop() {
  Serial.begin("Motor=ON");
  delay(2000);
  
  if(digitalRead(2)==1){
        Serial.print("SERVO");
        ServoMove();
        if(digitalRead(4)==1){
        motorStop();
        }
      
  }
  else if(digitalRead(3)==1){
        Serial.print("STEP");
        StepMove();
        if(digitalRead(4)==1){
        motorStop();
  }
  }
  else if(digitalRead(5)==1){
       Serial.print("BOB!!");
        delay(500);
        servo_move1();
        delay(500);
        StepMove();
        delay(500);
        servo_move2();
        delay(500);
  }
  else {
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
  }
}

//서보모터 동작
void ServoMove(){
  delay(1000);
  servo_move1();
  delay(5000);
  servo_move2();
  delay(1000);
}

void servo_move1(){         //서보모터 ON동작
  
  for(i = 0; i < 180 ; i++) 
  { 
    servo1.write(i);
    delay(30);                                    
  }
  delay(1000);
  for(i = 0; i < 90 ; i++) 
  { 
    servo2.write(i);
    delay(50);                                    
  }
}

void servo_move2(){         //서보모터 OFF동작
  i = 0;
  for(i = 90; i > 0 ; i--) 
  { 
    servo2.write(i);
    delay(30);                                    
  } 
   delay(1000);
  for(i = 180; i > 0 ; i--) 
  { 
    servo1.write(i);
    delay(50);                                    
  }
}

//스탭모터 동작
void StepMove(){
    delay(2000);
    for(int i=0; i<16; i++) {  // 64 * 32 = 2048 한바퀴
    stepper.step(steps);
    }
    delay(2000);
  
}

//모터 정지
void motorStop(){
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        Serial.print("Motor Stop!!");
}

