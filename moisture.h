
#define MOISTURE_PIN 39




void init_moisture()
{
  pinMode(MOISTURE_PIN, INPUT);
}

float read_moisture()
{
  int moisture = analogRead(MOISTURE_PIN);
  return map(moisture, 4095, 0, 0, 100);
}

