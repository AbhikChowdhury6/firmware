int b0 = 4;
int b1 = 5;
int b2 = 6;
int b3 = 7;
int EN = 3;
int PWR = 2;
int a = A0;

int a1;
int a2;
int a3;
int a4;
int a5;
int a6;
int a7;
int a8;
int a9;
int a10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(PWR, OUTPUT);
  Serial.println("Start");
  Serial.println("1\t2\t3\t4\t5\t6\t7\t8\t9\t10");

}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(b0, HIGH);digitalWrite(b1, LOW);digitalWrite(b2, LOW);digitalWrite(b3, LOW);//1
  a1 = analogRead(a);
  Serial.print(a1);
  Serial.print("\t");

  digitalWrite(b0, LOW);digitalWrite(b1, HIGH);digitalWrite(b2, LOW);digitalWrite(b3, LOW);//2
  a2 = analogRead(a);
  Serial.print(a2);
  Serial.print("\t");

  digitalWrite(b0, HIGH);digitalWrite(b1, HIGH);digitalWrite(b2, LOW);digitalWrite(b3, LOW);//3
  a3 = analogRead(a);
  Serial.print(a3);
  Serial.print("\t");

  digitalWrite(b0, LOW);digitalWrite(b1, LOW);digitalWrite(b2, HIGH);digitalWrite(b3, LOW);//4
  a4 = analogRead(a);
  Serial.print(a4);
  Serial.print("\t");

  digitalWrite(b0, HIGH);digitalWrite(b1, LOW);digitalWrite(b2, HIGH);digitalWrite(b3, LOW);//5
  a5 = analogRead(a);
  Serial.print(a5);
  Serial.print("\t");

  digitalWrite(b0, LOW);digitalWrite(b1, HIGH);digitalWrite(b2, HIGH);digitalWrite(b3, LOW);//6
  a6 = analogRead(a);
  Serial.print(a6);
  Serial.print("\t");

  digitalWrite(b0, HIGH);digitalWrite(b1, HIGH);digitalWrite(b2, HIGH);digitalWrite(b3, LOW);//7
  a7 = analogRead(a);
  Serial.print(a7);
  Serial.print("\t");

  digitalWrite(b0, LOW);digitalWrite(b1, LOW);digitalWrite(b2, LOW);digitalWrite(b3, HIGH);//8
  a8 = analogRead(a);
  Serial.print(a8);
  Serial.print("\t");

  digitalWrite(b0, HIGH);digitalWrite(b1, LOW);digitalWrite(b2, LOW);digitalWrite(b3, HIGH);//9
  a9 = analogRead(a);
  Serial.print(a9);
  Serial.print("\t");

  digitalWrite(b0, LOW);digitalWrite(b1, HIGH);digitalWrite(b2, LOW);digitalWrite(b3, HIGH);//10
  a10 = analogRead(a);
  Serial.print(a10);
  Serial.print("\t");

  Serial.print(a1+a2+a3+a4+a5+a6+a7+a8+a9+10);
  Serial.print("\n");
  delay(10);
}
