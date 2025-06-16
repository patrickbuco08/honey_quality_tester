#include <SD.h>
#include <SPI.h>

#define PH_PIN 35 
#define PH_1 4.01
#define PH_2 9.18

float pH4Voltage = 0;
float pH9Voltage = 0;

float calibrationValue_inSD_pH4() {
  float ph4_calibrationValue=0;
  File file = SD.open("/calibration_pH4.txt", FILE_READ);
    if (file) {
        while (file.available()) {
            String line = file.readStringUntil('\n');
            if (line.startsWith("PH4_voltage=")) {
                ph4_calibrationValue = line.substring(12).toFloat();
                //Serial.print("Loaded saved pH 4.01 calibration value: ");
                //Serial.println(ph4_calibrationValue);
            }
        }
        file.close();
    } else {
        //Serial.println("No calibration file found on microSD.");
    }
  return ph4_calibrationValue;
}

float calibrationValue_inSD_pH9() {
  float ph9_calibrationValue=0;
  File file = SD.open("/calibration_pH9.txt", FILE_READ);
    if (file) {
        while (file.available()) {
            String line = file.readStringUntil('\n');
            if (line.startsWith("PH9_voltage=")) {
                ph9_calibrationValue = line.substring(12).toFloat();
                //Serial.print("Loaded saved pH 4.01 calibration value: ");
                //Serial.println(ph4_calibrationValue);
            }
        }
        file.close();
    } else {
        //Serial.println("No calibration file found on microSD.");
    }
  return ph9_calibrationValue;
}

float pH_calibrationValue() {
    int sensorValue = analogRead(PH_PIN);
    float voltage = sensorValue * (3.3 / 4095.0); 
    return voltage;
}

float readPHvalue(){
  pH4Voltage = calibrationValue_inSD_pH4();
  pH9Voltage = calibrationValue_inSD_pH9();

  // Serial.print("PH4 Cal Value: ");
  // Serial.println(pH4Voltage);
  // Serial.print("PH9 Cal Value: ");
  // Serial.println(pH9Voltage);

  int sensorValue = analogRead(PH_PIN);
  float voltage = sensorValue * (3.3 / 4095.0);

  // Calculate pH based on the two-point calibration with pH 9.18 and pH 4.01
  float slope = (PH_2 - PH_1) / ( pH9Voltage - pH4Voltage);
  float intercept = PH_2 - slope * (pH9Voltage);
  float pHValue = slope * (voltage) + intercept;

  return pHValue;

}
