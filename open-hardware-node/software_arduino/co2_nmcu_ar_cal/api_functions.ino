
void postled(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total){
  String bodyContent = GetBodyContent(data, len);
  Serial.println(bodyContent);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error) { request->send(400); return;}

  String red_data = doc["red"];
  String green_data = doc["green"];
  String blue_data = doc["blue"];
  
  request->send(200, "text/plain", "OK");
  
  analogWrite(R_PIN, red_data.toInt());
  analogWrite(G_PIN, green_data.toInt());
  analogWrite(B_PIN, blue_data.toInt());
  
}

void getInfo(AsyncWebServerRequest *request)
{
  String payloads = "{";
  payloads += "\"ChipID\":\""; 
  payloads += ESP.getFlashChipId();
  payloads += "\", \"ChipRealSize\":\""; 
  payloads += ESP.getFlashChipRealSize();
  payloads += "\", \"ChipSize\":\""; 
  payloads += ESP.getFlashChipSize();
  payloads += "\", \"ChipSpeed\":\""; 
  payloads += ESP.getFlashChipSpeed();
  payloads += "\", \"ChipMode\":\""; 
  payloads += ESP.getFlashChipMode();
  payloads += "\", \"VCC\":\""; 
  payloads += ESP.getVcc();
  payloads += "\", \"ResetReason\":\""; 
  payloads += ESP.getResetReason();
  payloads += "\", \"FreeHeap\":\""; 
  payloads += ESP.getFreeHeap();
  payloads += "\", \"HeapFragmentation\":\""; 
  payloads += ESP.getHeapFragmentation();
  payloads += "\", \"CoreVersion\":\""; 
  payloads += ESP.getCoreVersion();
  payloads += "\", \"SdkVersion\":\""; 
  payloads += ESP.getSdkVersion();
  payloads += "\", \"CPUFreq\":\""; 
  payloads += ESP.getCpuFreqMHz();
  payloads += "\", \"SketchSize\":\""; 
  payloads += ESP.getSketchSize();
  payloads += "\", \"SketchMD5\":\""; 
  payloads += ESP.getSketchMD5();
  payloads += "\", \"CycleCount\":\""; 
  payloads += ESP.getCycleCount();
  payloads += "\"}";

  Serial.println(payloads);
  request->send(200, "application/json", payloads);
}

void getSInfo(AsyncWebServerRequest *request)
{
  String mess;
  myMHZ19.getABC() ? mess="ON" :  mess="OFF";
  String payloads = "{";
  payloads += "\"MH-Z19 CO2\":\""; 
  payloads += getCO2();
  payloads += "\", \"DHT22 Temperature\":\"";
  payloads += getTemp();
  payloads += "\", \"DHT22 Humidity\":\"";
  payloads += getHum();
  payloads += "\", \"MH-Z19 Autocalibration\":\"";
  payloads += mess;
  payloads += "\", \"MH-Z19 Temperature\":\"";
  payloads += myMHZ19.getTemperature();
  payloads += "\"}";

  Serial.println(payloads);
  request->send(200, "application/json", payloads);
}

void getCInfo(AsyncWebServerRequest *request)
{
  String mess;
  myMHZ19.getABC() ? mess="ON" :  mess="OFF";
  String payloads = "{";
  payloads += "\"MAC\":\""; 
  payloads += WiFi.macAddress();
  payloads += "\", \"IP\":\""; 
  payloads += WiFi.localIP().toString();
  payloads += "\", \"Connected SSID\":\""; 
  payloads += WiFi.SSID();
  for (int i=0; i<WNN; i++){
    payloads += "\", \"Configured SSID ";
    payloads += i;
    payloads += "\":\""; 
    payloads += WSSID[i];
    payloads += "\", \"Configured Pass ";
    payloads += i;
    payloads += "\":\""; 
    payloads += WPWD[i];
  }
  payloads += "\"}";

  Serial.println(payloads);
  request->send(200, "application/json", payloads);
}

void autoCal(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total){
  String bodyContent = GetBodyContent(data, len);
  Serial.println(bodyContent);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error) { request->send(400); return;}

  int autocal = doc["auto"];
  String mess;
  
  if(autocal==1){
    myMHZ19.autoCalibration(true);
  }
  else if (autocal==0){
    myMHZ19.autoCalibration(false);
  }
  myMHZ19.getABC() ? mess="Auto Calibration ON" :  mess="Auto Calibration OFF";
  request->send(200, "text/plain", mess);
  
}

void zeroCal(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total){
  String bodyContent = GetBodyContent(data, len);
  Serial.println(bodyContent);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error) { request->send(400); return;}

  String mess="Zero Calibration";
  
  myMHZ19.calibrate();
  request->send(200, "text/plain", mess);
  
}
