int a0, a1, a2, a3;

void setup() {
  Serial.begin(9600);
}

void loop() {
  a0 = analogRead(A0);
  Serial.print("A0 ");
  Serial.print(a0);
  Serial.print(" ");
  delay(500);

  a1 = analogRead(A1);
  Serial.print("A1 ");
  Serial.print(a1);
  Serial.print(" ");
  delay(500);

  a2 = analogRead(A2);
  Serial.print("A2 ");
  Serial.print(a2);
  Serial.print(" ");
  delay(500);

  a3 = analogRead(A3);
  Serial.print("A3 ");
  Serial.print(a3);
  Serial.print(" ");
  delay(500);

  Serial.println("");

  delay(3000);
}

