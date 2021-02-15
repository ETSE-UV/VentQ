#include "config.h"
#include <Arduino.h>
#include "MHZ19.h"
#include <SoftwareSerial.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266httpUpdate.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <ArduinoJson.h>
//#include "api_functions.hpp"
//#include "api_server.hpp"

#include "DHTesp.h"

#include <PubSubClient.h>


ESP8266WiFiMulti WiFiMulti;

MHZ19 myMHZ19;

WiFiClient client;
HTTPClient http;

DHTesp dht;

SoftwareSerial mySerial(RX_PIN, TX_PIN);

Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

unsigned long getDataTimer = 0;

float temperature = 0;
float humidity = 0;
int co2 = 0;

int counter = 0;

const int AnalogIn  = A0;
int readingIn = 0;

String mac="";

void setup()
{
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    #ifdef __DEBUG__
        Serial.println("OLED Screen not found");
    #endif
        while (true);
      }

    iniOLED();
    
    
    WiFi.mode(WIFI_STA);
    for (int i=0; i<WNN; i++){
      WiFiMulti.addAP(WSSID[i], WPWD[i]);
    }
  
    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");
  
    while (WiFiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
  
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  
    delay(500);
  
    firmUpdate();
    
    mac=WiFi.macAddress();  
    
    mySerial.begin(BAUDRATE);
    myMHZ19.begin(mySerial);

    myMHZ19.autoCalibration(false);

    dht.setup(DHT22_PIN, DHTesp::DHT22);

    pinMode(R_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);

    digitalWrite(R_PIN, LOW);
    digitalWrite(G_PIN, LOW);
    digitalWrite(B_PIN, LOW);

    InitServer();
    getDataTimer = millis();
}

void loop()
{
  if (millis() - getDataTimer >= ACT_FREC)
  {
    co2=getCO2();
    temperature=getTemp();
    humidity=getHum();
    readingIn = analogRead(AnalogIn);
    co2led(co2);
    publ(co2, temperature, humidity);
    infOLED(WiFi.localIP().toString(), WiFi.SSID(), co2, temperature, humidity);
    Serial.print("CO2: ");
    Serial.print(co2);
    Serial.print("ppm\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("º\t");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%\t");
    Serial.print("VCC: ");
    Serial.print(readingIn);
    Serial.print("V\t");
    Serial.println(" ");
    getDataTimer = millis();
    if (counter >= FIRM_CICLES){
      firmUpdate();
      counter=0;
    }
    counter=counter+1;
  }
}
