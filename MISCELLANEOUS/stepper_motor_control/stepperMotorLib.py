from machine import Pin
from time import sleep

class StepperMotor:
    def __init__(self, in1=28, in2=27, in3=26, in4=22, steps_per_revolution=2038, lead=4.0, delay=0.01):
        # Inizializza i pin
        self.IN1 = Pin(in1, Pin.OUT)
        self.IN2 = Pin(in2, Pin.OUT)
        self.IN3 = Pin(in3, Pin.OUT)
        self.IN4 = Pin(in4, Pin.OUT)
        
        # Parametri del motore
        self.steps_per_revolution = steps_per_revolution
        self.step_distance = lead / steps_per_revolution
        self.delay = delay

        # Sequenza dei passi
        self.step_sequence = [
            [1, 0, 0, 1],
            [1, 0, 0, 0],
            [1, 1, 0, 0],
            [0, 1, 0, 0],
            [0, 1, 1, 0],
            [0, 0, 1, 0],
            [0, 0, 1, 1],
            [0, 0, 0, 1]
        ]

    def set_step(self, w1, w2, w3, w4):
        # Imposta i pin del motore stepper
        self.IN1.value(w1)
        self.IN2.value(w2)
        self.IN3.value(w3)
        self.IN4.value(w4)

    def stop_motor(self):
        # Ferma il motore
        self.IN1.value(0)
        self.IN2.value(0)
        self.IN3.value(0)
        self.IN4.value(0)

    def move_stepper(self, steps):
        # Muove il motore di un numero specificato di passi
        for _ in range(abs(steps)):
            for step in self.step_sequence:
                if steps > 0:  # Movimento in avanti
                    self.set_step(*step)
                else:  # Movimento all'indietro
                    self.set_step(*reversed(step))
                sleep(self.delay)
        self.stop_motor()

    def move_by_angle(self, angle):
        # Muove il motore di un certo angolo (in gradi)
        steps = int((angle / 360.0) * self.steps_per_revolution)
        self.move_stepper(steps)

    def move_by_distance(self, distance):
        # Muove il motore di una certa distanza (in mm)
        steps = int(distance / self.step_distance)
        self.move_stepper(steps)


#Test movimento
angle_move_deg = 360
distance_move_mm = 5
stepper_revolution_setting = 510


#Ritardo step
delay_step = 0.001

# Esempio di utilizzo della classe StepperMotor
if __name__ == "__main__":
    # Inizializza il motore stepper
    stepper_motor = StepperMotor(steps_per_revolution=stepper_revolution_setting, delay=delay_step)
    
    try:
        while True:
            
            print(f'Angle move {angle_move_deg} degrees')            
            stepper_motor.move_by_angle(angle_move_deg)
            sleep(1)
            
            print(f'Distance move {distance_move_mm} millimeters')
            stepper_motor.move_by_distance(distance_move_mm)
            sleep(1)
            
            print(f'Movement {stepper_revolution_setting} steps')
            stepper_motor.move_stepper(stepper_revolution_setting)
            sleep(1)
    
    except KeyboardInterrupt:
        stepper_motor.stop_motor()
        print('Motore fermato dal programma')
