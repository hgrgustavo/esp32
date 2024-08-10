// https://wokwi.com/projects/405028246434409473


#include <HCSR04.h>
#include <ESP32Servo.h>
#include <Buzzer.h> // https://github.com/gmarty2000-ARDUINO/arduino-BUZZER
#include <ArduinoSound.h> // https://github.com/arduino-libraries/ArduinoSound



#define BUZZER_PIN 4

Servo servo;
HCSR04 hc(14, 27);
Buzzer buzzer(4, 5);



void setup() {
  servo.attach(2);

  Serial.begin(115200);
};

void loop() {
  while (hc.dist(1) < 0.001) {
    buzzer.begin(100);

    for (int pos = 0; pos <= 180; pos += 1) {
      servo.write(pos);
      delay(15);
    }

    buzzer.sound(C, 100); // Nota C com duração de 100ms
    buzzer.sound(E, 100);
    buzzer.sound(G, 100);

    // Pausa
    buzzer.pause(500);

    // Repetir a sequência

    for (int pos = 180; pos >= 0; pos -= 1) {
      servo.write(pos);
      delay(15);
    }
  };

  hc.dist(1);
};


