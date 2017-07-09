#include <ESP8266wifi.h>
#include "oled.h"
#include <Wire.h>
#include <ESP8266HTTPClient.h>

String deviceName = "Robot";
// WiFi settings
const char *ssid = "MSFTGUEST";

void setup()
{
    Serial.begin(9600);
    oled_setup();
    Serial.println("ESP8266 starting in normal mode");
    // Connect to WiFi
    oled_clear();
    oled_println("Wifi Connecting..");

    WiFi.begin(ssid); //, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    oled_println("Wifi connected");
    // Print the IP address
    Serial.println(WiFi.localIP());
}

void loop()
{
    HTTPClient http;
    http.begin("http://binglearningdemo.azurewebsites.net/api/messages/" + deviceName);

    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http.getString();
            Serial.println(payload);
            oled_clear();
            oled_println(payload);
        }
    }
    else
    {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    delay(2000);
}