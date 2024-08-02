#include "NHCSR04.h"

uint16_t SR04::microsecondsTimeoutOffset = 3184;

SR04::SR04(byte trigger, byte echo, uint16_t maxCentimeters)
    :maxCentimeters(maxCentimeters), sensorFactor(1.0/58.0), cmOffset(1.5), trigger(trigger), echo(echo)
{
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
}

uint64_t SR04::ping()
{
    digitalWrite(trigger, HIGH);
    delayMicroseconds(SENSOR_TRIGGER_TIME);
    digitalWrite(trigger, LOW);
    pulseTime = pulseIn(echo, HIGH, (maxCentimeters / sensorFactor) + microsecondsTimeoutOffset);
    return pulseTime;
}

double SR04::centimeters(bool doPing)
{
    if (doPing)
        ping();
    if (pulseTime == 0)
        return maxCentimeters;
    return (pulseTime * sensorFactor) + cmOffset;
}

double SR04::inches(bool doPing)
{
    return centimeters(doPing) * 2.54;
}