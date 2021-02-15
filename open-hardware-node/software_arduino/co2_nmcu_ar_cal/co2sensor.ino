void readCO2(){
  int CO2; 

  CO2 = myMHZ19.getCO2();
  
  Serial.print("CO2 (ppm): ");                      
  Serial.println(CO2);                                

  int8_t Temp;
  Temp = myMHZ19.getTemperature();
  Serial.print("Temperature (C): ");                  
  Serial.println(Temp);
}

int getCO2(){
  int CO2; 
  CO2 = myMHZ19.getCO2();
  return CO2;
}
