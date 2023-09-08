int lum=A0,luminosita,led=5;
void setup() {
  Serial.begin(9600);
  pinMode (led, OUTPUT);
}

void loop() {
  luminosita=analogRead(lum);
  //luminosita=luminosita/4;
  luminosita=map(luminosita,0,1023,0,255);
  Serial.println(luminosita);
  analogWrite(led,luminosita);
  delay(10);

}
