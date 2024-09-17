#include <HCSR04.h>
#include <ESP32Servo.h>
#include <Buzzer.h>



Servo servo;
HCSR04 hc(14, 27);
Buzzer buzzer(4);



void setup() {
  servo.attach(2);
  Serial.begin(115200);
};

void loop() {
  while (hc.dist(1) < 0.001) {
    for (int pos = 0; pos <= 180; pos += 1) {
      buzzer.begin(0);
      buzzer.sound(NOTE_C5, NOTE_C5);
      buzzer.sound(NOTE_C3, NOTE_C3);
      buzzer.end(1000);

      servo.write(pos);

      delay(15);
    }

    for (int pos = 180; pos >= 0; pos -= 1) {
      buzzer.begin(0);
      buzzer.sound(NOTE_C5, NOTE_C5);
      buzzer.sound(NOTE_C3, NOTE_C3);
      buzzer.end(1000);

      servo.write(pos);

      delay(15);
    }
  };

  hc.dist(1);
};

