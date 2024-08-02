// https://wokwi.com/projects/405028246434409473

#include <HCSR04.h>
#include <ESP32Servo.h>

Servo myservo;
HCSR04 hc(14, 27);

void setup() {
  myservo.attach(2);

  Serial.begin(115200);
};

void loop() {
  while (hc.dist(1) < 0.001) {
    for (int pos = 0; pos <= 180; pos += 1) { 
      myservo.write(pos);
      delay(15);                  
    }                   

    for (int pos = 180; pos >= 0; pos -= 1) { 
      myservo.write(pos);
      delay(15);                                     
    }
    hc.dist(1);
  };
};