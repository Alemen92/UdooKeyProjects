#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Menchetti";
const char* password = "27021992";

const int ledPin = 32; // Pin a cui è collegato il LED

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Inizialmente spegni il LED

  // Connessione alla rete Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione alla rete Wi-Fi in corso...");
  }

  Serial.println("Connesso alla rete Wi-Fi!");
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());

  // Configura le route per gestire le richieste HTTP
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", generateHtmlPage());
  });

  server.on("/accendi", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH); // Accendi il LED
    request->send(200, "text/plain", "LED acceso");
  });

  server.on("/spegni", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW); // Spegni il LED
    request->send(200, "text/plain", "LED spento");
  });

  server.begin();
  Serial.println("Server avviato!");
}

void loop() {
  // Il tuo codice per gestire altri compiti durante il funzionamento
}

String generateHtmlPage() {
  String htmlPage = "<!DOCTYPE html>\n";
  htmlPage += "<html>\n";
  htmlPage += "<head><title>Controllo LED</title></head>\n";
  htmlPage += "<body>\n";
  htmlPage += "<h1>Controllo LED</h1>\n";
  htmlPage += "<button onclick=\"accendiLed()\">Accendi LED</button>\n";
  htmlPage += "<button onclick=\"spegniLed()\">Spegni LED</button>\n";
  htmlPage += "<script>\n";
  htmlPage += "function accendiLed() {\n";
  htmlPage += "  fetch('/accendi')\n";
  htmlPage += "    .then(response => console.log('LED acceso'))\n";
  htmlPage += "    .catch(error => console.error('Errore accensione LED:', error));\n";
  htmlPage += "}\n";
  htmlPage += "function spegniLed() {\n";
  htmlPage += "  fetch('/spegni')\n";
  htmlPage += "    .then(response => console.log('LED spento'))\n";
  htmlPage += "    .catch(error => console.error('Errore spegnimento LED:', error));\n";
  htmlPage += "}\n";
  htmlPage += "</script>\n";
  htmlPage += "</body>\n";
  htmlPage += "</html>\n";

  return htmlPage;
}
