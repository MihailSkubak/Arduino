#include <ESP8266WiFi.h>

#define PIN_SWITCH_1 D6
#define PIN_SWITCH_2 D5

const char* ssid = "Redmi7";
const char* password = "welcometoredmi";
 
int ledPin = D5;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode (PIN_SWITCH_1, INPUT);
  pinMode (PIN_SWITCH_2, OUTPUT);
  pinMode (2, OUTPUT);
  digitalWrite(2,HIGH);
  
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

   digitalWrite(2,LOW);
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
 /* while(!client.available()){
    delay(1);
  }*/
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (digitalRead(PIN_SWITCH_1) == HIGH || request.indexOf("/LED=ON") != -1) {
    digitalWrite(PIN_SWITCH_2, HIGH);
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (digitalRead(PIN_SWITCH_1) == HIGH && request.indexOf("/LED=OFF") != -1) {
    digitalWrite(PIN_SWITCH_2, HIGH);
    digitalWrite(ledPin, HIGH);
    value = HIGH;
    }
     if (digitalRead(PIN_SWITCH_1) == LOW && request.indexOf("/LED=OFF") != -1) {
    digitalWrite(PIN_SWITCH_2, LOW);
    digitalWrite(ledPin, LOW);
    value = LOW;
    }
  /*if (request.indexOf("/LED=ON") != -1 ) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }*/
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=utf-8");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta http-equiv=""refresh"" content=""5"">");
        
  client.print("Состояние: ");
 
  if(value == HIGH) {
    client.print("Включено!");  
  } else {
    client.print("Отключено!");
  }
  client.println("<br><br>");
  client.println("Нажмите <a href=\"/LED=ON\">здесь</a> для включения!<br>");
  client.println("Нажмите <a href=\"/LED=OFF\">здесь</a> для выключения!<br>");
  client.println("</html>");
 
  //delay(1);
  //Serial.println("Client disconnected");
  //Serial.println("");
 
}
