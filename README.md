# Xavo Handbrake

Proyecto de creación de un freno de mano para SimRacing. 

## Hardware

- Placa Arduino Pro Micro o superior.
- Potenciometro lineal
- Tira de LEDs direccionable compatible con WS2812B
- Cableado para conectar el joystick y la tira de LEDs a la placa Arduino

## Dependencias

Asegúrate de haber instalado las siguientes bibliotecas en tu entorno de Arduino IDE:

- [Joystick Library](https://github.com/MHeironimus/ArduinoJoystickLibrary): Utilizada para emular un joystick mediante la respuesta del potenciometro.
- [FastLED Library](https://github.com/FastLED/FastLED): Utilizada para controlar la tira de LEDs.

## Descripción

Mediante un potenciometro lineal simulamos un joystick que proporciona una respuesta analógica, perfecta para aplicar una fuerza variable en la frenada. Incluye el control de unas luces reactivas que cambian de comportamiento en función del estado y progresión del freno.

### Funciones principales

- `setup()`: Esta función se ejecuta una vez al inicio y se encarga de inicializar la configuración inicial del programa, como la configuración de pines y la inicialización de las bibliotecas Joystick y FastLED.

- `loop()`: Esta función se ejecuta en bucle continuamente después de la función `setup()`. En esta función, se realiza el proceso principal del programa, que incluye leer el valor del potenciómetro del joystick, mapear ese valor a un rango de 0 a 255 y enviarlo como el valor del eje "throttle" del Joystick. También se controla la respuesta LED de la tira según el valor mapeado.

## Configuración

Antes de cargar este código en tu placa Arduino, asegúrate de haber conectado el potenciometro y la tira de LEDs al Arduino siguiendo el cableado adecuado. Además, asegúrate de haber instalado las bibliotecas requeridas mencionadas anteriormente.

## Notas

- Asegúrate de calibrar correctamente el joystick antes de usarlo para obtener lecturas precisas en el rango deseado.

- Puedes ajustar el rango mapeado del potenciómetro según tus necesidades cambiando los valores en la función `map()`.

- El primer LED de la tira permanecerá en blanco como LED de estatus, mientras el resto cambiará de brillo según el valor del joystick.

- Si experimentas problemas con la tira de LEDs, asegúrate de haber configurado correctamente el tipo de tira y el esquema de color en la función `FastLED.addLeds<WS2812B, PIN_LED, GRB>(leds, NUM_LEDS)`.

https://www.youtube.com/@xaviercaju
https://github.com/xaviercaju
