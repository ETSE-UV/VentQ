void publ(int co2, float temp, float hum){
  
  String payloads = "{";
  payloads += "\"co2\":\""; 
  payloads += co2;
  payloads += "\", \"temperature\":\"";
  payloads += temp;
  payloads += "\", \"humidity\":\"";
  payloads += hum;
  payloads += "\", \"vcc\":\"";
  payloads += analogRead(A0);
  payloads += "\", \"mac\":\"";
  payloads += mac;
  payloads += "\"}";

  String serverPath = "http://";
  serverPath += API_SERVER;
  serverPath += ":";
  serverPath += API_PORT;
  serverPath += API_PATH;

  http.begin(client, serverPath); //HTTP
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.PUT(payloads);
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      const String& payload = http.getString();
      Serial.println("received payload:\n<<");
      Serial.println(payload);
      Serial.println(">>");
    }
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}
