#include <HardwareSerial.h>

#define BLUE_LED_PIN 32
#define YELLOW_LED_PIN 33

// Definisci la velocità di comunicazione UART
#define UART_BAUD_RATE 9600

void setup() {
  Serial.begin(UART_BAUD_RATE); // Inizia la comunicazione seriale

  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) { // Controlla se ci sono dati disponibili sulla porta seriale
    String dataFromRaspberry = Serial.readString(); // Leggi i dati ricevuti dalla porta seriale
    Serial.print("Dati ricevuti dall'Raspberry Pi Pico: ");
    Serial.println(dataFromRaspberry); // Stampa i dati ricevuti sulla porta seriale di debug
    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(100);
  }
  // Aggiungi qui il resto del tuo codice per il loop
  digitalWrite(BLUE_LED_PIN, LOW);
  delay(100);
}
