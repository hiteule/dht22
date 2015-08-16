#include "DHT22.h"

/**
 * Constructor
 *
 * @param uint8_t pin
 */
DHT22::DHT22(uint8_t pin)
{
    _pin = pin;
}

/**
 * Setup the pin
 */
void DHT22::setup(void)
{
    pinMode(_pin, INPUT);
    digitalWrite(_pin, HIGH);
}

/**
 * Read the sensor value and store them into local variables
 *
 * @return boolean
 */
boolean DHT22::read(void)
{
    uint8_t lastState = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;

    _data[0] = _data[1] = _data[2] = _data[3] = _data[4] = 0;

    // Send start signal
    digitalWrite(_pin, HIGH);
    delay(200);
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(2);

    noInterrupts();

    digitalWrite(_pin, HIGH);
    delayMicroseconds(40);
    pinMode(_pin, INPUT);

    // Read data
    for (i = 0; i < 85; i++) {
        counter = 0;
        while (digitalRead(_pin) == lastState) {
            counter++;
            delayMicroseconds(1);

            if (counter == 255) {
                break;
            }
        }

        lastState = digitalRead(_pin);

        if (counter == 255) {
            break;
        }

        if (i >= 4 && (i%2) == 0) {
            _data[j/8] <<= 1;

            if (counter > 6) {
                _data[j/8] |= 1;
            }

            j++;
        }
    }

    interrupts();

    // Check CRC
    if (j >= 40 && _data[4] == ((_data[0] + _data[1] + _data[2] + _data[3]) & 0xFF)) {
        return true;
    }

    return false;
}

/**
 * Get temperature previously reading
 *
 * @return float
 */
float DHT22::getTemperature()
{
    float f;

    f = _data[2] & 0x7F;
    f *= 256;
    f += _data[3];
    f /= 10;

    if (_data[2] & 0x80) {
        f *= -1;
    }

    return f;
}

/**
 * Get humidity previously readed
 *
 * @return float
 */
float DHT22::getHumidity(void)
{
    float f;

    f = _data[0];
    f *= 256;
    f += _data[1];
    f /= 10;

    return f;
}
