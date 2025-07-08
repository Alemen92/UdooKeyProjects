import socket
import time

# Imposta l'indirizzo IP e la porta del server ESP32
ESP32_IP = "192.168.1.204"  # Inserisci l'indirizzo IP del tuo ESP32
PORT = 80

def invia_comando(comando):
    try:
        # Crea un socket TCP/IP
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Connessione al server ESP32
        sock.connect((ESP32_IP, PORT))
        # Invia il comando al server
        sock.sendall(comando.encode())
        # Ricevi la risposta dal server
        data = sock.recv(1024)
        print("Risposta dal server:", data.decode())
    except Exception as e:
        print("Errore durante la comunicazione con il server:", e)
    finally:
        # Chiudi il socket
        sock.close()

if __name__ == "__main__":
    # Loop di esempio per inviare comandi al server ESP32
    while True:
        # Chiedi all'utente di inserire il comando
        comando = input("Inserisci 'accendi' per accendere il LED o 'spegni' per spegnere il LED: ")
        # Invia il comando al server ESP32
        invia_comando(comando)
        time.sleep(1)  # Attendi 1 secondo prima di inviare un nuovo comando
