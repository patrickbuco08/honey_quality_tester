 #include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void init_dht22()
{
  dht.begin();
}

float read_humidity()
{
  return dht.readHumidity();
}

float read_temperature()
{
  return dht.readTemperature();
}

