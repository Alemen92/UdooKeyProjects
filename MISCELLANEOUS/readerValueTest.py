import serial
import time

# Configurazione della porta seriale
# Assicurati di sostituire 'COM3' con la porta seriale corretta del tuo sistema
# Su Linux potrebbe essere qualcosa come '/dev/ttyUSB0'
serial_port = 'COM9'
baud_rate = 9600  # Deve essere lo stesso del baud rate impostato nel programma Arduino

# Funzione per aprire la connessione seriale
def open_serial(port, baud):
    while True:
        try:
            ser = serial.Serial(port, baud, timeout=1)
            print(f"Connessione seriale aperta su {port} a {baud} baud.")
            return ser
        except serial.SerialException:
            print(f"Porta {port} non disponibile. Tentativo di riconnessione in 5 secondi...")
            time.sleep(5)

# Funzione per leggere dalla porta seriale
def read_serial(ser):
    content = ""
    while True:
        try:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').rstrip()
                if line:
                    content += line + "\n"
                    print(line)  # Stampa il contenuto letto
                else:
                    break
        except serial.SerialException:
            print("Errore di lettura. Tentativo di riconnessione...")
            ser = open_serial(serial_port, baud_rate)
    return content

print("In attesa dei dati dal Raspberry Pi Pico...")

# Inizializza la connessione seriale
ser = open_serial(serial_port, baud_rate)

# Leggi il contenuto inviato dal Raspberry Pi Pico
try:
    while True:
        file_content = read_serial(ser)
        if file_content:
            # Salva il contenuto in un file locale
            with open("output_index.html", "w") as f:
                f.write(file_content)
            print("Contenuto salvato in output_index.html")
except KeyboardInterrupt:
    print("Interruzione da tastiera ricevuta. Chiusura del programma...")
finally:
    if ser.is_open:
        ser.close()
        print("Connessione seriale chiusa.")
