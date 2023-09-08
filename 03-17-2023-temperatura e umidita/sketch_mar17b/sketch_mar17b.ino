#include <DHT.h>

DHT dht(7,DHT11);

void setup() {
  Serial.begin(9600);
  
}

void loop() {
 int temperatura=dht.readTemperature();
 int umidita=dht.readHumidity();

  Serial.println("la temperatura è:");
  Serial.println(temperatura );
  Serial.println("l'umidità è:");
  Serial.println(umidita);
  delay(3000);
}
