#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#define BOCUM_API_BASE_URL "https://honey-quality-tester.bucocu.net"
#define BOCUM_API_TOKEN "Fc0gBn7eLzWqkA8n3U2Jv5PpYeGiDR9tQsBhEMZLxVfNK6cyH1uOgTIabXCdqMwY"

bool sendHoneySampleToServer(String jsonPayload) {
    WiFiClientSecure client;
    HTTPClient https;

    client.setInsecure(); // Skips SSL certificate validation

    bool success = false;

    https.begin(client, String(BOCUM_API_BASE_URL) + "/api/honey-samples");
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Authorization", String("Bearer ") + BOCUM_API_TOKEN);

    int httpResponseCode = https.POST(jsonPayload);

    Serial.println("httpResponseCode: " + String(httpResponseCode));
    Serial.println("https.getString(): " + https.getString());

    if (httpResponseCode == 201) {
        Serial.println("POST successful");
        Serial.println(https.getString());
        success = true;
    } else {
        Serial.print("POST failed, error: ");
        Serial.println(https.errorToString(httpResponseCode).c_str());
    }

    https.end();

    return success;
}

// Function to resolve JSON data from honey sample parameters
String jsonDataResolver(
    float humidityValue,
    float tempValue,
    float ECValue,
    float moistureValue,
    float phValue,
    float spectroscopyMoisture,
    float absorbanceBlue,
    float absorbanceClear,
    float absorbanceOrange,
    float absorbanceNIR,
    float absorbanceRedCh7,
    float absorbanceRedCh8,
    float absorbanceGreenCh4,
    float absorbanceGreenCh5,
    float absorbanceVioletCh1,
    float absorbanceVioletCh2
  ) {
    String jsonPayload = "{";
    jsonPayload += "\"ambient_reading\": {\"humidity\": " + String(humidityValue, 2) + ", \"temperature\": " + String(tempValue, 2) + "},";
    jsonPayload += "\"sensor_readings\": {\"ec_value\": " + String(ECValue, 2) + ", \"moisture\": " + String(moistureValue, 2) + ", \"ph_value\": " + String(phValue, 2) + ", \"spectroscopy_moisture\": " + String(spectroscopyMoisture, 2) + "},";
    jsonPayload += "\"absorbance_readings\": {";
    jsonPayload += "\"blue\": " + String(absorbanceBlue, 2) + ", ";
    jsonPayload += "\"clear\": " + String(absorbanceClear, 2) + ", ";
    jsonPayload += "\"orange\": " + String(absorbanceOrange, 2) + ", ";
    jsonPayload += "\"near_ir\": " + String(absorbanceNIR, 2) + ", ";
    jsonPayload += "\"red_ch7\": " + String(absorbanceRedCh7, 2) + ", ";
    jsonPayload += "\"red_ch8\": " + String(absorbanceRedCh8, 2) + ", ";
    jsonPayload += "\"green_ch4\": " + String(absorbanceGreenCh4, 2) + ", ";
    jsonPayload += "\"green_ch5\": " + String(absorbanceGreenCh5, 2) + ", ";
    jsonPayload += "\"violet_ch1\": " + String(absorbanceVioletCh1, 2) + ", ";
    jsonPayload += "\"violet_ch2\": " + String(absorbanceVioletCh2, 2);
    jsonPayload += "}}";
  
    return jsonPayload;
}