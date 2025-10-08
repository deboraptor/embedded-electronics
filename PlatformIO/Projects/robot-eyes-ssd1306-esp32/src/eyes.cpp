// génération des images en binaire : https://javl.github.io/image2cpp/?pseSrc=pgEcranOledArduino
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "eyes_bitmaps.h"
#include "eyes.h"


// Animation
static const unsigned char* FRAMES[] = { eye1b, eye2b, eye3b, eye4b, eye3b, eye2b, eye1b }; // définir l'ordre des frames
// les paramètres de chaque frame, indexés pareil
static const uint8_t  W[] = {85,83,81,87,81,83,85};   // largeur  de chaque frame
static const uint8_t  H[] = {48,47,47,47,47,47,48};   // hauteur  de chaque frame
static const int8_t   X[] = {21,22,23,20,23,22,21};   // position X de départ
static const int8_t   Y[] = { 8, 8, 8,  8, 8, 8,  8}; // position Y de départ
static const uint8_t N = sizeof(FRAMES)/sizeof(FRAMES[0]);

static const uint16_t FRAME_MS = 60; // durée d’affichage d’une frame
static const uint16_t HOLD_MS  = 1000; // pause en fin de cycle 

// POO, déclaration de la classe Eyes 
// c'est comme le truc de la librairie Adafruit_SSD1306
// mais avec mes 2 écrans et mes animations :
// Adafruit_SSD1306 ecrana(128, 64, &Wire, -1); 
// Adafruit_SSD1306 ecranb(128, 64, &Wire, -1); 
Eyes::Eyes(int sda, int scl, uint32_t freq, uint8_t addrA, uint8_t addrB)
: ecrana(128, 64, &Wire, -1),
  ecranb(128, 64, &Wire, -1),
  _sda(sda), _scl(scl), _freq(freq), _addrA(addrA), _addrB(addrB) {}


bool Eyes::begin() {
  // pin 21/22 (réservé pour I2C) en 400 kHz
  Wire.begin(_sda, _scl, _freq);

  // initialisation des écrans, s'il sont détectés à la bonne adresse A=0x3D, B=0x3C
  bool okA = ecrana.begin(SSD1306_SWITCHCAPVCC, _addrA);
  bool okB = ecranb.begin(SSD1306_SWITCHCAPVCC, _addrB);

  // B = “normal”, A = miroir horizontal de B
  // lui parler que si okA = true
  if (okA) ecrana.ssd1306_command(0xA0); // miroir de l'écran B pour l'écran A, à changer quand nouveaux dessins

  // apparement un peu plus de contraste
  // TODO : à tester si utile
  if (okA) ecrana.ssd1306_command(SSD1306_SETCONTRAST), ecrana.ssd1306_command(0x8F);
  if (okB) ecranb.ssd1306_command(SSD1306_SETCONTRAST), ecranb.ssd1306_command(0x8F);

  _idx = 0;
  _tNext = millis();
  return okA && okB;
}


void Eyes::drawFrame(uint8_t i) {
  if (i >= N) return;
  // void = ne retourne rien
  // inline = suggère au compilateur de copier-coller le code à chaque appel,
  //          pour éviter le surcoût d'un appel de fonction (gain de temps)
  // static = la fonction est visible uniquement dans ce fichier (évite les conflits de noms)
  ecrana.clearDisplay();
  ecranb.clearDisplay();

  ecrana.drawBitmap(X[i], Y[i], FRAMES[i], W[i], H[i], SSD1306_WHITE);
  ecranb.drawBitmap(X[i], Y[i], FRAMES[i], W[i], H[i], SSD1306_WHITE);

  ecrana.display();
  ecranb.display();
}


void Eyes::animateStep() {
  uint32_t now = millis();
  // on utilise millis() pour avoir un timing plus précis, delay() bloque tout
  if (now < _tNext) return;

  drawFrame(_idx);

  if (_idx == N - 1) {
    _tNext = now + HOLD_MS;
    _idx = 0;
  } else {
    _tNext = now + FRAME_MS;
    _idx++;
  }
}