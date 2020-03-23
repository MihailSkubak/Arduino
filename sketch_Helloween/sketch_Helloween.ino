/*#include <Wtv020sd16p.h>
int resetPin = 2;  // The pin number of the reset pin.
int clockPin = 3;  // The pin number of the clock pin.
int dataPin = 4;  // The pin number of the data pin.
int busyPin = 5;  // The pin number of the busy pin.

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);
 
void setup() {
  Serial.begin(115200);
  //Initializes the module.
  wtv020sd16p.reset();
}
 
void loop() {
  if(digitalRead(busyPin)==0){
     Serial.println("Play");
    wtv020sd16p.asyncPlayVoice(0);
  }
  delay(20000); 
}*/ 

int trigPin = 5;    //Триггер – зеленый проводник

int echoPin = 4;
long duration, cm, inches;


void setup() {
pinMode(6, OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);

delayMicroseconds(5);

digitalWrite(trigPin, HIGH);

delayMicroseconds(10);

digitalWrite(trigPin, LOW);

pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);

// преобразование времени в расстояние

cm = (duration/2) / 29.1;

inches = (duration/2) / 74;
if(cm<8){

analogWrite(9,225);
analogWrite(10,0);
analogWrite(11,0);
  
tone(6, 392, 350);
delay(350);
tone(6, 392, 350);
delay(350);
tone(6, 392, 350);
delay(350);
tone(6, 311, 250);
delay(250);
tone(6, 466, 100);
delay(100);
tone(6, 392, 350);
delay(350);
tone(6, 311, 250);
delay(250);
tone(6, 466, 100);
delay(100);
tone(6, 392, 700);
delay(700);

tone(6, 587, 350);
delay(350);
tone(6, 587, 350);
delay(350);
tone(6, 587, 350);
delay(350);
tone(6, 622, 250);
delay(250);
tone(6, 466, 100);
delay(100);
tone(6, 369, 350);
delay(350);
tone(6, 311, 250);
delay(250);
tone(6, 466, 100);
delay(100);
tone(6, 392, 700);
delay(700);

tone(6, 784, 350);
delay(350);
tone(6, 392, 250);
delay(250);
tone(6, 392, 100);
delay(100);
tone(6, 784, 350);
delay(350);
tone(6, 739, 250);
delay(250);
tone(6, 698, 100);
delay(100);
tone(6, 659, 100);
delay(100);
tone(6, 622, 100);
delay(100);
tone(6, 659, 450);
delay(450);

tone(6, 415, 150);
delay(150);
tone(6, 554, 350);
delay(350);
tone(6, 523, 250);
delay(250);
tone(6, 493, 100);
delay(100);
tone(6, 466, 100);
delay(100);
tone(6, 440, 100);
delay(100);
tone(6, 466, 450);
delay(450);

tone(6, 311, 150);
delay(150);
tone(6, 369, 350);
delay(350);
tone(6, 311, 250);
delay(250);
tone(6, 466, 100);
delay(100);
tone(6, 392, 750);
delay(750);
analogWrite(9,0);
delay(3000);
}
} 
