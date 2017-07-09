#include <ESP8266wifi.h>
#include "oled.h"
#include <Wire.h>
#include <ESP8266HTTPClient.h>

String URL = "http://binglearningdemo.azurewebsites.net/api/messages/Robot";
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
}