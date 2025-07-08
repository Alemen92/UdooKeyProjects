from machine import Pin
from time import sleep

# Definisci i pin di uscita per il motore stepper
IN1 = Pin(28, Pin.OUT)  # GP28
IN2 = Pin(27, Pin.OUT)  # GP27
IN3 = Pin(26, Pin.OUT)  # GP26
IN4 = Pin(22, Pin.OUT)  # GP22

# Configura il sensore MH
sensor_pin = Pin(20, Pin.IN)  # GP20

# Definisci la sequenza dei passi per il motore 28BYJ-48
step_sequence = [
    [1, 0, 0, 1],
    [1, 0, 0, 0],
    [1, 1, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 1],
    [0, 0, 0, 1]
]

#Stepper delay

step_delay = 0.001

# Parametri del motore
steps_per_revolution = 2038
lead = 4.0  # Passo della vite in mm
step_distance = lead / steps_per_revolution

# Funzione per muovere il motore stepper
def move_stepper(steps, delay=0.01):
    for _ in range(abs(steps)):
        for step in step_sequence:
            if steps > 0:  # Movimento in avanti
                set_step(*step)
            else:  # Movimento all'indietro
                set_step(*reversed(step))
            sleep(delay)
    stop_motor()

def set_step(w1, w2, w3, w4):
    IN1.value(w1)
    IN2.value(w2)
    IN3.value(w3)
    IN4.value(w4)

def stop_motor():
    IN1.value(0)
    IN2.value(0)
    IN3.value(0)
    IN4.value(0)

# Funzione per muovere il motore di un certo angolo
def move_stepper_by_angle(angle):
    steps = int((angle / 360.0) * steps_per_revolution)
    move_stepper(steps,delay=step_delay)

# Funzione per muovere il motore di una certa distanza
def move_stepper_by_distance(distance):
    steps = int(distance / step_distance)
    move_stepper(steps,delay=step_delay)

# Esempio di utilizzo nel loop principale
while True:
    if sensor_pin.value() == 1:
        stop_motor()
    else:
        print('Muovo 90 gradi')
        # Esempio: muovi di 90 gradi
        move_stepper_by_angle(90)
        sleep(1)
        
        print('Muovo 10mm')
        # Esempio: muovi di 10mm
        move_stepper_by_distance(10)
        sleep(1)


