#include <E:\esp32\src\libs\servo\src\Servo.h>


class servoMotor {
    Servo servo = new Servo();
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