# Controlador Joystick con Tira de LEDs

Este es un programa de ejemplo para controlar un joystick analógico y una tira de LEDs utilizando una placa Arduino y las bibliotecas Joystick.h y FastLED.h.

## Requisitos

- Placa Arduino (p. ej., Arduino Uno)
- Joystick analógico
- Tira de LEDs direccionable compatible con WS2812B
- Cableado para conectar el joystick y la tira de LEDs a la placa Arduino

## Dependencias

Asegúrate de haber instalado las siguientes bibliotecas en tu entorno de Arduino IDE:

- [Joystick Library](https://github.com/MHeironimus/ArduinoJoystickLibrary): Utilizada para emular un joystick con el valor del eje "throttle".
- [FastLED Library](https://github.com/FastLED/FastLED): Utilizada para controlar la tira de LEDs.

## Código

```cpp
#include <Joystick.h>
#include <FastLED.h>

#define NUM_LEDS 20  // Número de LEDs en tu tira
#define PIN_LED 6    // Pin al que está conectada la tira de LEDs

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(A0, INPUT);
  pinMode(PIN_LED, OUTPUT);
  
  Joystick.begin();
  
  Serial.begin(9600); // Inicializar el puerto serie para ver la posición en el Monitor Serie

  FastLED.addLeds<WS2812B, PIN_LED, GRB>(leds, NUM_LEDS); // Configurar la tira de LEDs
  FastLED.setBrightness(255); // Establecer el brillo al 50% (rango 0-255)
}

void loop() {
  int potValue = analogRead(A0);
  int mappedValue = map(potValue, 0, 1023, 0, 100); // Mapear el valor a un rango de 0 a 100
  
  Joystick.setThrottle(mappedValue); // Enviar el valor mapeado al eje de "throttle" del Joystick
  
  CRGB color = CRGB::White;  // Cambiamos el color a verde solo para el primer LED
  color.nscale8_video(mappedValue * 2); // Escalar la intensidad a un rango de 0-255
  leds[0] = CRGB::Green;  // Establecer el color verde solo para el primer LED
  fill_solid(&leds[1], NUM_LEDS - 1, color); // Dejar el resto de LEDs en blanco
  FastLED.show(); // Mostrar los colores en la tira de LEDs
  
  Serial.println(mappedValue); // Mostrar el valor mapeado en el Monitor Serie
  delay(100); // Opcional: para evitar lecturas rápidas y estables del potenciómetro
}
```

## Descripción

Este código muestra cómo utilizar un joystick analógico conectado al pin analógico A0 para controlar un eje "throttle" emulado en el Joystick. Además, se utiliza una tira de LEDs WS2812B para visualizar el valor del joystick mediante un cambio en el brillo del primer LED en la tira.

### Funciones principales

- `setup()`: Esta función se ejecuta una vez al inicio y se encarga de inicializar la configuración inicial del programa, como la configuración de pines y la inicialización de las bibliotecas Joystick y FastLED.

- `loop()`: Esta función se ejecuta en bucle continuamente después de la función `setup()`. En esta función, se realiza el proceso principal del programa, que incluye leer el valor del potenciómetro del joystick, mapear ese valor a un rango de 0 a 100 y enviarlo como el valor del eje "throttle" del Joystick. También se controla el brillo del primer LED de la tira según el valor mapeado.

## Configuración

Antes de cargar este código en tu placa Arduino, asegúrate de haber conectado el joystick analógico y la tira de LEDs al Arduino siguiendo el cableado adecuado. Además, asegúrate de haber instalado las bibliotecas requeridas mencionadas anteriormente.

## Notas

- Asegúrate de calibrar correctamente el joystick antes de usarlo para obtener lecturas precisas en el rango deseado.

- Puedes ajustar el rango mapeado del potenciómetro según tus necesidades cambiando los valores en la función `map()`.

- El primer LED de la tira cambiará de brillo según el valor del joystick, mientras que los demás LEDs permanecerán en blanco.

- Si experimentas problemas con la tira de LEDs, asegúrate de haber configurado correctamente el tipo de tira y el esquema de color en la función `FastLED.addLeds<WS2812B, PIN_LED, GRB>(leds, NUM_LEDS)`.

¡Diviértete experimentando con el joystick y la tira de LEDs!
