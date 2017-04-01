#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

/* Node MCU pin mapping: 
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;
 */

const char* ssid = "james.residencia";
const char* password = "facada.2013";

int red = 5;
int green = 4;
int rele = 0;

ESP8266WebServer server(80);

void handleRoot() {
  digitalWrite(13, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(13, 0);
}

void handle_ON() {
  int pin = rele;
  if (server.args() > 0){
    pin = server.arg(0).toInt();  
  }
  digitalWrite(pin, HIGH);
  String message = server.arg(0);
  server.send(200, "text/plain", message);
}

  
void handle_OFF() {
  int pin = rele;
  if (server.args() > 0){
    pin = server.arg(0).toInt();
  }
  digitalWrite(pin, LOW);
  String message = server.arg(0);
  server.send(200, "text/plain", message);
}

void handleNotFound(){
  digitalWrite(13, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(13, 0);
}

void setup(void){
  pinMode(13, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH);
  digitalWrite(13, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/lights_on", handle_ON);
  server.on("/lights_off", handle_OFF);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
