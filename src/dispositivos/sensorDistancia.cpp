#define PIN_TRIG 3
#define PIN_ECHO 2


class sensorDistancia 
{
    static float getDistancia() 
    {
        digitalWrite(PIN_TRIG, LOW);
        delayMicroseconds(2);
        
        digitalWrite(PIN_TRIG, HIGH);
        delayMicroseconds(10);

        digitalWrite(PIN_TRIG, LOW);

        return pulseIn(PIN_ECHO, HIGH);
    }


    static bool estaPerto() 
    {
        return (digitalWrite(LED_BUILTIN, getDistancia() < 100)); 
    }


    
}