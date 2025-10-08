#pragma once // n’inclus ce fichier qu’une seule fois pendant la compilation, même si on l’appelle plusieurs fois avec #include.
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class Eyes {
public:
  Eyes(int sda, int scl, uint32_t freq, uint8_t addrA, uint8_t addrB);

  bool begin();
  void drawFrame(uint8_t i);
  void animateStep();

private:
  Adafruit_SSD1306 ecrana;
  Adafruit_SSD1306 ecranb;

  int _sda, _scl;
  uint32_t _freq;
  uint8_t _addrA, _addrB;

  uint8_t _idx = 0;
  uint32_t _tNext = 0;
};
