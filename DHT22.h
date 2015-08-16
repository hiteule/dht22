#ifndef DHT22_H
#define DHT22_H

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class DHT22 {
    private:
        uint8_t _data[6];
        uint8_t _pin;

    public:
        DHT22(uint8_t pin);
        void setup(void);
        boolean read(void);
        float getTemperature();
        float getHumidity(void);
};

#endif
