/*
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

// WiFi settings
#define WIFI_MODE   1 // 1 = AP mode, 2 = STA mode
#define SSID_AP     "iot-ljw"    // for AP mode
#define PASSWORD_AP "" // for AP mode
#define SSID_STA     "wifi_ssid"     // for STA mode
#define PASSWORD_STA "wifi_password" // for STA mode

// pin settings
#define LED1_PIN    D6   //16 pin 1 of (D0)led
#define LED2_PIN    D7   //16 pin 1 of (D0)led
#define LED3_PIN    D8   //16 pin 1 of (D0)led

//IP for AP mode
IPAddress local_ip(192, 168, 4, 100); 
IPAddress gateway(192, 168, 4, 100); 
IPAddress subnet(255, 255, 255, 0); 
ESP8266WebServer server(80);

int set_mode = 0; //select mode action
bool LED1status = LOW;
bool LED2status = LOW;
bool LED3status = LOW;

// initialize
void setup() {
  Serial.begin(9600);
  Serial.println("Wifi Control");
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  

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
  server.on("/led1on", HTTP_GET, handle_led1on);
  server.on("/led1off", HTTP_GET, handle_led1off);
  server.on("/led2on", HTTP_GET, handle_led2on);
  server.on("/led2off", HTTP_GET, handle_led2off);
  server.on("/led3on", HTTP_GET, handle_led3on);
  server.on("/led3off", HTTP_GET, handle_led3off);
  server.on("/ledallon", HTTP_GET, handle_ledallon);
  server.on("/ledalloff", HTTP_GET, handle_ledalloff);

  //start server
  server.begin();
  Serial.println("ESP8266 web server started...");
}

// handle HTTP requests and arduino control 
void loop() { 
  server.handleClient();
  ardu_action();
}

// HTTP request: on connect
void handle_OnConnect() {
  set_mode = 0; LED1status=LOW; LED2status=LOW; LED3status=LOW;
  Serial.println("Client connected");
  server.send(200, "text/html", SendHTML());
}
// LED1 ON
void handle_led1on() {
  set_mode = 1; LED1status=HIGH; 
  Serial.println("RED ON!");
  server.send(200, "text/html", SendHTML());
}
// LED1 OFF
void handle_led1off() {
  set_mode = 2; LED1status=LOW; 
  Serial.println("RED OFF!");
  server.send(200, "text/html", SendHTML());
}
// LED2 ON
void handle_led2on() {
  set_mode = 3; LED1status=HIGH; 
  Serial.println("ORANGE ON!");
  server.send(200, "text/html", SendHTML());
}
// LED2 OFF
void handle_led2off() {
  set_mode = 4; LED1status=LOW; 
  Serial.println("ORANGE OFF!");
  server.send(200, "text/html", SendHTML());
}
// LED3 ON
void handle_led3on() {
  set_mode = 5; LED1status=HIGH; 
  Serial.println("GREEN ON!");
  server.send(200, "text/html", SendHTML());
}
// LED3 OFF
void handle_led3off() {
  set_mode = 6; LED1status=LOW; 
  Serial.println("GREEN OFF!");
  server.send(200, "text/html", SendHTML());
}
// LED ALL ON
void handle_ledallon() {
  set_mode = 7; LED1status=HIGH; 
  Serial.println("ALL LED ON!");
  server.send(200, "text/html", SendHTML());
}
// LED ALL OFF
void handle_ledalloff() {
  set_mode = 8; LED1status=LOW; 
  Serial.println("ALL LED OFF!");
  server.send(200, "text/html", SendHTML());
}

// control mode select
void ardu_action() {
  switch (set_mode) {
    case 0: // all off
      digitalWrite(D6, LOW);
      digitalWrite(D7, LOW);
      digitalWrite(D8, LOW);
      break;
    case 1: // RED ON
      digitalWrite(D6, HIGH);
      break;
    case 2: // RED OFF
      digitalWrite(D6, LOW);
      break;
    case 3: // ORANGE ON
      digitalWrite(D7, HIGH);
      break;
    case 4: // ORANGE OFF
      digitalWrite(D7, LOW);
      break;
    case 5: // GREEN ON
      digitalWrite(D8, HIGH);
      break;
    case 6: // GREEN OFF
      digitalWrite(D8, LOW);
      break;
    case 7: // ALL LED ON
      digitalWrite(D6, HIGH);
      digitalWrite(D7, HIGH);
      digitalWrite(D8, HIGH);
      break;
    case 8: // all off
      digitalWrite(D6, LOW);
      digitalWrite(D7, LOW);
      digitalWrite(D8, LOW);
      break;
///    case 5: // MOT_SPEED
///      analogWrite(MOT1_PIN, MOT_SPEED);
///      break;   
  }
}

// output HTML web page for user
String SendHTML() {
  String html = "<!DOCTYPE html>\n";
  html += "<html>\n";
  html += "<head>\n";
  html += "<title>Wifi Control</title>\n";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  html += "<style>\n";
  html += "html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  html += "body {margin-top: 10px;} h2 {color: #444444;margin: 10px auto 10px;} h4 {color: #444444;margin-bottom: 10px;}\n";
  html += ".button {border: 5px solid green; color: white; width: 100px; margin: 5px; padding: 15px 15px; text-align: center; text-decoration: none; font-weight: bold; font-size: 20px; border-radius: 10px; box-shadow: 0 6px #999; cursor: pointer;}\n";
  html += ".button-on {background-color: #700000;}\n";
  html += ".button-off {background-color: #000070;}\n";
  html += ".button:active {background-color: #3e8e41; box-shadow: 0 5px #666; transform: translateY(4px);}\n";
  html += ".center {display: flex; justify-content: center; align-items: center; margin: 10px;}\n";
  html += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  html += "</style>\n";  
  html += "</head>\n";
  html += "<body>\n";
  html += "<div align=\"center\">\n";
  html += "<h2>Wifi Control</h2>\n";
  html += "<br>\n";
  html += "<form method=\"GET\">\n";
  html += "<input class=\"button button-on\" type=\"button\" value=\"1\" onclick=\"window.location.href='/led1on'\">\n";
  html += "<br><br>\n";
  html += "<input class=\"button button-off\" type=\"button\" value=\"2\" onclick=\"window.location.href='/led1off'\">\n";
  html += "<br><br>\n";
  html += "<input class=\"button button-on\" type=\"button\" value=\"On\" onclick=\"window.location.href='/mot1on'\">\n";
  html += "<br><br>\n";
  html += "<input class=\"button button-off\" type=\"button\" value=\"Off\" onclick=\"window.location.href='/mot1off'\">\n"; 
  html += "</form>\n";
  html += "</div>\n";
  html += "</body>\n";
  html += "</html>\n";
  return html;
}
