#include <WiFi.h>

#define BLUE_LED_PIN 32
#define YELLOW_LED_PIN 33

const char* ssid = "Menchetti";
const char* password = "27021992";
WiFiServer server(80); // Crea un server TCP sulla porta 80

void setup() {

  // initialize digital pins as output.
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  
  Serial.begin(115200);

  // Connessione alla rete Wi-Fi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione alla rete Wi-Fi in corso...");
  }

  Serial.println("Connesso alla rete Wi-Fi!");
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());

  server.begin(); // Inizia il server TCP
}

void loop() {
  // Accetta e gestisci le connessioni in arrivo
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("Nuova connessione in arrivo!");

    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println("Richiesta ricevuta: " + request);

        // Controlla il contenuto della richiesta per accendere/spegnere il LED
        if (request.indexOf("accendi") != -1) {
          digitalWrite(BLUE_LED_PIN, HIGH); // Accendi il LED
          client.println("LED acceso!");
        } else if (request.indexOf("spegni") != -1) {
          digitalWrite(BLUE_LED_PIN, LOW); // Spegni il LED
          client.println("LED spento!");
        }

        delay(10);
        client.stop(); // Chiudi la connessione
        Serial.println("Connessione chiusa.");
      }
    }
  }
}
