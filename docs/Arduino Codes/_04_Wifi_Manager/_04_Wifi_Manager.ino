#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266HTTPClient.h>

String deviceName = "Robot";

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
       display.println("Connecting to Wifi.");
       printMacAddress();
       display.display();

       WiFiManager wifiManager;

       char apName[50];
       ("ForDemoAP-" + deviceName).toCharArray(apName, 50);
       wifiManager.autoConnect(apName);

       //if you get here you have connected to the WiFi
       Serial.println("connected..");
       display.clearDisplay();
       display.setCursor(0, 0);
       display.println("Connected..");
       //display.setCursor(1,0);
       display.println(WiFi.localIP().toString());
       display.display();
       delay(2000);
}

void loop() {
       HTTPClient http;
       http.begin("http://binglearningdemo.azurewebsites.net/api/messages/" + deviceName);
       // start connection and send HTTP header
       int httpCode = http.GET();

       // httpCode will be negative on error
       if (httpCode > 0) {
              // HTTP header has been send and Server response header has been handled
              Serial.printf("[HTTP] GET... code: %d\n", httpCode);

              // file found at server
              if (httpCode == HTTP_CODE_OK) {
                     String payload = http.getString();
                     Serial.println(payload);
                     display.clearDisplay();
                     display.setCursor(0, 0);
                     display.println(payload);
                     display.display();
              }
       }
       else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
       }

       http.end();
       delay(2000);
}
