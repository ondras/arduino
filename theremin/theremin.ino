int trigPin = 7;
int echoPin = 8;
int buzzPin = 10;
int val;

void setup()
{
 Serial.begin (9600);
  pinMode(buzzPin, OUTPUT);  //set speaker pin to output
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
}

int getPing()
{
  //send a 10us pulse to wake up the sonar
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 return pulseIn(echoPin, HIGH);
}

void loop()
{
    val = 1000 - getPing() / 5;  //you can tune the pitch by dividing by a different number
  	//Serial.println(val);

    //generate the pulse
    tone(buzzPin, val);
    delay(5);

/*
    digitalWrite(buzzPin, HIGH);
    delayMicroseconds(val);
    digitalWrite(buzzPin, LOW);
    delayMicroseconds(val);
    */

}
