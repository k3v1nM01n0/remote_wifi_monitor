#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

const char* ssid = "wifi_name";
const char* password = "wifi_pass";

//Your domain name with url path or ip adress with path
const char* server_name = "http://192.168.0.1:4500/status";


void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.println("connecting..");

    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connection failed");      
    }
    Serial.println("Connected to WiFI:");
    delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
    if(WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        //your domain name with URL path or IP address with path
        http.begin(server_name);

        //Specifiy content-type header
        http.addHeader("Content-Type", "application/json");

        //Ping google and get the time it takes to return ping
        char buffer[256];
        int ping = Ping.ping("www.google.com");
        int ping_ms = Ping.averageTime();
        sprintf(buffer, "{\"p\":%d}", ping_ms);
        Serial.println(buffer);

        //Send HTTP POST request
        int httpResponceCode = http.POST((const uint8_t*)buffer, strlen(buffer));
        Serial.println("http responce code:");
        Serial.println(httpResponceCode);
        delay(60000);

        //Free resources
        http.end();

    }else {
        Serial.println("WiFi disconnected");
    }
 
}

