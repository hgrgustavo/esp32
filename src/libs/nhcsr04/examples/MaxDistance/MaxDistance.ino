#include <NHCSR04.h>

int maxCentimeters = 500; //Default is 100cm. This is to prevent too long ping

int baudrate = 9600;

int triggerPin = 2;
int echoPin = 3;

SR04 sensor(triggerPin, echoPin, maxCentimeters);

double cm;

void setup()
{
    Serial.begin(baudrate);
}

void loop()
{
    cm = sensor.centimeters();
    Serial.print("cm: ");
    Serial.println(cm);
}