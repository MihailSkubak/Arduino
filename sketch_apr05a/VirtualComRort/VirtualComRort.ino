/*#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>   //подгружаем библиотеку mDNS
const char* ssid = "HappyWifi";
const char* password = "happywifi1998";
ESP8266WebServer server(80);
MDNSResponder mdns;        //назначаем экземпляр класса ESP8266mDNS
const int led = 13;
void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}
void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  // ожидание соединения
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //назначаем символьное имя mDNS нашему серверу опираясь на его динамически полученный IP
 if (MDNS.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");  //активируем сервис MDNS
  MDNS.addService("http", "tcp", 80);
}
void loop(void){
  server.handleClient();
  if(Serial.available()){
    int vs = (int)Serial.read()-80;
    if(vs==1){
       Serial.println("Hello VS!");
  }
   else{
    Serial.println("Goodbye VS!");
   }
  }
}*/

#include <ESP8266WiFi.h>

#include <Stepper_28BYJ.h>
// изменить количество шагов для вашего мотора
#define STEPS 4078
#define PIN_1 0//D8
#define PIN_2 2//D9
#define PIN_3 15//D10
#define PIN_4 13//D11

Stepper_28BYJ stepper(STEPS, PIN_1, PIN_2, PIN_3, PIN_4);

#define PIN_SWITCH_1 4//D4
#define PIN_SWITCH_2 12//D6
#define PIN_SWITCH_3 16//D7
#define PIN_SWITCH_4 5//D3

const char* ssid = "HappyWifi";
const char* password = "happywifi1998";
 
int ledPin = D5;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  stepper.setSpeed(13);
 
  pinMode (PIN_SWITCH_1, OUTPUT);//INPUT
  pinMode (PIN_SWITCH_2, OUTPUT);//OUTPUT
  pinMode (PIN_SWITCH_3, OUTPUT);
  pinMode (PIN_SWITCH_4, OUTPUT);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Match the request

   
  int value = LOW;
  if (request.indexOf("/LED=ON1") != -1) {
    digitalWrite(ledPin, HIGH);
     digitalWrite(PIN_SWITCH_1, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF1") != -1){
    digitalWrite(ledPin, LOW);
    digitalWrite(PIN_SWITCH_1,LOW);
    value = LOW;
  }

  
   if (request.indexOf("/LED=ON2") != -1) {
    digitalWrite(ledPin, HIGH);
     digitalWrite(PIN_SWITCH_2, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF2") != -1){
    digitalWrite(ledPin, LOW);
    digitalWrite(PIN_SWITCH_2,LOW);
    value = LOW;
  }

  
   if (request.indexOf("/LED=ON3") != -1) {
    digitalWrite(ledPin, HIGH);
     digitalWrite(PIN_SWITCH_3, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF3") != -1){
    digitalWrite(ledPin, LOW);
    digitalWrite(PIN_SWITCH_3,LOW);
    value = LOW;
  }

  if (request.indexOf("/LED=ON5") != -1) {
    digitalWrite(ledPin, HIGH);
     digitalWrite(PIN_SWITCH_4, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF5") != -1){
    digitalWrite(ledPin, LOW);
    digitalWrite(PIN_SWITCH_4,LOW);
    value = LOW;
  }

  if (request.indexOf("/LED=ON4") != -1) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(PIN_SWITCH_1, HIGH);
    digitalWrite(PIN_SWITCH_2, HIGH);
    digitalWrite(PIN_SWITCH_3, HIGH);
    digitalWrite(PIN_SWITCH_4, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF4") != -1){
   digitalWrite(ledPin, LOW);
   digitalWrite(PIN_SWITCH_1,LOW);
   digitalWrite(PIN_SWITCH_2,LOW);
   digitalWrite(PIN_SWITCH_3,LOW);
   digitalWrite(PIN_SWITCH_4,LOW);
    value = LOW;
  }
  if (request.indexOf("/LED=ON6") != -1) {
    Serial.println("Move right");
   stepper.step(2200);//2500
   delay(1000);
   stepper.step(2200);//2500
   delay(1000);
   stepper.step(2200);//2500
   delay(1000);
   Serial.println("Finish right");
  } 
  if (request.indexOf("/LED=OFF6") != -1){
   Serial.println("Move left");
   stepper.step(-2200);//2500
   delay(1000);
   stepper.step(-2200);//2500
   delay(1000);
   stepper.step(-2200);//2500
   delay(1000);
   Serial.println("Finish left");
  }
 
  // Return the response
   client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=utf-8");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
        
  client.print("Состояние: ");
 
  if(value == HIGH) {
    client.print("Отключено!");  
  } else {
    client.print("Включено!");
  }
  client.println("<br><br>");
  client.println("Нажмите <a href=\"/LED=ON1\">здесь</a> для выключения света!<br>");
  client.println("Нажмите <a href=\"/LED=OFF1\">здесь</a> для включения света!<br>");
  client.println("Нажмите <a href=\"/LED=ON2\">здесь</a> для выключения лампы!<br>");
  client.println("Нажмите <a href=\"/LED=OFF2\">здесь</a> для включения лампы!<br>");
  client.println("Нажмите <a href=\"/LED=ON3\">здесь</a> для выключения света в комнате!<br>");
  client.println("Нажмите <a href=\"/LED=OFF3\">здесь</a> для включения света в комнате!<br>");
  client.println("Нажмите <a href=\"/LED=ON5\">здесь</a> для выключения техники!<br>");
  client.println("Нажмите <a href=\"/LED=OFF5\">здесь</a> для включения техники!<br>");
  client.println("Нажмите <a href=\"/LED=ON4\">здесь</a> для отключения всего!<br>");
  client.println("Нажмите <a href=\"/LED=OFF4\">здесь</a> для включения всего!<br>");
  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
