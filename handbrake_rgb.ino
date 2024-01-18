#include <Joystick.h>
#include <FastLED.h>

// CONTROL
const int maxDisp = 1023;  // Máximo valor del potenciómetro según fabricante

// LEDS
#define NUM_LEDS 4    // Número de LEDs en tu tira
#define PIN_LED 6     // Pin al que está conectada la tira de LEDs
CRGB leds[NUM_LEDS];  // Creo un array con los LEDs controlables

// Paleta de colores blanco, azul, lila y morado
CRGBPalette16 customPalette = CRGBPalette16(
  CRGB::Green,  // Verde
  CRGB::Blue,   // Azul
  CRGB::Red,  // Lila
  CRGB::Purple  // Morado
);

void encenderLeds() {
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = ColorFromPalette(customPalette, i * 16);
    FastLED.show();
    delay(100 * i);
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(100);
  }
  delay(200);

  // Hacer parpadear el LED verde 3 veces
  for (int i = 0; i < 3; ++i) {
    leds[0] = CRGB::Green;
    FastLED.show();
    delay(300);
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(300);
  }
}

void setup() {
  pinMode(A0, INPUT);        // definición pin entrada
  pinMode(PIN_LED, OUTPUT);  // definición pin salida

  Joystick.begin();    // arrancamos la libreria Joystick
  Serial.begin(9600);  // arrancamos el puerto serie para monitorizar en PC

  FastLED.addLeds<WS2812B, PIN_LED, GRB>(leds, NUM_LEDS);  // Configurar la tira de LEDs
  FastLED.setBrightness(50);                              // Establecer el brillo ~50% (100 en un rango 0-255)

  encenderLeds();  // Llamar a la función para encender los LEDs al inicio
}



void loop() {
  //CONTROL--------------------------------------------------------

  int potDisp = analogRead(A0);  // guardamos como valor la respuesta del potenciometro
  int invertedValue = maxDisp - potDisp;
  invertedValue = (invertedValue < 10) ? 0 : invertedValue;  // Invertir el valor para tener 0 en el mínimo y 100 en el máximo

  // Mapear el recorrido del potenciometro disponible del total, con el valor de salida necesario
  // map(lectura, min potenciometro, max potenciometro, min respuesta PC, max respuesta PC)
  // int mappedValue = map(potDisp, 0, 1023, 0, 100); ****funcion original
  int mappedValue = map(invertedValue, 420, 800, 0, 200);

  mappedValue = (mappedValue < 20) ? 0 : mappedValue;
  invertedValue = (invertedValue > 225) ? 300 : invertedValue;
  
  Joystick.setThrottle(mappedValue);  // Enviar el valor mapeado del joystick (potenciometro) al PC

  Serial.println(mappedValue);                                 // Mostrar el valor mapeado en el Monitor Serie, nos ayuda a calibrar
  Serial.println("Inverted Value: " + String(invertedValue));  // Imprimir el valor invertido en el Monitor Serie

  //LEDS------------------------------------------------------------

  CRGB color = CRGB::Red;                   // Cambiamos el color a blanco
  color.nscale8_video(mappedValue);       // Escalar la intensidad a un rango de 0-255
  leds[0] = CRGB::Green;                      // Establecer el color verde solo para el primer LED
  fill_solid(&leds[1], NUM_LEDS - 1, color);  // Dejar el resto de LEDs en blanco
  FastLED.show();                             // Mostrar los colores en la tira de LEDs

  delay(100);  // suaviza la ejecución entre loops.
}