#include<Servo.h>         
#include<sensorDistancia.h>

class servoMotor {
    servoMotor();
    sensorDistancia();
    static void anexar(int pin, int pulse_min, int pulse_max) {
        if(!servo.attached()) {
            servo.attach(pin, pulse_min, pulse_max);
        }
    }
    static Servo estaPerto() {
        // read hcsr04 proximity signal >> trigger servoMotor. 
        switch(sensorDistancia.ping()) {
            case 100:
                Servo::write(80);
                break;
            case 150:
                Servo::write(60);
                break;
            case 200:
                Servo::write(35);
                break;
            default:
                SensorDistancia::ping(false);
                break;
        }
    }
}