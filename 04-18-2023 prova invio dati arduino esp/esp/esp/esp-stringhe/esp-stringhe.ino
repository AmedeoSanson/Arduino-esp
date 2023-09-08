#include "./SOFT.h"


#define SOFTRX 0
#define SOFTTX 1
String teststr;

SoftwareSerial SerialS(SOFTRX, SOFTTX);
char v = 0;

void setup() {
  Serial.begin(115200);

  SerialS.begin(9600);
}

void loop() {
  if(v!='z')
  {
    if (Serial.available()){
    teststr = Serial.readString();
    teststr.trim();
    Serial.println(teststr);
    }
  }
  else
  {
    if (SerialS.available()){
      
    v=SerialS.read();
      if(v!='\n')
      {
        if(v!='\0')
        {
          Serial.println("bro lo arduino mi ha inviato questo carattere:");
          Serial.println(v);
        }
      }
    }
  }
}