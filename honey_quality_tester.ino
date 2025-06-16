#include <SD.h>
#include <SPI.h>
#include <WiFi.h>
#include <WebServer.h>

#include "ph.h"
#include "as7341.h"
#include "assesHoney.h"
#include "oled.h"
#include "EC.h"
#include "dht22.h"
#include "moisture.h"
#include "honey_web_gui.h"

//Wifi Name for your ESP32
const char* ssid = "ESP32-Honey Quality";
const char* password = "12345678";
WebServer server(80);

// Define your pins and peripherals
#define SD_CS_PIN 5  // SD card CS pin

File logFile;  // File object for SD card logging

// Variables for data acquisition
float phValue = 0;
float ECValue = 0;
float moistureValue = 0;
float tempValue = 0;
float humidityValue = 0;
float violet_ch1_value = 0;
float violet_ch2_value = 0;
float blue_value = 0;
float green_ch4_value = 0;
float green_ch5_value = 0;
float orange_value = 0;
float red_RedCh7_value = 0;
float red_ch8_value = 0;
float clear_value = 0;
float nir_value = 0;

int sampleCount = 0;
bool analyzing = false;
String note = "No SD Card detected";


bool analysisInProgress = false;
unsigned long analysisStartTime = 0;
// Function Prototypes


void setup() {
  Serial.begin(115200);
  // Initialize Wi-Fi
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  init_dht22();
  // Define page routes
  // Serve the main HTML page
  server.on("/", handleRoot);
  server.on("/startAnalysis", HTTP_GET, handleStartAnalysis);
  server.on("/latestLog", handleLatestLog);  // Serve the JSON data from the single file

  server.on("/calibratePH4", HTTP_GET, handleCalibratePH4);
  server.on("/calibratePH9", HTTP_GET, handleCalibratePH9);
  server.on("/calibrateEC1", HTTP_GET, handleCalibrateEC1413);
  server.on("/calibrateEC2", HTTP_GET, handleCalibrateEC1288);
  server.on("/calibrateAS7341", HTTP_GET, handleCalibrateAS7341);

  server.begin();
  Serial.println("HTTP server started");


  init_7341();
  // Initialize OLED display
  init_oled();

  checkSDCard();
  // Initialize SD card
  // if (!SD.begin(SD_CS_PIN)) {
  //   Serial.println("SD card initialization failed!");
  //   //while (1);
  // }
}

void loop() {
  server.handleClient();

  pH9Voltage = calibrationValue_inSD_pH9();
  pH4Voltage = calibrationValue_inSD_pH4();
  EC1_analogValue = calibrationValue_inSD_EC1413();
  EC2_analogValue = calibrationValue_inSD_EC1288();
}


