#ifndef NHCSR04
#define NHCSR04

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define MICROS_OFFSET 3198
#define SENSOR_TRIGGER_TIME 10

class SR04
{
public:
    static uint16_t microsecondsTimeoutOffset;

    /// @brief Class for using HC-SR04 modules.
    /// @param trigger trigger pin
    /// @param echo echo pin
    /// @param maxCentimeters maximum distance (cm)
    SR04(byte trigger, byte echo, uint16_t maxCentimeters = 100);

    /// @brief Sends a ping and saves the time it took for echo.
    /// @return echo time
    uint64_t ping();

    /// @brief Converts ping time to centimeters
    /// @param doPing Send a ping and refresh echo time.
    /// @return `double` distance (cm)
    double centimeters(bool doPing = true);

    /// @brief Converts ping time to inches.
    /// @param doPing Send a ping and refresh echo time.
    /// @return `double` distance (in)
    double inches(bool doPing = true);

    uint16_t maxCentimeters;
    float sensorFactor;
    float cmOffset;
private:
    const byte trigger, echo;
    uint64_t pulseTime;
};

#endif