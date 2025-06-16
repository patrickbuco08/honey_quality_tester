#include <Wire.h>
#include <Adafruit_AS7341.h>

#include "RGB_color.h"

Adafruit_AS7341 as7341;

float absorbance[10];

void init_7341(){
  
  as7341.begin();
  
  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_256X);

}

void measureIntensity(float *intensities) {
    if (as7341.readAllChannels()) {
      // Directly read all 10 channels and store their values
      intensities[0] = as7341.getChannel(AS7341_CHANNEL_415nm_F1);
      intensities[1] = as7341.getChannel(AS7341_CHANNEL_445nm_F2);
      intensities[2] = as7341.getChannel(AS7341_CHANNEL_480nm_F3);
      intensities[3] = as7341.getChannel(AS7341_CHANNEL_515nm_F4);
      intensities[4] = as7341.getChannel(AS7341_CHANNEL_555nm_F5);
      intensities[5] = as7341.getChannel(AS7341_CHANNEL_590nm_F6);
      intensities[6] = as7341.getChannel(AS7341_CHANNEL_630nm_F7);
      intensities[7] = as7341.getChannel(AS7341_CHANNEL_680nm_F8);
      intensities[8] = as7341.getChannel(AS7341_CHANNEL_NIR);
      intensities[9] = as7341.getChannel(AS7341_CHANNEL_CLEAR);
      // Exit after a single read
    }
}

void calculateAbsorbance() {
  // Open the SD file to read calibration data (I0)
  File dataFile = SD.open("/calibration_as7341.txt", FILE_READ);
  if (!dataFile) {
    Serial.println("Failed to open intensities.txt for reading.");
    return;
  }

  // Dynamically allocate memory for calibration intensities
  float *I0 = new float[10];
  int channelIndex = 0;

  // Read the I0 values from the SD file
  while (dataFile.available() && channelIndex < 10) {
    String value = dataFile.readStringUntil('\n'); // Read each value as a string
    I0[channelIndex] = value.toFloat();           // Convert to float
    channelIndex++;
  }
  dataFile.close();

  // Check if we successfully read all 10 channels
  if (channelIndex != 10) {
    Serial.println("Error: Not enough calibration data in file.");
    delete[] I0; // Free allocated memory
    return;
  }

  // Calculate absorbance for each channel
  for (int i = 0; i < 10; i++) {
    Serial.println(I0[i]);
  }

  // Free dynamically allocated memory
  delete[] I0;
}




void readChannel_as7341()
{
  if (!as7341.readAllChannels()){
    Serial.println("Error reading all channels!");
    return;
  }
}


