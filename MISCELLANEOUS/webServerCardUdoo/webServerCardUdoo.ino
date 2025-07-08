#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SD.h>
#include <SPI.h>

// Credenziali WiFi
const char* ssid = "Menchetti";
const char* password = "27021992";

// Pin del lettore SD
const int ledPin = 32; // Pin a cui è collegato il LED
const int CS_PIN = 10; // GPIO15 per chip select

// Creazione del server
AsyncWebServer server(80);

// Path del file HTML sulla SD card
const char* filePath = "index.txt";

void setup() {
  Serial.begin(115200);

  // Configura il LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connessione alla rete WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione alla rete WiFi in corso...");
  }
  Serial.println("Connesso alla rete WiFi!");
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());

  // Configura i pin SPI
  SPI.begin(9, 7, 8, 10); // SCK, MISO, MOSI, CS

  // Attendi un momento prima di inizializzare la scheda SD
  delay(2000);

  // Inizializzazione della scheda SD
  if (!SD.begin(CS_PIN)) {
    Serial.println("Errore nell'inizializzazione della scheda SD!");
    return;
  }
  Serial.println("Scheda SD inizializzata.");

  // Route principale per servire la pagina HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    File file = SD.open(filePath);
    if (!file) {
      request->send(500, "text/plain", "Errore nell'aprire il file HTML!");
      return;
    }
    String html = "";
    while (file.available()) {
      html += char(file.read());
    }
    file.close();
    request->send(200, "text/html", html);
  });

  // Route per accendere il LED
  server.on("/accendi", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH); // Accendi il LED
    request->send(200, "text/plain", "LED acceso");
  });

  // Route per spegnere il LED
  server.on("/spegni", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW); // Spegni il LED
    request->send(200, "text/plain", "LED spento");
  });

  // Avvia il server
  server.begin();
  Serial.println("Server avviato!");
}

void loop() {
  // Il tuo codice per gestire altri compiti durante il funzionamento
}
