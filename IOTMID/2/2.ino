#include<Servo.h> 

Servo myservo; 
int servo = 0;
int servoPin = 5;
int pos = 0; 
 
void setup() 
{ 
  myservo.attach(servoPin); 
} 
 
void loop() 
{ 
  for(servo=0; servo<3; servo++){
  for(pos = 0; pos < 180; pos += 1) 
  { 
    myservo.write(pos);
    delay(15); //delay값을 조정하여 모터의 속도를 컨터롤가능
  } 
  delay(3000);
  for(pos = 180; pos>=1; pos-=1)
  { 
    myservo.write(pos); 
    delay(15); 
  } 
  delay(3000);
  }
  delay(5000);
}
