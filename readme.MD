# 🍯 Honey Quality Tester

## Overview

This project is a comprehensive ESP32-based system designed to analyze honey quality through multiple sensor readings. It can detect adulteration and provide detailed measurements of honey properties using spectral analysis, pH, electrical conductivity, and moisture content measurements.

![Honey Quality Tester](https://raw.githubusercontent.com/patrickbuco08/honey_quality_tester/main/honey-tester-demo.jpg)

## 📋 Features

- **Multi-parameter Analysis**:
  - pH value measurement
  - Electrical conductivity (EC) measurement
  - Moisture content calculation
  - Spectral analysis with AS7341 (10-channel spectral sensor)
  - Temperature and humidity monitoring

- **User Interface**:
  - WiFi access point with web-based interface
  - OLED display for direct readings
  - Sensor calibration tools
  - Real-time analysis results

- **Data Management**:
  - SD card storage for logs and calibration data
  - Exportable results
  - Honey authenticity assessment

## 🔧 Hardware Requirements

- ESP32 microcontroller
- pH sensor
- EC (Electrical Conductivity) sensor
- AS7341 10-channel spectral sensor
- DHT22 temperature and humidity sensor
- Moisture sensor
- RGB indicator light
- OLED display
- SD card module
- Power supply

## 🔌 Wiring Diagram

```
ESP32 Connections:
- pH Sensor: Analog input (configured in ph.h)
- EC Sensor: Analog input (configured in EC.h)
- AS7341 Sensor: I2C connection (SDA, SCL)
- DHT22: Digital pin (configured in dht22.h)
- Moisture Sensor: Analog input (configured in moisture.h)
- RGB LED: Digital pins (configured in RGB_color.h)
- OLED Display: I2C connection
- SD Card Module: SPI connection (CS pin 5)
```

## 📲 Software Setup

1. **Dependencies**:
   - SPI.h - For SD card communication
   - WiFi.h - For wireless connectivity
   - WebServer.h - For web interface
   - AS7341 library - For spectral sensor
   - Adafruit GFX & SSD1306 libraries - For OLED display
   - DHT sensor library

2. **Installation**:
   - Clone this repository to your local machine
   - Open the `honey_quality_tester.ino` file in Arduino IDE
   - Install required libraries through Arduino Library Manager
   - Select ESP32 board from board manager
   - Upload code to your ESP32

## 🔬 Calibration

Before using the honey quality tester, calibration of sensors is necessary:

1. **pH Sensor Calibration**:
   - Use the "Calibrate pH Sensor (4.01)" button with a 4.01 pH buffer solution
   - Use the "Calibrate pH Sensor (9.18)" button with a 9.18 pH buffer solution

2. **EC Sensor Calibration**:
   - Use the "Calibrate EC Sensor (1413)" button with 1413 μS/cm solution
   - Use the "Calibrate EC Sensor (1288)" button with 1288 μS/cm solution

3. **AS7341 Spectral Sensor Calibration**:
   - Use the "Calibrate AS7341" button with air/no sample

## 🧪 Using the Tester

1. **Setup**:
   - Power on the device
   - Connect to the "ESP32-Honey Quality" WiFi network (password: 12345678)
   - Navigate to `http://192.168.4.1` in a web browser

2. **Analysis**:
   - Place honey sample in the testing chamber
   - Click "Start Analysis" button
   - Wait for approximately 10 seconds while measurements are collected
   - View results on the web interface or OLED display

3. **Interpreting Results**:
   - Results will show measured values for all parameters
   - The system will assess if the honey is likely authentic or adulterated
   - Results are automatically saved to the SD card

## 💾 Data Storage

Measurement results are stored on the SD card in JSON format including:
- Timestamp
- pH value
- EC value
- Moisture percentage
- Temperature & humidity
- Spectral absorbance readings (10 channels)
- Assessment result

## 🛠️ Troubleshooting

- **No SD Card detected**: Check SD card is properly inserted and formatted
- **Sensor errors**: Ensure proper calibration before testing
- **Connection issues**: Verify power supply and wiring connections

## 📚 Technical Details

This system uses multiple sensor data points to assess honey quality:

- **pH Analysis**: Pure honey typically has pH 3.4-6.1
- **Electrical Conductivity**: Measures ionic content, correlates with mineral content
- **Spectral Analysis**: AS7341 provides 10-channel spectral data to detect adulteration
- **Moisture Content**: Derived from EC measurements
- **Environmental Factors**: Temperature and humidity are monitored as control variables