byte in[9];

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.println("Started!");

}

void loop() {
  
  if (Serial.available() > 0) {
    Serial.readBytes(in,9); // read the incoming bytes:
    Serial.println("gotem");
    Serial.println(in[0]);
    Serial.println(in[1]);
    Serial.println(in[2]);
    Serial.println(in[3]);
    Serial.println(in[4]);
    Serial.println(in[5]);
    Serial.println(in[6]);
    Serial.println(in[7]);
  }
  if (in[0] == '1')
    digitalWrite(2, HIGH);
  if (in[1] == '1')
    digitalWrite(3, HIGH);
  if (in[2] == '1')
    digitalWrite(4, HIGH);
  if (in[3] == '1')
    digitalWrite(5, HIGH);
  if (in[4] == '1')
    digitalWrite(6, HIGH);
  if (in[5] == '1')
    digitalWrite(7, HIGH);
  if (in[6] == '1')
    digitalWrite(8, HIGH);
  if (in[7] == '1')
    digitalWrite(9, HIGH);
  
  
  delay(4);
//  delayMicroseconds(500);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  
  
  delay(4);
//  delayMicroseconds(500);

}
