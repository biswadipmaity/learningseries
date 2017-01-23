#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_VCC   D4
#define OLED_MOSI  D2
#define OLED_CLK   D3
#define OLED_DC    3
#define OLED_CS    -1
#define OLED_RESET D1
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void printMacAddress() {
       byte mac[6];
       WiFi.macAddress(mac);
       display.print(mac[0], HEX);
       display.print(":");
       display.print(mac[1], HEX);
       display.print(":");
       display.print(mac[2], HEX);
       display.print(":");
       display.print(mac[3], HEX);
       display.print(":");
       display.print(mac[4], HEX);
       display.print(":");
       display.println(mac[5], HEX);
}

void setup() {
       pinMode(OLED_VCC, OUTPUT);
       digitalWrite(OLED_VCC, HIGH);

       // put your setup code here, to run once:
       Serial.begin(115200);

       // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
       display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
       display.display();
       delay(200);

       // Clear the buffer.
       display.clearDisplay();

       // text display tests
       display.setTextSize(1);
       display.setTextColor(WHITE);
       display.setCursor(0, 0);
       display.println("My MAC Address is : ");
       printMacAddress();
       display.display();
}

void loop()
{
 
}
