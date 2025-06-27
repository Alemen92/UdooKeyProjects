from machine import Pin
import time

# Pin del sensore IR
ir_sensor = Pin(15, Pin.IN)

# LED onboard del Pico
led = Pin(25, Pin.OUT)

while True:
    if ir_sensor.value() == 0:
        # Oggetto rilevato (linea scura o ostacolo vicino)
        print("Oggetto Rilevato!")
        led.value(1)
    else:
        # Nessun oggetto
        print("Nessun oggetto.")
        led.value(0)

    time.sleep(0.1)
