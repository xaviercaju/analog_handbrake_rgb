import serial
import time

ser = serial.Serial('COM13', 9600)  # Cambia 'COM3' al puerto serie correcto

print("Realiza la calibración del potenciómetro...")
input("Presiona Enter cuando estés listo para comenzar la calibración.")

min_value = 1023
max_value = 0

duration = 10  # Duración de la calibración en segundos

start_time = time.time()

while time.time() - start_time < duration:
    value = int(ser.readline().strip())
    if value < min_value:
        min_value = value
    if value > max_value:
        max_value = value

ser.close()

print("Calibración completada.")
print(f"Valor mínimo: {min_value}")
print(f"Valor máximo: {max_value}")
