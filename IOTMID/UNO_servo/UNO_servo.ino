#include<Servo.h>        //서보모터 헤더파일

int i = 0;

Servo servo1; 
Servo servo2; 

void setup() {
  
  servo1.write(0);
  servo2.write(0);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  //servo
  servo1.attach(6);
  servo2.attach(7);
}

void loop() {
  if(digitalRead(2)==1)
     ServoMove();
}

void ServoMove(){
  delay(2000);
  servo_move1();
  delay(5000);
  servo_move2();
  delay(2000);
}

//서보모터 동작
void servo_move1(){
  
  for(i = 0; i < 180 ; i++) 
  { 
    servo1.write(i);
    delay(30);                                    //delay값을 조정하여 모터의 속도를 컨터롤가능
  }
  delay(2000);
  for(i = 0; i < 90 ; i++) 
  { 
    servo2.write(i);
    delay(30);                                    //delay값을 조정하여 모터의 속도를 컨터롤가능
  }
}

void servo_move2(){
  i = 0;
  for(i = 90; i > 0 ; i--) 
  { 
    servo2.write(i);
    delay(30);                                    //delay값을 조정하여 모터의 속도를 컨터롤가능
  } 
   delay(2000);
  for(i = 180; i > 0 ; i--) 
  { 
    servo1.write(i);
    delay(30);                                    //delay값을 조정하여 모터의 속도를 컨터롤가능
  }
}

