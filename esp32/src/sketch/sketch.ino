#include <HCSR04.h>
#include <Buzzer.h>


const int trigPin = 31;
const int echoPin = 33;
const int ioPin = 35;
Buzzer buzzer(ioPin);
UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);



void setup() {
  Serial.begin(300);
}


void loop() {
  float distance = distanceSensor.measureDistanceCm();

  if (distance <= 20) {
    buzzer.begin(0);
    buzzer.sound(NOTE_D7, 300);
    buzzer.sound(NOTE_D7, 300);
    buzzer.end(20);
  }

  Serial.println(distance);

  delay(500);
}
