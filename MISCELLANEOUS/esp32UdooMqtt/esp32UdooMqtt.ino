#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <PubSubClient.h>

#define BLUE_LED_PIN 32
#define YELLOW_LED_PIN 33

const char* ssid = "Menchetti";
const char* password = "27021992";
const char* mqtt_server = "indirizzo_del_broker_mqtt";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione alla rete Wi-Fi in corso...");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Messaggio ricevuto su topic: ");
  Serial.println(topic);

  // Decodifica il messaggio
  if (payload[0] == '1') {
    // Accendi il LED
    digitalWrite(BLUE_LED_PIN, HIGH);
  } else if (payload[0] == '0') {
    // Spegni il LED
    digitalWrite(BLUE_LED_PIN, LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connessione al broker MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connesso al broker MQTT!");
      client.subscribe("mqtt_topic");  // Sostituisci con il tuo topic MQTT
    } else {
      Serial.print("Errore di connessione, rc=");
      Serial.print(client.state());
      Serial.println(" Riprovo tra 5 secondi...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  // initialize digital pins as output.
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
