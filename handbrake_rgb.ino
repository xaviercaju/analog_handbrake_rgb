#include <Joystick.h>
#include <FastLED.h>

#define NUM_LEDS 20  // Número de LEDs en tu tira
#define PIN_LED 6    // Pin al que está conectada la tira de LEDs

CRGB leds[NUM_LEDS];

const int deadZone = 10;  // Tamaño de la zona muerta
const int maxPot = 123;

void setup() {
  pinMode(A0, INPUT);
  pinMode(PIN_LED, OUTPUT);
  
  Joystick.begin();
  
  Serial.begin(9600); // Inicializar el puerto serie para ver la posición en el Monitor Serie

  FastLED.addLeds<WS2812B, PIN_LED, GRB>(leds, NUM_LEDS); // Configurar la tira de LEDs
  FastLED.setBrightness(100); // Establecer el brillo al 50% (rango 0-255)
}

void loop() {
  int potValue = analogRead(A0);

  // Aplicar la zona muerta
  if (potValue < deadZone) {
    potValue = 0;  // En la zona muerta inferior, asume mínimo
  } else if (potValue > maxPot - deadZone) {
    potValue = maxPot;  // En la zona muerta superior, asume máximo
  }

  int mappedValue = map(potValue, deadZone, maxPot - deadZone, 30, -230); // Mapear el valor a un rango de 0 a 100
  //new logic
  
  Joystick.setThrottle(mappedValue); // Enviar el valor mapeado al eje de "throttle" del Joystick
  
  CRGB color = CRGB::White;  // Cambiamos el color a verde solo para el primer LED
  color.nscale8_video(mappedValue * 2); // Escalar la intensidad a un rango de 0-255
  leds[0] = CRGB::Green;  // Establecer el color verde solo para el primer LED
  fill_solid(&leds[1], NUM_LEDS - 1, color); // Dejar el resto de LEDs en blanco
  FastLED.show(); // Mostrar los colores en la tira de LEDs
  
  Serial.println(mappedValue); // Mostrar el valor mapeado en el Monitor Serie
  delay(100); // Opcional: para evitar lecturas rápidas y estables del potenciómetro
}