// Function to start analysis
//void startAnalysis() {
void handleStartAnalysis() {
  //checkSDCard();
  turn_ON_RGB();
  // Open the SD file to read calibration data (I0)
  File dataFile = SD.open("/calibration_as7341.txt", FILE_READ);
  if (!dataFile) {
    Serial.println("Failed to open calibration_as7341.txt for reading.");
    return;
  }

  // Dynamically allocate memory for calibration intensities
  float* I0 = new float[10];
  int channelIndex = 0;

  // Read the I0 values from the SD file
  while (dataFile.available() && channelIndex < 10) {
    String value = dataFile.readStringUntil('\n');  // Read each value as a string
    I0[channelIndex] = value.toFloat();             // Convert to float
    //Serial.print("Calibration AS: ");
    //Serial.println(I0[channelIndex]);
    channelIndex++;
  }
  dataFile.close();

  // Check if we successfully read all 10 channels
  if (channelIndex != 10) {
    Serial.println("Error: Not enough calibration data in file.");
    delete[] I0;  // Free allocated memory
    return;
  }
  // Display message for debugging start of analysis
  Serial.println("Starting sample analysis...");
  Serial.println("After starting sample analysis...");
  // display.clearDisplay();
  // display.setCursor(0, 0);
  // display.print("Analyzing the sample...");
  // display.display();

  Serial.println("Analyzing the sample...");

  int readingsCount = 0;

  float phTotal = 0;
  float ECTotal = 0;
  float moistureTotal = 0;
  float tempTotal = 0;
  float humidityTotal = 0;
  float violetCh1Total = 0;
  float violetCh2Total = 0;
  float blueTotal = 0;
  float greenCh4Total = 0;
  float greenCh5Total = 0;
  float orangeTotal = 0;
  float redRedCh7Total = 0;
  float redCh8Total = 0;
  float clearTotal = 0;
  float nirTotal = 0;

  // Absorbance variables for each channel
  float absorbanceVioletCh1;  // 415nm (F1)
  float absorbanceVioletCh2;  // 445nm (F2)
  float absorbanceBlue;       // 480nm (F3)
  float absorbanceGreenCh4;   // 515nm (F4)
  float absorbanceGreenCh5;   // 555nm (F5)
  float absorbanceOrange;     // 590nm (F6)
  float absorbanceRedCh7;     // 630nm (F7)
  float absorbanceRedCh8;     // 680nm (F8)
  float absorbanceClear;      // CLEAR channel
  float absorbanceNIR;        // NIR channel

  unsigned long startTime = millis();
  while (millis() - startTime < 10000) {  // 10-second window

    phTotal += readPHvalue();
    ECTotal += readECvalue();
    moistureTotal += read_moisture();
    tempTotal += read_temperature();
    humidityTotal += read_humidity();

    readChannel_as7341();
    violetCh1Total += as7341.getChannel(AS7341_CHANNEL_415nm_F1);
    violetCh2Total += as7341.getChannel(AS7341_CHANNEL_445nm_F2);
    blueTotal += as7341.getChannel(AS7341_CHANNEL_480nm_F3);
    greenCh4Total += as7341.getChannel(AS7341_CHANNEL_515nm_F4);
    greenCh5Total += as7341.getChannel(AS7341_CHANNEL_555nm_F5);
    orangeTotal += as7341.getChannel(AS7341_CHANNEL_590nm_F6);
    redRedCh7Total += as7341.getChannel(AS7341_CHANNEL_630nm_F7);
    redCh8Total += as7341.getChannel(AS7341_CHANNEL_680nm_F8);
    clearTotal += as7341.getChannel(AS7341_CHANNEL_CLEAR);
    nirTotal += as7341.getChannel(AS7341_CHANNEL_NIR);

    readingsCount++;
    delay(100);  // Adjust as needed
  }
  // Calculate averages
  phValue = phTotal / readingsCount;
  ECValue = ECTotal / readingsCount;
  moistureValue = calculateMoisture(ECValue);
  tempValue = tempTotal / readingsCount;
  humidityValue = humidityTotal / readingsCount;
  violet_ch1_value = violetCh1Total / readingsCount;
  violet_ch2_value = violetCh2Total / readingsCount;
  blue_value = blueTotal / readingsCount;
  green_ch4_value = greenCh4Total / readingsCount;
  green_ch5_value = greenCh5Total / readingsCount;
  orange_value = orangeTotal / readingsCount;
  red_RedCh7_value = redRedCh7Total / readingsCount;
  red_ch8_value = redCh8Total / readingsCount;
  clear_value = clearTotal / readingsCount;
  nir_value = nirTotal / readingsCount;

  absorbanceVioletCh1 = (I0[0] > 0 && violet_ch1_value > 0)
                          ? log10(I0[0] / violet_ch1_value)
                          : -1;
  absorbanceVioletCh2 = (I0[1] > 0 && violet_ch2_value > 0)
                          ? log10(I0[1] / violet_ch2_value)
                          : -1;
  absorbanceBlue = (I0[2] > 0 && blue_value > 0)
                     ? log10(I0[2] / blue_value)
                     : -1;
  absorbanceGreenCh4 = (I0[3] > 0 && green_ch4_value > 0)
                         ? log10(I0[3] / green_ch4_value)
                         : -1;
  absorbanceGreenCh5 = (I0[4] > 0 && green_ch5_value > 0)
                         ? log10(I0[4] / green_ch5_value)
                         : -1;
  absorbanceOrange = (I0[5] > 0 && orange_value > 0)
                       ? log10(I0[5] / orange_value)
                       : -1;
  absorbanceRedCh7 = (I0[6] > 0 && red_RedCh7_value > 0)
                       ? log10(I0[6] / red_RedCh7_value)
                       : -1;
  absorbanceRedCh8 = (I0[7] > 0 && red_ch8_value > 0)
                       ? log10(I0[7] / red_ch8_value)
                       : -1;
  absorbanceClear = (I0[8] > 0 && clear_value > 0)
                      ? log10(I0[8] / clear_value)
                      : -1;
  absorbanceNIR = (I0[9] > 0 && nir_value > 0)
                    ? log10(I0[9] / nir_value)
                    : -1;

  bool isReal = assessHoneyQuality(phValue, ECValue, moistureValue, absorbanceVioletCh1, absorbanceVioletCh2, absorbanceBlue, absorbanceGreenCh4, absorbanceGreenCh5, absorbanceOrange, absorbanceRedCh7, absorbanceRedCh8, absorbanceClear, absorbanceNIR);
  // Display results on OLED
  displayResults(phValue, moistureValue, ECValue, tempValue, humidityValue, isReal);

  // Log results to SD card
  logResults(phValue, ECValue, moistureValue, tempValue, humidityValue, absorbanceVioletCh1, absorbanceVioletCh2, absorbanceBlue, absorbanceGreenCh4, absorbanceGreenCh5, absorbanceOrange, absorbanceRedCh7, absorbanceRedCh8, absorbanceClear, absorbanceNIR, isReal);

  // Send JSON response back to the client
  String response = "{\"message\": \"Analysis completed.\"}";
  server.send(200, "application/json", response);
  delete[] I0;

  Serial.println("done analysis...");

  turn_OFF_RGB();
}


