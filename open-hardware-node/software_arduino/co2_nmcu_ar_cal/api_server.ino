AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void InitServer()
{
  server.on("/led", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, postled);
  server.on("/autocal", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, autoCal);
  server.on("/zerocal", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, zeroCal);
  server.on("/info", HTTP_GET, getInfo);
  server.on("/sinfo", HTTP_GET, getSInfo);
  server.on("/cinfo", HTTP_GET, getCInfo);
  
  server.onNotFound(notFound);

  server.begin();
    Serial.println("HTTP server started");
}
