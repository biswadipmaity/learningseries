#include <ESP8266wifi.h>
#include <Wire.h>
#include <ESP8266HTTPClient.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include "oled.h"

String deviceName = "Robot";


WiFiManager wifiManager;


void setup()
{
    Serial.begin(9600);
    oled_setup();

    oled_clear();
    oled_println("Please connect to wifi with name:");
    
    //wifiManager.autoConnect();
    char deviceAPNameChars[50];
    String deviceAPName = deviceName + "-AP";
    deviceAPName.toCharArray(deviceAPNameChars, 50);
    oled_println(deviceAPName);
    oled_println("And visit 192.168.4.1");
    wifiManager.startConfigPortal(deviceAPNameChars);

    oled_println("WiFi connected");
    Serial.println("");
    Serial.println("WiFi connected");
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
