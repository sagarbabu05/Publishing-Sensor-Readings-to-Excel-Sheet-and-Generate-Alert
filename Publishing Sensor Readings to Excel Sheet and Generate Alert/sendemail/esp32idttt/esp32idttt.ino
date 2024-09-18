#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4

//our sensor is DHT11 type
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


const char* ssid = "WarriorsWay_2G";
const char* password = "Success7183!";

String server = "http://maker.ifttt.com";
String eventName = "temp_data";
String eventNametemp30 = "temp_datatemp30";
String IFTTT_Key = "jhfMDkoKf90e4RWyfbGwm4PuZwZCW5QzdlxABiwr7JH";
String IFTTTUrl="http://maker.ifttt.com/trigger/temp_data/with/key/jhfMDkoKf90e4RWyfbGwm4PuZwZCW5QzdlxABiwr7JH";
//key for temp>30
String IFTTT_Keytemp30 = "jhfMDkoKf90e4RWyfbGwm4PuZwZCW5QzdlxABiwr7JH";
String IFTTTUrltemp30 ="http://maker.ifttt.com/trigger/temp_datatemp30/with/key/jhfMDkoKf90e4RWyfbGwm4PuZwZCW5QzdlxABiwr7JH";
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
  Serial.println(" Connected !!!");
}


void sendDataToSheet(void)
{
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String((int)value1) + "&value2="+String((int)value2);  
  Serial.println(url);
  //Start to send data to IFTTT
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
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
void sendDataToSheettemp30(void)
{
  String url = server + "/trigger/" + eventNametemp30 + "/with/key/" + IFTTT_Keytemp30 + "?value1=" + String((int)value1) + "&value2="+String((int)value2);  
  Serial.println(url);
  //Start to send data to IFTTT
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
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

if (value2 >29)
{
  sendDataToSheettemp30();
    sendDataToSheet();
    delay(30000);

}
else
{
  sendDataToSheet();
}
  Serial.print("Values are ");
  Serial.print(value1);
  Serial.print(' ');
  Serial.print(value2);
  Serial.print(' ');
 

  
  delay(30000);
}
