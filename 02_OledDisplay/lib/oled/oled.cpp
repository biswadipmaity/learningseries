#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include <oled.h>

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void oled_setup()
{
  pinMode(OLED_VCC, OUTPUT);
  digitalWrite(OLED_VCC, HIGH);

  // put your setup code here, to run once:
  Serial.begin(115200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 64x48)
  display.display();
  delay(200);

  // Clear the buffer.
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}

void oled_print(char str)
{
  display.print(str);
  display.display();
}

void oled_println(String str)
{
  display.println(str);
  display.display();
}