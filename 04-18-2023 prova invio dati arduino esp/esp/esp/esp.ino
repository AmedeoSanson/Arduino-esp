#include <SOFT.h>

#include <SoftwareSerial.h>

//#include <atomic.h>
//#include <crc16.h>
#include <delay_basic.h>


//#include "./SOFT.h"


#define SOFTRX 0
#define SOFTTX 1

SoftwareSerial_h SerialS(SOFTRX, SOFTTX);
char v = 0;

void setup() {
  Serial.begin(115200);

  SerialS.begin(9600);
}

void loop() {
  if(v!='z')
  {
    if (Serial.available()){
    v=Serial.read();
    Serial.println(v);
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