#include<Stepper.h>      //스탭모터 헤더파일
#include<Servo.h>        //서보모터 헤더파일

int set_mode = 0;       
//ServoMotor set
Servo myservo; 
int servo = 0;
int pos =0;

//StepMotor set
int lap = 2048; //2048-->360도 회전
Stepper Step1 (lap, 11,9,10,8);
Stepper Step2 (lap, 8,10,9,11);

// pin settings
#define INT1  2 //Servotest
#define INT2  3 //steptest
#define INT3  4 //ALL STOP
#define INT4  5 //BOB

#define Servo_PIN1   6  //servo motor
#define Servo_PIN2   7   //servo motor
#define Step_1PIN    8   //step motor int1
#define Step_2PIN    9   //step motor int2
#define Step_3PIN    10  //step motor int3
#define Step_4PIN    11  //step motor int4
     
void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  Step1.setSpeed(20); 
  Step2.setSpeed(20); 
  //servo
  myservo.attach(Servo_PIN1);
  myservo.attach(Servo_PIN2);
  //step
}

void ServoMoter(){
  if(INT1=HIGH){
    set_mode = 1;
    Serial.println("INIT=1");
  }
}

void loop() {
  Action_Motor();
}

void Action_Motor() {
    switch (set_mode){
      case 1:
      Serial.println("SERVO");
        servo_move();
        break;
      case 2:
        Serial.println("STEP");
        step_move_CW();
        delay(5000);
        step_move_CCW();
        break;
      case 3: 
        Serial.println("ALLSTOP");
        motor_stop();
        break;
      case 4:
        Serial.println("BOB");
        servo_move();
        delay(2000);
        step_move_CW();
        delay(5000);
        step_move_CCW();
        delay(2000);
        servo_move();
        delay(10000);
        break;
  }
}

//서보모터 동작
void servo_move(){
  for(pos = 0; pos < 60; pos += 1) 
  { 
    myservo.write(pos);
    delay(20);                                    //delay값을 조정하여 모터의 속도를 컨터롤가능
  } 
  delay(5000);
  for(pos = 60; pos>0; pos -=1)
  { 
    myservo.write(pos); 
    delay(20); 
  }
}

//스탭모터 동작(정,역운전)
//step_move_Clock Wise
void step_move_CW() {
  Step1.step(lap); //오른쪽으로 한바퀴
}

//step_move_Counter Clock Wise
void step_move_CCW() {
  Step2.step(lap); //오른쪽으로 한바퀴
}

//moter_stop
void motor_stop() {
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
}


