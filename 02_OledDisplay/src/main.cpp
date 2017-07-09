#include <ESP8266wifi.h>
#include <SPI.h>
#include <Wire.h>
#include <oled.h>

void printMacAddress()
{
    byte mac[6];
    WiFi.macAddress(mac);

    char MAC_char[18]="";
    for (int i = 0; i < sizeof(mac); ++i)
    {
        sprintf(MAC_char, "%s%02x:", MAC_char, mac[i]);
    }

    Serial.print(MAC_char);
    oled_println(MAC_char);
}

void setup()
{
    oled_setup();
    
    Serial.begin(9600);
    Serial.println("Program started");

    oled_println("My Mac address :");
    printMacAddress();
}

void loop()
{
    
}