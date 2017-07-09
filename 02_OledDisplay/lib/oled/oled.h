#define OLED_VCC   D4
#define OLED_MOSI  D2
#define OLED_CLK   D3
#define OLED_DC    3
#define OLED_CS    -1
#define OLED_RESET D1

void oled_setup();
void oled_print(char);
void oled_println(String str);
