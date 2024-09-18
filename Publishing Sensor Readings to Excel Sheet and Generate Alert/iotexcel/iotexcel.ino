#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "WarriorsWay_2G";
const char* password = "Success7183!";

String server = "http://maker.ifttt.com";
String eventName = "temp_data";
String IFTTT_Key = "jhfMDkoKf90e4RWyfbGwm4PuZwZCW5QzdlxABiwr7JH";
String IFTTTUrl="http://maker.ifttt.com/trigger/temp_data/with/key/jhfMDkoKf90e4RWyfbGwm4PuZwZCW5QzdlxABiwr7JH";

int value1;
int value2;

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi Connected !!!");
}


void sendDataToSheet(void)
{
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String((int)value1) + "&value2="+String((int)value2);  
  Serial.println(url);
  HTTPClient http;
  http.begin(url); //HTTP

  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();

}

void loop() {
  value1 = dht.readHumidity();
  value2 = dht.readTemperature();
  sendDataToSheet();
  Serial.print("Values are ");
  Serial.print(value1);
  Serial.print(' ');
  Serial.print(value2);
  Serial.print(' ');
 

  delay(10000);
}
