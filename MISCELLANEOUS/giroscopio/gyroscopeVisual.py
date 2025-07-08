import tkinter as tk
import serial
import threading

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

        # Apre la connessione seriale
        self.serial_port = serial.Serial('COM7', 115200)

        # Avvia un thread per leggere continuamente i dati seriali
        self.read_thread = threading.Thread(target=self.read_serial)
        self.read_thread.daemon = True
        self.read_thread.start()

    def read_serial(self):
        while True:
            if self.serial_port.in_waiting > 0:
                line = self.serial_port.readline().decode().strip()
                if line.startswith("Accel") and "Gyro" in line and "Temp" in line:
                    # Estrae i valori da stringa
                    values = line.split()
                    print(values)
                    accel_vals = values[2:5]
                    gyro_vals = values[7:10]
                    temp_val = values[10]

                    # Aggiorna le etichette con i nuovi valori
                    self.label_accel.config(text=f"Accel - x:{accel_vals[0]} y:{accel_vals[1]} z:{accel_vals[2]}")
                    self.label_gyro.config(text=f"Gyro - x:{gyro_vals[0]} y:{gyro_vals[1]} z:{gyro_vals[2]}")
                    self.label_temp.config(text=f"Temp:{temp_val} °C")

    def on_closing(self):
        # Chiude la porta seriale quando l'applicazione viene chiusa
        if self.serial_port.is_open:
            self.serial_port.close()
        self.destroy()

if __name__ == "__main__":
    app = RealTimeDataApp()
    app.protocol("WM_DELETE_WINDOW", app.on_closing)
    app.mainloop()
