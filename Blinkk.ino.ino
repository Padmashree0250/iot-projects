//declaration
int led = 6; //42
//setup
void setup() {
pinMode(led,OUTPUT);
}

//loop
void loop() {
digitalWrite(led, HIGH);
Serial.println("Led ON");
delay(2000);
digitalWrite(led, LOW);
Serial.println("Led OFF");
delay(2000);
}
