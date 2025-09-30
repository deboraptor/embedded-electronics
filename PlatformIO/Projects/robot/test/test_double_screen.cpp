// https://www.hackster.io/nash-ali/esp32-esp8266-dual-oleds-631382
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

Adafruit_SSD1306 display1(-1);
Adafruit_SSD1306 display2(-1);
// this is the default address of the display(0x78) on back of display
#define OLED1 0x3C
// this is after switching over the jumper.
#define OLED2 0x3D
int i, j;

void setup()   {
  display1.begin(SSD1306_SWITCHCAPVCC, OLED1);
  display1.clearDisplay();
  display1.display();
  
  display2.begin(SSD1306_SWITCHCAPVCC, OLED2);
  display2.clearDisplay();
  display2.display();
}


void loop() {

  for (int i = 0; i < 270; i+=10) {

    display1.setTextSize(1);
    display1.setTextColor(WHITE);
    display1.setCursor(0, 0 );
    display1.println("Display 1");
    display1.fillCircle(i, 30,  5, 1);
    display1.display();
    display1.clearDisplay();

    display2.setTextSize(1);
    display2.setTextColor(WHITE);
    display2.setCursor(0, 0);
    display2.println("Display 2");
    display2.fillCircle(i - 127, 30,  5, 1);
    display2.display();
    display2.clearDisplay();
  }
  

}
