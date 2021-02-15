void co2led(int co2){
  if (co2>CO2_HIGH){
    analogWrite(R_PIN, 500);
    analogWrite(G_PIN, 0);
    analogWrite(B_PIN, 0);
  }
  else if(co2<=CO2_HIGH && co2>CO2_MIDDLE){
    analogWrite(R_PIN, 500);
    analogWrite(G_PIN, 300);
    analogWrite(B_PIN, 0);
  }
  else{
    analogWrite(R_PIN, 0);
    analogWrite(G_PIN, 500);
    analogWrite(B_PIN, 0);
  }

}

void ledgreen(){
  digitalWrite(R_PIN, LOW);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(B_PIN, LOW);
}
void ledblue(){
  digitalWrite(R_PIN, LOW);
  digitalWrite(G_PIN, LOW);
  digitalWrite(B_PIN, HIGH);
}
void ledred(){
  digitalWrite(R_PIN, HIGH);
  digitalWrite(G_PIN, LOW);
  digitalWrite(B_PIN, LOW);
}
