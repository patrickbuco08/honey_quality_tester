#include <Wire.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3C // OLED display I2C address, adjust if necessary
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin (not used with I2C interfaces)


Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void init_oled()
{
  display.begin(i2c_Address, true);
  display.display();
  delay(5000); // Pause for 2 seconds
  
  display.clearDisplay();
  // Display start-up message
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("Honey Quality Tester Ready");
  display.display();
  delay(2000); // Wait to confirm display shows message
}
void displayResults(float ph, float moisture, float ec, float temp, float humidity, bool isReal) {
  Serial.println("Displaying results on OLED...");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("pH: ");
  display.print(ph);
  display.setCursor(0, 10);
  display.print("Moisture: ");
  display.print(moisture);
  display.print(" %");
  display.setCursor(0, 20);
  display.print("EC: ");
  display.print(ec);
  display.print(" us/cm ");
  display.setCursor(0, 30);
  display.print("Amb.Temp: ");
  display.print(temp);
  display.print(" deg.C");
  display.setCursor(0, 40);
  display.print("Amb. Humidity:");
  display.print(humidity);
  display.print(" %");
  display.setCursor(0, 50);
  // display.print("Assmt:");
  // if(isReal == true) display.print("Pure Honey");
  // else display.print("Aldulterated ");
  display.display();
}