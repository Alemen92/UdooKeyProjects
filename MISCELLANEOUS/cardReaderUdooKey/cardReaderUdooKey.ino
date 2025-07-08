/*

VCC a 3.3V
GND a GND
CS a GP17
MOSI a GP19
MISO a GP16
SCK a GP18

*/


#include <SPI.h>
#include <SD.h>

// Definizione dei pin
const int chipSelect = 17;
const int ledPin = 25;

// Intervallo di trasmissione (in millisecondi)
const unsigned long interval = 5000;
unsigned long previousMillis = 0;

void setup() {
  // Impostazione del pin LED come output
  pinMode(ledPin, OUTPUT);

  // Accensione del LED per indicare l'inizio del programma
  digitalWrite(ledPin, HIGH);

  // Inizializza la comunicazione seriale
  Serial.begin(9600);

  // Inizializza la scheda SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Inizializzazione della scheda SD fallita!");
    // Spegni il LED in caso di errore
    digitalWrite(ledPin, LOW);
    return;
  }
  Serial.println("Scheda SD inizializzata.");

  // Spegni il LED dopo l'inizializzazione
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Ottieni il tempo corrente
  unsigned long currentMillis = millis();

  // Controlla se è ora di inviare di nuovo il file
  if (currentMillis - previousMillis >= interval) {
    // Salva l'ultimo tempo in cui abbiamo inviato il file
    previousMillis = currentMillis;

    // Accendi il LED per indicare che stiamo inviando il file
    digitalWrite(ledPin, HIGH);

    // Apri il file index.html
    File file = SD.open("index.txt");
    if (file) {
      Serial.println("Lettura del file index.txt:");

      // Leggi il file e stampa il contenuto
      while (file.available()) {
        Serial.write(file.read());
      }

      // Chiudi il file
      file.close();
    } else {
      Serial.println("Impossibile aprire il file index.txt");
    }

    // Spegni il LED dopo l'invio
    digitalWrite(ledPin, LOW);
  }
}