void handleCalibratePH4() {
  checkSDCard();

  // Update OLED to show calibration has started
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Calibrating pH Sensor");
  display.setCursor(0, 10);
  display.print("Using 4.01 buffer...");
  display.display();

  // Accumulate sensor readings for averaging
  float sumVoltage = 0.0;
  int numReadings = 0;
  unsigned long startTime = millis();

  while (millis() - startTime < 10000) {
    float voltage = pH_calibrationValue();
    sumVoltage += voltage;
    numReadings++;
    delay(500);
  }

  if (numReadings == 0) {
    server.send(500, "application/json", "{\"error\": \"No readings taken.\"}");
    return;
  }

  float avgVoltage = sumVoltage / numReadings;

  Serial.print("Average calibration voltage for pH 4.01: ");
  Serial.println(avgVoltage);

  bool success = false;
  File file = SD.open("/calibration_pH4.txt", FILE_WRITE);
  if (file) {
    file.print("PH4_voltage=");
    file.println(avgVoltage);
    file.close();
    success = true;
  }

  // OLED display update
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Done pH Calibration");
  display.setCursor(0, 10);
  display.print("Calibrated to 4.01 buffer");
  display.display();

  // Send final server response
  String response;
  int statusCode;

  if (success) {
    response = "{\"message\": \"pH calibration to 4.01 completed successfully. Saved average voltage: " + String(avgVoltage, 3) + " V\"}";
    statusCode = 200;
  } else {
    response = "{\"error\": \"Failed to save pH calibration.\"}";
    statusCode = 500;
  }

  server.send(statusCode, "application/json", response);
}


void handleCalibratePH9() {
  checkSDCard();

  // Show calibration start on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Calibrating pH Sensor");
  display.setCursor(0, 10);
  display.print("Using 9.18 buffer...");
  display.display();

  // Accumulate voltage readings
  float sumVoltage = 0.0;
  int numReadings = 0;
  unsigned long startTime = millis();

  while (millis() - startTime < 10000) {
    float voltage = pH_calibrationValue();
    sumVoltage += voltage;
    numReadings++;
    delay(500);
  }

  // Check if readings were taken
  if (numReadings == 0) {
    server.send(500, "application/json", "{\"error\": \"No readings taken.\"}");
    return;
  }

  float avgVoltage = sumVoltage / numReadings;

  Serial.print("Average calibration voltage for pH 9.18: ");
  Serial.println(avgVoltage);

  // Save to SD
  bool success = false;
  File file = SD.open("/calibration_pH9.txt", FILE_WRITE);
  if (file) {
    file.print("PH9_voltage=");
    file.println(avgVoltage);
    file.close();
    success = true;
  }

  // Update OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Done pH Calibration");
  display.setCursor(0, 10);
  display.print("Calibrated to 9.18 buffer");
  display.display();

  // Prepare and send response
  String response;
  int statusCode;

  if (success) {
    response = "{\"message\": \"pH calibration to 9.18 completed successfully. Saved average voltage: " + String(avgVoltage, 3) + " V\"}";
    statusCode = 200;
  } else {
    response = "{\"error\": \"Failed to save pH calibration.\"}";
    statusCode = 500;
  }

  server.send(statusCode, "application/json", response);
}


