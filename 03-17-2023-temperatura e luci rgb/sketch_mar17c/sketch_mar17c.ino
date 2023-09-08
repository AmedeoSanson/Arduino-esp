#include <DHT.h>

DHT dht(7,DHT11);

const int LED_B=6, LED_V=3, LED_R=5;

void setup() {
  Serial.begin(9600);
  pinMode (LED_B, OUTPUT);
  pinMode (LED_V, OUTPUT);
  pinMode (LED_R, OUTPUT);
}

void loop() {
  int temperatura=dht.readTemperature();
 int umidita=dht.readHumidity();

  Serial.println("la temperatura è:");
  Serial.println(temperatura );
  
  delay(1000);
  analogWrite(LED_B,255);
  analogWrite(LED_R,255);
  analogWrite(LED_V,255);
  if(temperatura>24){
    Serial.println("la temperatura è calda :");
  Serial.println(temperatura );
  analogWrite(LED_R,0);
  delay(1000);
  }
  else if(temperatura>20){
    Serial.println("la temperatura è media :");
  Serial.println(temperatura );
    analogWrite(LED_R,10);
    analogWrite(LED_V,0);
    delay(1000);
  }
  else if(temperatura>18){
    Serial.println("la temperatura è fredda :");
  Serial.println(temperatura );
    analogWrite(LED_V,0);
    delay(1000);
  }

}
