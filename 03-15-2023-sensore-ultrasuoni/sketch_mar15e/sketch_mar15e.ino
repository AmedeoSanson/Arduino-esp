const int trig=14, echo=15;
long distanza, durata;

void setup() {
  Serial.begin(9600);
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);  
}

void loop() {
  digitalWrite(trig, 0);
  digitalWrite(trig, 1);
  delayMicroseconds(10);
  digitalWrite(trig, 0);
  
  durata=pulseIn(echo,1);

  distanza=0.034*durata/2;

  Serial.println("distanza: ");
  
  if(durata>3800){
    Serial.println("Fora portata ");
  }
  else{
    Serial.println(distanza);
  }
  delay(300);
}