void handleCalibrateEC1413() {
  checkSDCard();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Calibrating EC Sensor using 1413us/cm buffer");
  display.display();

  String response;
  int statusCode;
  float sumAnalogRead = 0.0;
  int numReadings = 0;
  unsigned long startTime = millis();

  while (millis() - startTime < 10000) {
    float analogValue = EC_calibrationValue();
    sumAnalogRead += analogValue;
    numReadings++;
    delay(500);
  }

  if (numReadings == 0) {
    server.send(500, "application/json", "{\"error\": \"No readings taken.\"}");
    return;
  }

  float avgAnalogRead = sumAnalogRead / numReadings;
  Serial.print("Average calibration analog Value EC1413: ");
  Serial.println(avgAnalogRead);

  bool success = false;
  File file = SD.open("/calibration_EC1413.txt", FILE_WRITE);
  if (file) {
    file.print("EC1413=");
    file.println(avgAnalogRead);
    file.close();
    Serial.println("Calibration value saved to microSD.");
    success = true;
  } else {
    Serial.println("Failed to open file for writing.");
  }

  // OLED update
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Done EC Calibration.");
  display.display();

  // Send result after everything is done
  if (success) {
    response = "{\"message\": \"EC calibration to 1413 µS/cm completed successfully. Saved average analog value: " + String(avgAnalogRead, 2) + "\"}";
    statusCode = 200;
  } else {
    response = "{\"error\": \"Failed to save calibration.\"}";
    statusCode = 500;
  }

  server.send(statusCode, "application/json", response);
}


void handleCalibrateEC1288() {
  checkSDCard();

  // Show calibration start on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Calibrating EC Sensor");
  display.setCursor(0, 10);
  display.print("Using 1288us/cm buffer...");
  display.display();

  // Accumulate sensor readings
  float sumAnalogRead = 0.0;
  int numReadings = 0;
  unsigned long startTime = millis();

  while (millis() - startTime < 10000) {
    float analogValue = EC_calibrationValue(); // renamed for clarity
    sumAnalogRead += analogValue;
    numReadings++;
    delay(500);
  }

  if (numReadings == 0) {
    server.send(500, "application/json", "{\"error\": \"No readings taken.\"}");
    return;
  }

  float avgAnalogRead = sumAnalogRead / numReadings;

  Serial.print("Average calibration analog value for EC1288: ");
  Serial.println(avgAnalogRead);

  // Save to SD
  bool success = false;
  File file = SD.open("/calibration_EC1288.txt", FILE_WRITE);
  if (file) {
    file.print("EC1288=");
    file.println(avgAnalogRead);
    file.close();
    success = true;
  }

  // Update OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Done EC Calibration");
  display.setCursor(0, 10);
  display.print("Calibrated to 1288us/cm");
  display.display();

  // Prepare and send JSON response
  String response;
  int statusCode;

  if (success) {
    response = "{\"message\": \"EC calibration to 1288 µS/cm completed successfully. Saved average analog value: " + String(avgAnalogRead, 2) + "\"}";
    statusCode = 200;
  } else {
    response = "{\"error\": \"Failed to save EC calibration.\"}";
    statusCode = 500;
  }

  server.send(statusCode, "application/json", response);
}


void handleCalibrateAS7341() {
  turn_ON_RGB();
  checkSDCard();

  // Show calibration message on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Calibrating AS7341");
  display.setCursor(0, 10);
  display.print("Collecting data...");
  display.display();

  // Initialize variables
  unsigned long startTime = millis();
  float totalIntensity[10] = {0};
  float intensities[10] = {0};
  int count = 0;

  // Accumulate readings over 10 seconds
  while (millis() - startTime < 10000) {
    if (as7341.readAllChannels()) {
      totalIntensity[0] += as7341.getChannel(AS7341_CHANNEL_415nm_F1);
      totalIntensity[1] += as7341.getChannel(AS7341_CHANNEL_445nm_F2);
      totalIntensity[2] += as7341.getChannel(AS7341_CHANNEL_480nm_F3);
      totalIntensity[3] += as7341.getChannel(AS7341_CHANNEL_515nm_F4);
      totalIntensity[4] += as7341.getChannel(AS7341_CHANNEL_555nm_F5);
      totalIntensity[5] += as7341.getChannel(AS7341_CHANNEL_590nm_F6);
      totalIntensity[6] += as7341.getChannel(AS7341_CHANNEL_630nm_F7);
      totalIntensity[7] += as7341.getChannel(AS7341_CHANNEL_680nm_F8);
      totalIntensity[8] += as7341.getChannel(AS7341_CHANNEL_CLEAR);
      totalIntensity[9] += as7341.getChannel(AS7341_CHANNEL_NIR);
      count++;
    }
    delay(100);
  }

  // Compute averages
  for (int i = 0; i < 10; i++) {
    intensities[i] = (count > 0) ? totalIntensity[i] / count : 0;
  }

  // Save to SD
  bool success = false;
  File file = SD.open("/calibration_as7341.txt", FILE_WRITE);
  if (file) {
    for (int i = 0; i < 10; i++) {
      file.println(intensities[i]);
    }
    file.close();
    success = true;
  }

  // Update OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Done AS7341 Calibration.");
  display.display();

  turn_OFF_RGB();

  // Send JSON response
  String response;
  int statusCode;

  if (success) {
    response = "{\"message\": \"AS7341 calibration complete.\", \"samples\": " + String(count) + "}";
    statusCode = 200;
  } else {
    response = "{\"error\": \"Failed to save AS7341 calibration.\"}";
    statusCode = 500;
  }

  server.send(statusCode, "application/json", response);
}


