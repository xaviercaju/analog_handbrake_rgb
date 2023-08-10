import serial

ser = serial.Serial('COM13', 9600)  # Reemplaza 'COMX' con el puerto serie correcto
min_value = 1023
max_value = 0

while True:
    try:
        value = int(ser.readline().decode().strip())
        if value < min_value:
            min_value = value
        if value > max_value:
            max_value = value
        print(f"Value: {value} | Min: {min_value} | Max: {max_value}")
    except KeyboardInterrupt:
        break

ser.close()
