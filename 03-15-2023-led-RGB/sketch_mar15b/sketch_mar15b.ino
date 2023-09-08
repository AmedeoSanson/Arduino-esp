const int LED_B=6, LED_V=3, LED_R=5;
void setup() {
  Serial.begin(9600);
  pinMode (LED_B, OUTPUT);
  pinMode (LED_V, OUTPUT);
  pinMode (LED_R, OUTPUT);

}

void loop() {
  analogWrite(LED_B,0);
  analogWrite(LED_R,0);
  analogWrite(LED_V,0);
  for(int verd=0;verd<254;verd++){
    analogWrite(LED_V,verd);
    //delay(100);
    for(int blu=0;blu<254;blu++){
      analogWrite(LED_B,blu);
      //delay(10);
     for(int ros=0;ros<254;ros++){
        analogWrite(LED_R,ros);
        //delay(10);
      }
    }
  }
 
}
