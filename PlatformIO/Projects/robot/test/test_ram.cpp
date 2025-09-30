#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// --- ta déclaration d’écrans ---
Adafruit_SSD1306 ecrana(128, 64, &Wire, -1);
Adafruit_SSD1306 ecranb(128, 64, &Wire, -1);

// ----- utilitaire SRAM libre (AVR) -----
extern char __bss_end;
extern char *__brkval;
int freeRam() {
  char top;
  return &top - (__brkval ? __brkval : &__bss_end);
}
// --------------------------------------

void setup() {
  Serial.begin(115200);
  while(!Serial) {}

  Serial.print(F("SRAM au boot: ")); Serial.println(freeRam());

  if (!ecrana.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("ecrana.begin a échoué (allocation?)"));
  }
  Serial.print(F("Après ecrana.begin: ")); Serial.println(freeRam());

  if (!ecranb.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("ecranb.begin a échoué (allocation?)"));
  }
  Serial.print(F("Après ecranb.begin: ")); Serial.println(freeRam());

  // petit draw pour forcer l’usage des buffers
  ecrana.clearDisplay(); ecranb.clearDisplay();
  ecrana.display(); ecranb.display();
  Serial.print(F("Après 1er display sur les deux: ")); Serial.println(freeRam());
}

void loop() {}
