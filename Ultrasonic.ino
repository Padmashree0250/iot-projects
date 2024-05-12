//Ultrasonic sensor
int trigPin = 7;
int echoPin = 8;
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  Serial.begin(9600); //Starts the serial communication
}

void loop() {
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  //Sets the trigPin on high state for 10 micro seconds
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  distance = duration*0.034/2;
  Serial.println("Distance: ");
  Serial.println(distance);
  delay(1000);
}
