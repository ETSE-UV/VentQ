void firmUpdate(){
  t_httpUpdate_return ret = ESPhttpUpdate.update(FIRM_SERVER, FIRM_PORT, FIRM_PATH, FIRM_VER);
  switch(ret) {
    case HTTP_UPDATE_FAILED:
        Serial.println("[update] Update failed.");
        break;
    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("[update] Update no Update.");
        break;
    case HTTP_UPDATE_OK:
        Serial.println("[update] Update ok."); // may not called we reboot the NodeMCU
        break;
  }
}
