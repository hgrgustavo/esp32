#include<NHCSR04.h>
#include<servoMotor.h>

#define PIN_TRIG 2
#define PIN_ECHO 3

class sensorDistancia {
    sensorDistancia();
    static float getDistancia() {
        digitalWrite(PIN_TRIG, HIGH);
        delayMicroseconds(2);
        digitalWrite(PIN_TRIG, LOW);
        delayMicroseconds(10);
        return pulseIn(PIN_ECHO, HIGH) / 58);
    }
    static bool ping(bool b) {
        SR04 sensor(PIN_TRIG, PIN_ECHO);
        return sensor.centimeters(true);
    }
}