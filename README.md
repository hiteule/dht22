# DHT22 Arduino Library

A small and powerfull Arduino library for the DTH22 Digital Humidity and Temperature Sensor. (AM2302)

## Usage

```c++
#include "DHT22.h"

DHT22 dht(7);

void setup()
{
    dht.setup();
    Serial.begin(9600);
}

void loop()
{
    dht.read();
    Serial.println(dht.getTemperature());
    Serial.println(dht.getHumidity());
    delay(3000);
}
```

## Note

The read sensor minimum interval is 2 seconds. Reading interval less than 2 seconds, may cause some trouble to communicate with the sensor and the temperature and humidity are not allowed.