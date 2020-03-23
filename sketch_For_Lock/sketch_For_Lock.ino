#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <SPI.h>
#include "MFRC522.h"
#include <Servo.h> 

/* wiring the MFRC522 to ESP8266 (ESP-12)
RST     = GPIO5
SDA(SS) = GPIO4 
MOSI    = GPIO13
MISO    = GPIO12
SCK     = GPIO14
GND     = GND
3.3V    = 3.3V
*/
//Card UID: C6D1781E
//Card UID: E2904FD3
#define RST_PIN  D9  
#define SS_PIN  D10   

Servo myservo;

const char *ssid =  "MIA-1";      
const char *pass =  "12345678"; 

WiFiServer server(80);

MFRC522 mfrc522(SS_PIN, RST_PIN); 
int a;
void setup() {
  Serial.begin(115200);    
  delay(250);
  Serial.println(F("Booting...."));
  myservo.attach(D4);
  
  SPI.begin();           
  mfrc522.PCD_Init();   
  
   Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, pass);
 
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
  
  Serial.println(F("Ready!"));
  Serial.println(F("======================================================")); 
  Serial.println(F("Scan for Card and print UID:"));
}

void loop() { 
   
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

   if (request.indexOf("/LED=ON") != -1){
    myservo.write(180); 
      //delay(3000);
   }
   if (request.indexOf("/LED=OFF") != -1){
    myservo.write(0); 
      //delay(3000);
   }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=utf-8");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta http-equiv=""refresh"" content=""3"">");
  client.println("<br><br>");
  client.println("Нажмите <a href=\"/LED=ON\">здесь</a> открыть дверь!<br>");
  client.println("Нажмите <a href=\"/LED=OFF\">здесь</a> закрыть дверь и доступ!<br>");
   client.println("</html>");
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }
  
  Serial.print(F("Card UID:")); 
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size); 
  Serial.println();
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
   // Serial.print(buffer[i] < 0x10 ? " 0" : " ");
     Serial.print(buffer[i],DEC);
     a += (int)buffer[i];
      Serial.println(a);
  }
  if(a == 557){
    myservo.write(180); 
      delay(3000);
    }if(a==0){
    myservo.write(0); 
    }
     myservo.write(0);
    a=0;
}
