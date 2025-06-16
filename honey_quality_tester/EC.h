/*
  In this prototype, I used only the TDS module since the EC module is pricey

  The equation I used to directly read the EC value is Linear Algebra


  The TDS must be calibrated using the EC solution using the 1413 µS/cm and 1288 µS/cm



*/

#define EC_PIN 34

int EC1_analogValue = 0; // Analog reading in 1413 µS/cm solution
int EC2_analogValue = 0; // Analog reading in 1288 µS/cm solution

float EC_calibrationValue() {
    int sensorValue = analogRead(EC_PIN);
    Serial.println("EC sensor value: " + String(sensorValue));
    return sensorValue;
}

float calibrationValue_inSD_EC1413() {
  float EC1413_calibrationValue=0;
  File file = SD.open("/calibration_EC1413.txt", FILE_READ);
    if (file) {
        while (file.available()) {
            String line = file.readStringUntil('\n');
            if (line.startsWith("EC1413=")) {
                EC1413_calibrationValue = line.substring(7).toFloat();
                //Serial.print("Loaded saved pH 4.01 calibration value: ");
                //Serial.println(ph4_calibrationValue);
            }
        }
        file.close();
    } else {
        //Serial.println("No calibration file found on microSD.");
    }
  return EC1413_calibrationValue;
}

float calibrationValue_inSD_EC1288() {
  float EC1288_calibrationValue=0;
  File file = SD.open("/calibration_EC1288.txt", FILE_READ);
    if (file) {
        while (file.available()) {
            String line = file.readStringUntil('\n');
            if (line.startsWith("EC1288=")) {
                EC1288_calibrationValue = line.substring(7).toFloat();
                //Serial.print("Loaded saved EC 1288 us/cm calibration value: ");
                //Serial.println(ph4_calibrationValue);
            }
        }
        file.close();
    } else {
        //Serial.println("No calibration file found on microSD.");
    }
  return EC1288_calibrationValue;
}

float readECvalue() {
  const int samples = 20;
  long sum = 0;

  for (int i = 0; i < samples; i++) {
    sum += analogRead(EC_PIN);
    delay(5); // small delay between reads
  }

  float analogValue = sum / (float)samples;

  // Coefficients from Ridge Regression
  float a = 0.718002;           // linear
  float b = -0.000135;      // quadratic
  float c = 0.00000004547;   // cubic
  float d = 76.54;           // intercept

  // Polynomial EC estimation
  float ecValue = a * analogValue + b * analogValue * analogValue + c * analogValue * analogValue * analogValue + d;

  // Clamp to 0 if negative (optional safety)
  if (ecValue < 0) ecValue = 0;

  return ecValue; // in µS/cm
}

float readECvalueOld()
{
  EC1_analogValue = calibrationValue_inSD_EC1413() ; // Analog reading in 1413 µS/cm solution
  EC2_analogValue = calibrationValue_inSD_EC1288();
  int analogValue = analogRead(EC_PIN);
  float EC1 = 1413.0;
  float EC2 = 1288.0;
  float m = (EC2 - EC1) / (EC2_analogValue - EC1_analogValue);
  float b = EC1 - (m * EC1_analogValue);

  float ecValue = m * analogValue + b; // Apply linear conversion

  return ecValue;
}
