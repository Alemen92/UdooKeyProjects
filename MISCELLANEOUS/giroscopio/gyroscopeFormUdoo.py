import tkinter as tk
import random

class RealTimeDataApp(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("Real-Time Data Display")

        self.label_accel = tk.Label(self, text="Accel - x:0.00 y:0.00 z:0.00")
        self.label_gyro = tk.Label(self, text="Gyro - x:0.00 y:0.00 z:0.00")
        self.label_temp = tk.Label(self, text="Temp:0.00 °C")

        self.label_accel.pack(pady=5)
        self.label_gyro.pack(pady=5)
        self.label_temp.pack(pady=5)

        self.update_values()

    def update_values(self):
        # Simulazione di nuovi valori
        accel_x = round(random.uniform(-1, 1), 2)
        accel_y = round(random.uniform(-1, 1), 2)
        accel_z = round(random.uniform(-1, 1), 2)
        gyro_x = round(random.uniform(-1, 1), 2)
        gyro_y = round(random.uniform(-1, 1), 2)
        gyro_z = round(random.uniform(-1, 1), 2)
        temp = round(random.uniform(33, 35), 2)

        # Aggiorna le etichette con i nuovi valori
        self.label_accel.config(text=f"Accel - x:{accel_x} y:{accel_y} z:{accel_z}")
        self.label_gyro.config(text=f"Gyro - x:{gyro_x} y:{gyro_y} z:{gyro_z}")
        self.label_temp.config(text=f"Temp:{temp} °C")

        # Richiama la funzione ogni secondo (1000 millisecondi)
        self.after(1000, self.update_values)

if __name__ == "__main__":
    app = RealTimeDataApp()
    app.mainloop()
