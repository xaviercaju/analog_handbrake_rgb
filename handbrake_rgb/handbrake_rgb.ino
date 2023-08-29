#include <Joystick.h>
#include <FastLED.h>

//CONTROL
const int maxDisp = 1023;  // Máximo valor del potenciómetro según fabricante

//LEDS
#define NUM_LEDS 4    // Número de LEDs en tu tira
#define PIN_LED 6     // Pin al que está conectada la tira de LEDs
CRGB leds[NUM_LEDS];  // Creo un array con los leds controlables

void setup() {
  pinMode(A0, INPUT);        // definición pin entrada
  pinMode(PIN_LED, OUTPUT);  // definición pin salida

  Joystick.begin();    // arrancamos la libreria Joystick
  Serial.begin(9600);  // arrancamos el puerto serie para monitorizar en PC

  FastLED.addLeds<WS2812B, PIN_LED, GRB>(leds, NUM_LEDS);  // Configurar la tira de LEDs
  FastLED.setBrightness(100);                              // Establecer el brillo ~50% (100 en un rango 0-255)
}

void loop() {
  //CONTROL--------------------------------------------------------

  int potDisp = analogRead(A0);           // guardamos como valor la respuesta del potenciometro
  int invertedValue = maxDisp - potDisp;  // Invertir el valor para tener 0 en el mínimo y 100 en el máximo

  // Mapear el recorrido del potenciometro disponible del total, con el valor de salida necesario
  // map(lectura, min potenciometro, max potenciometro, min respuesta PC, max respuesta PC)
  // int mappedValue = map(potDisp, 0, 1023, 0, 100); ****funcion original
  int mappedValue = map(invertedValue, 822, 930, 0, 100);
  Joystick.setThrottle(mappedValue);  // Enviar el valor mapeado del joystick (potenciometro) al PC

  Serial.println(mappedValue);                                 // Mostrar el valor mapeado en el Monitor Serie, nos ayuda a calibrar
  Serial.println("Inverted Value: " + String(invertedValue));  // Imprimir el valor invertido en el Monitor Serie

  //LEDS------------------------------------------------------------

  CRGB color = CRGB::White;                   // Cambiamos el color a blanco
  color.nscale8_video(mappedValue * 2);       // Escalar la intensidad a un rango de 0-255
  leds[0] = CRGB::Green;                      // Establecer el color verde solo para el primer LED
  fill_solid(&leds[1], NUM_LEDS - 1, color);  // Dejar el resto de LEDs en blanco
  FastLED.show();                             // Mostrar los colores en la tira de LEDs

  delay(100);  // suaviza la ejecución entre loops.
}