const int sensore=14;

void setup() {
  Serial.begin(9600);

}

void loop() {
  int Pote=analogRead(sensore);
  Serial.println(Pote);
  delay(500);

}
