void setup() {
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(String(analogRead(A0)) + "\t" + String(analogRead(A1)) + "\t" + String(analogRead(A2)) + "\t" + String(analogRead(A3)));

  delay(200);
}
