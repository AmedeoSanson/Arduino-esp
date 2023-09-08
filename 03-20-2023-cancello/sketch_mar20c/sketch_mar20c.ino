#include <Servo.h>

Servo myservo;
int pos=0;

long int tempo;
const int LED_V=3, LED_R=5, BIP=6;
int puls1=7,cacca=0;

const int trig=14, echo=15;
long dis;

void setup() {
  Serial.begin(9600);
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);  

  pinMode (LED_V, OUTPUT);
  pinMode (LED_R, OUTPUT);

  pinMode (BIP, OUTPUT);

  pinMode (puls1, INPUT_PULLUP);

  myservo.attach(9);

}

void loop() {

switch (cacca){

   case 0:
    digitalWrite(LED_V,1);

    if(digitalRead(puls1)==LOW)
      cacca=1;

    break;

  case 1:

    for(pos=0; pos<180;pos++){
      myservo.write(pos);
      delay(75);
    }
    digitalWrite(LED_V,0);
    delay(1000);
    cacca=2;
    break;

   case 2:
    
    for(pos; pos>=0;pos--){
      do{
        dis=misura();
        digitalWrite(LED_R,1);
        digitalWrite(BIP,1);
      }while(dis<30);     
      
      myservo.write(pos);
      delay(75);
      digitalWrite(LED_R,0);
      digitalWrite(BIP,0);           
    }
    if(pos==0){
      cacca=0;
    }

    break;
 }}
 


long misura() {
  long distanza, durata;
    digitalWrite(trig, 0);
    digitalWrite(trig, 1);
    delayMicroseconds(10);
    digitalWrite(trig, 0);
    
    durata=pulseIn(echo,1);

    distanza=0.034*durata/2;
    return distanza;
  }
