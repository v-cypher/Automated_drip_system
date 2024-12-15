#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "HTTPSRedirect.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <DHT.h>
#define DHTPIN D2


String readString;
const char* ssid = "JAIHO@9211";
const char* password = "Nextproject@9211";

const char* host = "script.google.com";
const char* GScriptId = "AKfycbzJpII0m-eIG2WQ38TFRKyaE0pq9b2ksWiUVlpymOBbeDTk_y0y";
const int httpsPort = 443;




String url = String("/macros/s/") + GScriptId + "/exec?value=Temperature";  // Write Teperature to Google Spreadsheet at cell A1
// Fetch Google Calendar events for 1 week ahead
String url2 = String("/macros/s/") + GScriptId + "/exec?cal";  // Write to Cell A continuosly

//replace with sheet name not with spreadsheet file name taken from google
String payload_base =  "{\"command\": \"appendRow\", \
                    \"sheet_name\": \"Sheet1\", \
                       \"values\": ";
String payload = "";
HTTPSRedirect* client = nullptr;


int sense_Pin = A0; // sensor input at Analog pin A0
int value = 0;

DHT dht(DHTPIN, DHT11);

int motor_pin = D0;
float moist;

//For time
const long utcOffsetInSeconds = 19800;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(motor_pin, OUTPUT);
  delay(2000);

  wifi_connect();
  connect_try();
  timeClient.begin();

}

void loop() {

  Serial.print(get_temperature());
  Serial.print(" : ");

  Serial.print(get_humidity());
  Serial.print(" : ");

  Serial.print(get_moisture());
  Serial.println("||");

  motor();

  send_data( get_temperature(), get_humidity(), get_moisture() );

  delay(2000);

  
}
