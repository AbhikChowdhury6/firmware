unsigned long LstartMicro;
unsigned long currMicro;

int sampleNumber = 0;

int t = 0;
int prev1 = 0;
int prev2= 0;
int prev3 = 0;

int a1 = 0;
int a2 = 0;
int a3 = 0;

void setup() {
  Serial.begin(115200); 
  pinMode(13, OUTPUT);
}

void loop() {
  LstartMicro = micros();

  a1 = analogRead(A0);
  a2 = analogRead(A1);
  a3 = analogRead(A2);

  if (sampleNumber % 100 == 0){
    t = abs(a1 - prev1) + abs(a2 - prev2) + abs(a3 - prev3);
    if (t  > 100)
      digitalWrite(13,HIGH);
    else 
      digitalWrite(13,LOW);
    
    prev1 = a1;
    prev2 = a2;
    prev3 = a3;
  }
  

  

  // put your main code here, to run repeatedly:
  Serial.println("(" + String(a1) + "," + String(a2) + "," + String(a3) + ")");


  sampleNumber++;
  
  currMicro = micros();
  if (currMicro - LstartMicro >= 0) //protect from overflows
    delayMicroseconds(10 * 1000 - (currMicro - LstartMicro));
}
