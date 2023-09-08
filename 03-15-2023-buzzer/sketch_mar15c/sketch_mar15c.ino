long int tempo;
const int LED_G=8, LED_V=3, LED_R=5, BIP=6;
void setup() {
  Serial.begin(9600);
  pinMode (LED_G, OUTPUT);
  pinMode (LED_V, OUTPUT);
  pinMode (LED_R, OUTPUT);
  pinMode (BIP, OUTPUT);
}

void loop() {
  digitalWrite(LED_V, 1);
  digitalWrite(LED_R, 0);
  digitalWrite(LED_G, 0);
  tempo=millis();
 
  while((millis()-tempo)<3000){
   beep(600,300);
  }
   
    digitalWrite(LED_V, 0);
    digitalWrite(LED_G, 1);
    tempo=millis();
    
  while((millis()-tempo)<2000){
   beep(800,200);
  }
        
    digitalWrite(LED_R, 1);
    digitalWrite(LED_G, 0);
    tempo=millis();
    
  while((millis()-tempo)<4000){
   beep(440,500);
  }      
   
  digitalWrite(LED_V, 0);
  digitalWrite(LED_R, 0);
  digitalWrite(LED_G, 0);
}

void beep(int note, int duration){
  tone(BIP,note,duration);
  delay(duration);
  noTone(BIP);
  delay(50);
}