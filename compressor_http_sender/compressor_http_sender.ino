
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Shivkumar.R";
const char* password = "shivshiv";

const char* serverURL = "http://10.44.127.97:8000/store";

// Digital pins
const int pins[] = {16, 17, 18, 19, 21, 22, 25, 26};

// Analog pin
const int PRESSURE_PIN = 34;

void setup() {
    Serial.begin(115200);

    for (int i = 0; i < 8; i++) {
        pinMode(pins[i], INPUT);
    }

    analogReadResolution(12);
    analogSetPinAttenuation(PRESSURE_PIN, ADC_11db);

    WiFi.begin(ssid, password);

    Serial.print("Connecting");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi Connected!");
}

void loop() {

    if (WiFi.status() == WL_CONNECTED) {

        int state[8];

        for (int i = 0; i < 8; i++) {
            state[i] = digitalRead(pins[i]);
        }

        // Average pressure voltage over 20 samples
        unsigned long total = 0;

        for (int i = 0; i < 20; i++) {
            total += analogReadMilliVolts(PRESSURE_PIN);
            delay(5);
        }

        float voltage = (total / 20.0) / 1000.0;

        // Calculate current using 150 ohm resistor
        float current = (voltage / 150.0) * 1000.0;

        // Convert 4-20mA to 0-10 bar
        float pressure = (current - 4.0) * 10.0 / 16.0;

        // Limit pressure range
        pressure = constrain(pressure, 0.0, 10.0);

        // Prepare JSON
        String json = "{";

        json += "\"c1_on\":" + String(state[0]) + ",";
        json += "\"c1_load\":" + String(state[1]) + ",";
        json += "\"c2_on\":" + String(state[2]) + ",";
        json += "\"c2_load\":" + String(state[3]) + ",";
        json += "\"c3_on\":" + String(state[4]) + ",";
        json += "\"c3_load\":" + String(state[5]) + ",";
        json += "\"c4_on\":" + String(state[6]) + ",";
        json += "\"c4_load\":" + String(state[7]) + ",";
        json += "\"pressure_voltage\":" + String(voltage, 3) + ",";
        json += "\"pressure_current\":" + String(current, 2) + ",";
        json += "\"pressure_bar\":" + String(pressure, 2);

        json += "}";

        HTTPClient http;

        http.begin(serverURL);
        http.addHeader("Content-Type", "application/json");

        int response = http.POST(json);

        Serial.println("\n--------------------");
        Serial.println(json);
        Serial.print("HTTP Response: ");
        Serial.println(response);

        http.end();
    }
    else {
        Serial.println("WiFi disconnected!");
        WiFi.reconnect();
    }

    delay(5000);
}
