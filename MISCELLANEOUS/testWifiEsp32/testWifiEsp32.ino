#include <WiFi.h>

#define BLUE_LED_PIN 32
#define YELLOW_LED_PIN 33

const char* ssid = "Menchetti";
const char* password = "27021992";

const int ledPin = 13; // Pin a cui è collegato il LED

void setup() {
  Serial.begin(115200);

  // initialize digital pins as output.
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);

  pinMode(ledPin, OUTPUT);
  
  // Connessione alla rete WiFi
  Serial.println();
  Serial.print("Connessione a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connessione WiFi stabilita");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Se la connessione WiFi è stabilita, accendi il LED
    digitalWrite(BLUE_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
  } else {
    // Se la connessione WiFi è persa, spegni il LED
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
  }

  delay(1000); // Attendi 1 secondo
}
