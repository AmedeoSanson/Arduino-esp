//#include <TinyDHT.h>
#include "./DHT.h"

DHT dht(7,DHT11);

long int tempo;
const int LED_V=3, LED_R=5, BIP=6;
int puls1=8, puls2=2, cacca=0;
void setup() {
  Serial.begin(9600);
  pinMode (LED_V, OUTPUT);
  pinMode (LED_R, OUTPUT);
  pinMode (puls1, INPUT_PULLUP);
  pinMode (puls2, INPUT_PULLUP);
}

void loop() {
  int temperatura=dht.readTemperature();
 int umidita=dht.readHumidity();
 
 switch (cacca){

   case 0:
    analogWrite(LED_R,255);
    analogWrite(LED_V,0);

    if(digitalRead(puls1)==LOW)
      cacca=1;

    break;

  case 1:
    analogWrite(LED_R,0);
     analogWrite(LED_V,255);

    if(digitalRead(puls2)==LOW)
      cacca=2;

    break;

   case 2:
    Serial.println("la temperatura è calda :");
    Serial.println(temperatura );
    if(digitalRead(puls1)==LOW)
      cacca=1;
  
    if(temperatura>23){
    analogWrite(LED_R,255);
    analogWrite(LED_V,0);
    beep(600,300);
  }
    break;
 }
  

}

void beep(int note, int duration){
  tone(BIP,note,duration);
  delay(duration);
  noTone(BIP);
  delay(50);
}
