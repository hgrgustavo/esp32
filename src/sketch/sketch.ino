#include <HCSR04.h>
#include <Buzzer.h>

const int trigPin = 31;
const int echoPin = 33;
const int ioPin = 35;

long duration;
int distance;
Buzzer buzzer(ioPin);
UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ioPin, INPUT);
  
  Serial.begin(300);
  buzzer.begin(300);
}

void loop() {
  if (distanceSensor.measureDistanceCm() < 35) {
    buzzer.sound(NOTE_D7, 300);
    buzzer.sound(NOTE_D7, 300);
    buzzer.end(20);
  }

  int distance = distanceSensor.measureDistanceCm();
  Serial.println(distance);
  
  delay(500);
}
