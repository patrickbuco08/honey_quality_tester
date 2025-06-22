#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#define BOCUM_API_BASE_URL "https://honey-quality-tester.bucocu.net"
#define BOCUM_API_TOKEN "Fc0gBn7eLzWqkA8n3U2Jv5PpYeGiDR9tQsBhEMZLxVfNK6cyH1uOgTIabXCdqMwY"

bool sendHoneySampleToServer(String jsonPayload) {
    WiFiClientSecure client;
    HTTPClient https;

    client.setInsecure(); // Skips SSL certificate validation

    bool success = false;
    String endpoint = String(BOCUM_API_BASE_URL) + "/api/honey-samples";
    Serial.println("\n--- DEBUG: sendHoneySampleToServer ---");
    Serial.println("WiFi RSSI: " + String(WiFi.RSSI()));
    Serial.println("Sending POST request to: " + endpoint);
    Serial.println("Using endpoint: " + endpoint);
    Serial.println("Payload: " + jsonPayload);

    https.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
    bool beginResult = https.begin(client, endpoint);
    Serial.println("https.begin result: " + String(beginResult));
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Authorization", String("Bearer ") + BOCUM_API_TOKEN);
    https.addHeader("User-Agent", "ESP32Client/1.0");

    int httpResponseCode = https.POST(jsonPayload);

    Serial.println("httpResponseCode: " + String(httpResponseCode));
    Serial.println("Redirect location (if any): " + https.header("Location"));
    Serial.println("Response body:");
    Serial.println(https.getString());
    Serial.println("--- END DEBUG ---\n");
    Serial.println(https.getString());

    if (httpResponseCode == 201) {
        Serial.println("POST successful");
        success = true;
    } else {
        Serial.print("POST failed, error: ");
        Serial.println(https.errorToString(httpResponseCode).c_str());
    }

    https.end();

    return success;
}

// Helper function to handle NaN values
String formatValue(float value, int decimals) {
  if (isnan(value)) return "null";
  return String(value, decimals);
}

// Helper function to ensure absorbance values are non-negative
String formatAbsorbance(float value, int decimals) {
  if (isnan(value)) return "null";
  return String(max(value, 0.0f), decimals); // Ensure non-negative
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
    String jsonPayload = "{\"data\":{\"ambient_reading\":{\"humidity\":" + formatValue(humidityValue, 2) + ",\"temperature\":" + formatValue(tempValue, 2) + "},\"sensor_readings\":{\"ec_value\":" + formatValue(ECValue, 2) + ",\"moisture\":" + formatValue(moistureValue, 2) + ",\"ph_value\":" + formatValue(phValue, 2) + ",\"spectroscopy_moisture\":" + formatValue(spectroscopyMoisture, 2) + "},\"absorbance_readings\":{\"blue\":" + formatAbsorbance(absorbanceBlue, 2) + ",\"clear\":" + formatAbsorbance(absorbanceClear, 2) + ",\"orange\":" + formatAbsorbance(absorbanceOrange, 2) + ",\"near_ir\":" + formatAbsorbance(absorbanceNIR, 2) + ",\"red_ch7\":" + formatAbsorbance(absorbanceRedCh7, 2) + ",\"red_ch8\":" + formatAbsorbance(absorbanceRedCh8, 2) + ",\"green_ch4\":" + formatAbsorbance(absorbanceGreenCh4, 2) + ",\"green_ch5\":" + formatAbsorbance(absorbanceGreenCh5, 2) + ",\"violet_ch1\":" + formatAbsorbance(absorbanceVioletCh1, 2) + ",\"violet_ch2\":" + formatAbsorbance(absorbanceVioletCh2, 2) + "}}}";
    
    return jsonPayload;
}