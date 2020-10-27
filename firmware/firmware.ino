

#include<Servo.h>

const int myMotor = 9;
const int TrigPin = 2;
const int EchoPin = 3;
const int LedPin = 12;
int speed_0;
float distance = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(myMotor, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void Distance_test() 
{
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  float Fdistance = pulseIn(EchoPin, HIGH);
  Fdistance= Fdistance/58;
  Distance = Fdistance;
}  

void loop() {
   if (distance < 10 & diatance > 0) {
   speed_0 = 175;
   digitalWrite(ledPin, HIGH);  
   }
   else if (distance >= 10) {
   speed_0 = 0;
   digitalWrite(ledPin, LOW);  
   }

}
