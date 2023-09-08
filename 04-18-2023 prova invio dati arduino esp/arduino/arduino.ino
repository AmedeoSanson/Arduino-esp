#include <SoftwareSerial.h>

#define SOFTRX 0
#define SOFTTX 1
const int LED_B=4, LED_R=7;
SoftwareSerial SerialS(SOFTRX, SOFTTX);
char v = 0;
void setup() {  
  pinMode(SOFTTX, OUTPUT);
  pinMode(SOFTRX, INPUT);
 pinMode (LED_B, OUTPUT);
  pinMode (LED_R, OUTPUT);

  digitalWrite(LED_R, 0);
  digitalWrite(LED_B, 0);
  
  Serial.begin(9600);
  Serial.println("Pronto a ricevere da arduino 1");
  
  SerialS.begin(115200);
}

void loop() {
  if(v!='z')
  {
    if (SerialS.available()){
      
      v=SerialS.read();
      if(v!='\n')
      {
        if(v!='\0')
        {
          Serial.println("bro lo esp mi ha inviato questo carattere:");
          Serial.println(v);
        }
        
      }
      

      switch (v){
      case '1':
        digitalWrite(LED_R, 0);
        digitalWrite(LED_B, 1);
        Serial.println("blu acceso");
        break;

      case '2':
        digitalWrite(LED_R, 1);
        digitalWrite(LED_B, 0);
        Serial.println("rosso acceso ");
        break;

      case '3':
        digitalWrite(LED_R, 1);
        digitalWrite(LED_B, 1);
        Serial.println("entrambi accesi");
        break;
      
      case '4':
      digitalWrite(LED_R, 0);
        digitalWrite(LED_B, 0); 
        Serial.println("spengo i led");
        break;
      }
    }
  }
  else
  {
    if (Serial.available()){
    v=Serial.read();
    Serial.println(v);
    }
  }
}