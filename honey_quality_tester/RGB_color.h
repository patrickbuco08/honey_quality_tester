#include "esp32-hal-gpio.h"
#define RED_PIN 16
#define GREEN_PIN 17
#define BLUE_PIN 2

//Vary this value to change the color of the RGB Led
#define RED_VALUE 200
#define GREEN_VALUE 240
#define BLUE_VALUE 255

void turn_ON_RGB() {
  analogWrite(RED_PIN, RED_VALUE);  // Set the intensity of the red color channel
  analogWrite(GREEN_PIN, GREEN_VALUE);  // Set the intensity of the green color channel
  analogWrite(BLUE_PIN, BLUE_VALUE);  // Set the intensity of the blue color channel
}

void turn_OFF_RGB() {
  analogWrite(RED_PIN, LOW);  // Set the intensity of the red color channel
  analogWrite(GREEN_PIN, LOW);  // Set the intensity of the green color channel
  analogWrite(BLUE_PIN, LOW);  // Set the intensity of the blue color channel
}

