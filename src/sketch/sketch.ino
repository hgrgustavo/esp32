#include <Buzzer.h>

const int trigPin = 31;
const int echoPin = 33;
const int ioPin = 35;

long duration;
int distance;
Buzzer buzzer(ioPin);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ioPin, INPUT);
  Serial.begin(300);
  buzzer.begin(300);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // triggering buzzer
  if (distance < 41) {
    buzzer.distortion(NOTE_C3, NOTE_C5);
    buzzer.distortion(NOTE_C5, NOTE_C3);
    buzzer.end(1000);   
  }

  Serial.println(distance);
  
  delay(1000);
}
