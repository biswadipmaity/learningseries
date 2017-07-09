#include <ESP8266wifi.h>
#include <SPI.h>
#include <Wire.h>
#include <oled.h>

void printMacAddress()
{
    byte mac[6];
    WiFi.macAddress(mac);

    char MAC_char[18];
    for (int i = 0; i < sizeof(mac); ++i)
    {
        sprintf(MAC_char, "%s%02x:", MAC_char, mac[i]);
    }

    Serial.print(MAC_char);
    //oled_println(MAC_char);
}

void setup()
{
    Serial.begin(9600);
    Serial.println("Program started");
    oled_setup();
    printMacAddress();
}

void loop()
{
    oled_println("ABC");
    oled_println("DEF");
    oled_println("GHI");
    delay(1000);
}