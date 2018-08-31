void setup() {
  pinMode(1, OUTPUT); //LED on Model A   
}

void loop() {
  digitalWrite(1, HIGH);
  delay(1000);               // wait for a second
  digitalWrite(1, LOW); 
  delay(1000);               // wait for a second
}

