import machine
import time

# Definisci i pin UART sul Raspberry Pi Pico
uart = machine.UART(0, baudrate=9600, tx=0, rx=1)  # UART0: tx=GPIO0 (Pin GP0), rx=GPIO1 (Pin GP1)

led = machine.Pin(25, machine.Pin.OUT)

led.value(1)  # Accendi il LED
time.sleep(2)
led.value(0)

while True:
    if uart.any():  # Controlla se ci sono dati disponibili sulla porta UART
        dataFromESP32 = uart.read().decode().strip()  # Leggi i dati ricevuti e decodificali come stringa
        print("Dati ricevuti dall'ESP32:", dataFromESP32)
        led.value(1)  # Accendi il LED
        time.sleep(0.1)
    led.value(0)  # Accendi il LED
    time.sleep(0.1)
    # Aggiungi qui il resto del tuo codice per il loop
