/*   메카트로닉스공학과 3학년B반 41615063이종우
//AP mode test OK good 20201015
//WiFi 설정 IoT-AP 연결
D0  16 LED PULLUP 10K
D1  5 
D2  4 
D3  0 FLASH LEFT
D4  2    (SDA)
D5  14   (SCL)OK
D6  12 R UP
D7  13 B DOWN
D8  15 MOTOR G PULLDOWN 10K
D9  3 RX  
D10 1 TX  
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
int i = 0;

//PIN settings
#define PIN1     D5
#define PIN2     D6
#define PIN3     D7
#define PIN4     D8

// WiFi settings
#define WIFI_MODE   1 // 1 = AP mode, 2 = STA mode
#define SSID_AP     "iot-ljw"    // for AP mode
#define PASSWORD_AP ""           // for AP mode
#define SSID_STA     "KT_GiGA_2G_Wave2_C493"     // for STA mode
#define PASSWORD_STA "wifi_password" // for STA mode

//IP for AP mode
IPAddress local_ip(192, 168, 4, 50); 
IPAddress gateway(192, 168, 4, 50); 
IPAddress subnet(255, 255, 255, 0); 
ESP8266WebServer server(80);
int set_mode = 0; //select mode action

// initialize
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN1,OUTPUT);
  pinMode(PIN2,OUTPUT);
  pinMode(PIN3,OUTPUT);
  pinMode(PIN4,OUTPUT);

  Serial.begin(9600);
  Serial.println("Wifi Control");

  if (WIFI_MODE == 1) { // AP mode
    WiFi.softAP(SSID_AP, PASSWORD_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
  } else { // STA mode
    WiFi.begin(SSID_STA, PASSWORD_STA);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected! IP: ");
    Serial.println(WiFi.localIP()); //
  }

  // setup web server to handle specific HTTP requests
  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/servoon", HTTP_GET, handle_servoon); 
  server.on("/stepon", HTTP_GET, handle_stepon);
  server.on("/allstop", HTTP_GET, handle_allstop);
  server.on("/bobon",HTTP_GET, handle_bobon);
  
  //start server
  server.begin();
  Serial.println("ESP8266 web server started...");
}


// handle HTTP requests and arduino control 
void loop() { 
  server.handleClient();
  ardu_action();
  delay(1000);
}


// HTTP request: on connect
void handle_OnConnect() {
  set_mode = 0;
}
// Servo_test
void handle_servoon() {
  set_mode = 1;
}
// Step_test
void handle_stepon() {
  set_mode = 2; 
}
// ALL STOP!
void handle_allstop() {
  set_mode = 3;
}
// BOB
void handle_bobon() {
  set_mode = 4;
}


// control mode select
void ardu_action() {
  switch (set_mode) {
    case 0: // all off
      
      digitalWrite(PIN1,LOW);
      digitalWrite(PIN2,LOW);
      digitalWrite(PIN3,LOW);
      digitalWrite(PIN4,LOW);
      
      ledBlink2();
      delay(2000);
      
      break;
      
    case 1: // Servo
      ledOff();
      digitalWrite(LED_BUILTIN,LOW);
      digitalWrite(PIN1,HIGH);
      Serial.println("SERVO MOTER-MOVE!");
      delay(4000);
      digitalWrite(PIN1,LOW);
      delay(4000);
      break;
      
    case 2: // Step
    
      ledOff();
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(PIN2,HIGH);
      Serial.println("STEP MOTOR_MOVE!");
      delay(4000);
      digitalWrite(PIN2,LOW);
      delay(4000);
      break;
    case 3: // ALL STOP
    
      ledBlink1();
      ledOff();
      digitalWrite(PIN3,HIGH);
      delay(5000);
      Serial.println("ALL STOP!!");
      digitalWrite(PIN3,LOW);
      delay(2000);
      break;
      
    case 4: // BOB

      ledOff();
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(PIN4,HIGH);
      Serial.println("BOB!!!");
      delay(4000);
      while(1){
        digitalWrite(PIN4,LOW);
      }
      break;
  }
}

void ledOff(){

      digitalWrite(PIN1,LOW);
      digitalWrite(PIN2,LOW);
      digitalWrite(PIN3,LOW);
      digitalWrite(PIN4,LOW);
      
}

void ledBlink1(){
  
      digitalWrite(LED_BUILTIN, HIGH);   
      delay(1000);                       
      digitalWrite(LED_BUILTIN, LOW);    
      delay(1000);
      digitalWrite(LED_BUILTIN, HIGH);   
      delay(1000);                       
      digitalWrite(LED_BUILTIN, LOW);    
      delay(1000); 
    
}

void ledBlink2(){
  
      digitalWrite(LED_BUILTIN, HIGH);   
      delay(500);                       
      digitalWrite(LED_BUILTIN, LOW);    
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);   
      delay(500);                       
      digitalWrite(LED_BUILTIN, LOW);    
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);   
      delay(500); 
      
}

