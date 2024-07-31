// MySensor.h
#ifndef MySensor_h
#define MySensor_h

class MySensor {
public:
  MySensor(int pin);
  int readValue();

private:
  int _pin;
};

#endif

// MySensor.cpp
#include "MySensor.h"

MySensor::MySensor(int pin) : _pin(pin) {}

int MySensor::readValue() {
  return analogRead(_pin);
}

// main.cpp
#include "MySensor.h"

MySensor sensor(A0);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = sensor.readValue();
  Serial.println(value);
  delay(100);
}
