/*int Relay = 4;
int PIR = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode (Relay, OUTPUT);
  pinMode (PIR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(PIR);
  if (value == HIGH) {
    digitalWrite(Relay, LOW);
  }
}*/
#define pirPin 7
#define Relay 4

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(Relay, OUTPUT);
  //Serial.println("Start");
}

void loop() {
 //int pirVal = digitalRead(pirPin);

  //Если обнаружили движение
  if (digitalRead(pirPin) == HIGH) {
    digitalWrite(Relay, LOW);
    Serial.println("Motion detected");
    delay(500);
  }  else  {
    Serial.println("No motion");
    digitalWrite(Relay, HIGH);
    delay(500);
  }
}