void logResults(float ph, float ec, float moisture, float temperature, float humidity, float violetCh1, float violetCh2, float blue, float greenCh4, float greenCh5, float orange, float redCh7, float redCh8, float clear, float nir, bool isReal) {
  Serial.println("Logging results to SD card...");
  logFile = SD.open("/sensor_data.json", FILE_WRITE);  // Use a fixed filename
  if (logFile) {
    logFile.print("{ \"pH\": ");
    logFile.print(ph);
    logFile.print(", \"ec\": ");
    logFile.print(ec);
    logFile.print(", \"moisture\": ");
    logFile.print(moisture);
    logFile.print(", \"temperature\": ");
    logFile.print(temperature);
    logFile.print(", \"humidity\": ");
    logFile.print(humidity);
    logFile.print(", \"Spectrum\": [");
    logFile.print("{ \"violetCh1\": ");
    logFile.print(violetCh1);
    logFile.print(", \"violetCh2\": ");
    logFile.print(violetCh2);
    logFile.print(", \"blue\": ");
    logFile.print(blue);
    logFile.print(", \"greenCh4\": ");
    logFile.print(greenCh4);
    logFile.print(", \"greenCh5\": ");
    logFile.print(greenCh5);
    logFile.print(", \"orange\": ");
    logFile.print(orange);
    logFile.print(", \"redCh7\": ");
    logFile.print(redCh7);
    logFile.print(", \"redCh8\": ");
    logFile.print(redCh8);
    logFile.print(", \"clear\": ");
    logFile.print(clear);
    logFile.print(", \"nir\": ");
    logFile.print(nir);
    logFile.print("}], ");
    logFile.print("\"assessment\": ");
    logFile.print(isReal ? "\"Pure Honey\"" : "\"Adulterated Honey\"");
    logFile.println("}");
    logFile.close();
    Serial.println("Data logged to /sensor_data.json");
  }

  else {
    Serial.println("Failed to open log file.");
  }
}

void handleRoot() {
  server.send(200, "text/html", htmlPage());  // Send the HTML page content
}

void handleLatestLog() {
  File logFile = SD.open("/sensor_data.json");
  if (logFile) {
    String jsonString = "";
    while (logFile.available()) {
      jsonString += (char)logFile.read();
    }
    logFile.close();
    Serial.println("Latest log file read: /sensor_data.json");
    Serial.println(jsonString);
    server.send(200, "application/json", jsonString);  // Send the JSON data to the client
  } else {
    Serial.println("Failed to open log file.");
    server.send(404, "text/plain", "File not found");
  }
}

String htmlPage() {
  return String(HTML_PAGE);
}


void checkSDCard() {
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed!");
    delay(1000);  // Delay to retry
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("No MicroSD Card detected. Please reinsert a MicroSD card");
    display.display();
    String response = "{\"message\": \" No MicroSD Card is detected. Please reinsert the card\"}";
    server.send(200, "application/json", response);
  }
}

// Function to calculate estimated moisture based on EC value
float calculateMoisture(float ec) {
  // Polynomial formula coefficients:
  // Moisture = a * EC^2 + b * EC + c
  float a = 0.00000140;
  float b = 0.00046;
  float c = 20.29594;

  float moisture = (a * ec * ec) + (b * ec) + c;

  return moisture;
}
