void iniOLED(){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(23, 5);
    display.println("NodeMCU");
    display.setCursor(47, 25);
    display.println("CO");
    display.setTextSize(1);
    display.setCursor(71, 25);
    display.print("2");
    display.setTextSize(2);
    display.setCursor(29, 41);
    display.println("Sensor");
    display.display();
}

void infOLED(String ip, String ssid, int co2, float temp, float hum){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("IP: ");
    display.print(ip);
    display.setCursor(0, 9);
    display.print("SSID: ");
    display.print(ssid);
    display.setTextSize(2);
    display.setCursor(0, 18);
    display.print(co2);
    display.print("ppm");
    display.setCursor(0, 34);
    display.print(temp);display.print((char)247);display.print("C  ");
    display.setCursor(0, 50);
    display.print(hum);display.print("%");
    display.display();
}

void updOLED(){
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(0, 18);
    display.print("Updating");
    display.setCursor(0, 34);
    display.print("Firmware");
    display.setCursor(0, 50);
    display.print(".....");
    display.display();
}
