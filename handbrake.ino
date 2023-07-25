/*
  Autor:    Xavier Carmona Juan
  GitHub:   https://github.com/xaviercaju
  YouTube:  youtube.com/@xaviercaju

  Título: Emulación de eje de freno de mano analógico con Arduino Pro Micro
  Descripción: Este código utiliza un potenciómetro conectado al pin A0 del Arduino Pro Micro
               para emular un eje analógico de freno de mano (handbrake) en juegos de simulación.
               El potenciómetro controla la posición del freno de mano en el juego.

  Importante: Asegúrate de haber instalado previamente la librería "Joystick" de MHeironimus en el IDE de Arduino.

  Hardware utilizado:
  - Arduino Pro Micro (o Arduino Leonardo)
  - Potenciómetro lineal de 10k ohm (conexiones: GND, VCC, DTB/Wiper)

  Conexiones del potenciómetro:
  - Conectar el pin "GND" del potenciómetro al pin GND del Arduino Pro Micro.
  - Conectar el pin "VCC" del potenciómetro al pin 5V del Arduino Pro Micro.
  - Conectar el pin "DTB" o "Wiper" del potenciómetro al pin A0 del Arduino Pro Micro.

  Notas:
  - Este código emula un eje de "throttle" (aceleración) en el joystick, ajustando los valores mapeados
    en la función map() al rango requerido por el juego.
  - El Monitor Serie se puede utilizar para depurar y verificar la posición del potenciómetro.

  Fecha: [08/08/2023]
*/

#include <Joystick.h>

void setup() {
  pinMode(A0, INPUT);
  Joystick.begin();
  Serial.begin(9600); // Inicializar el puerto serie para ver la posición en el Monitor Serie
}

void loop() {
  int potValue = analogRead(A0);
  int mappedValue = map(potValue, 0, 1023, 0, 100); // Mapear el valor a un rango de 0 a 100
  
  Joystick.setThrottle(mappedValue); // Enviar el valor mapeado al eje de "throttle" del Joystick

  Serial.println(mappedValue); // Mostrar el valor mapeado en el Monitor Serie
  delay(100); // Opcional: para evitar lecturas rápidas y estables del potenciómetro
}
