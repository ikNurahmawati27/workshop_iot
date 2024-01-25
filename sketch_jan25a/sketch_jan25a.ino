//ini untuk mengkur kelembaban air tanah dan temperatur serta hunmiditas udara
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
int M, sensor_analog;
const int sensor_pin = 32;
const char* ssid ="<klorofil>";
const char* password ="wooosshhh";
#define CHAT_ID "830339211"
#define BOTtoken "6727922965:AAGe44ogSwulfP0kJlLOneazpz1x3YOrwG4"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting Wifi:");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  while (WiFi.status() !=WL_CONNECTED){
    Serial.print(".");
  delay(500);
  }

  Serial.println(" ");
  Serial.println("Wifi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Tunggu dulu...monitoring akan segera dimulai","");

  delay(2000);
  Serial.print("Workshop Monitoring Tanaman SMKN 7 Blaeendah\n");
  dht.begin();
}
void loop() {
  sensor_analog = analogRead(sensor_pin);
  M = (100-((sensor_analog/4095.00)*100));
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(M)){
    Serial.println("Sensor tidak terbaca");
    return;
  }
  Serial.println("================MONITORING TANAMAN ================");
  Serial.print("Humiditas Gas udara :  ");
  Serial.print(h);
  Serial.println(" %");
  Serial.print("Temperatur lingkungan: ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.print("Kelembapan air tanah :  ");
  Serial.print(M);
  Serial.print(" %");
  delay(2000);
}
