#include "BdStepper.h"
#include <BdStepper.h>

long tempo,soldi=0, inporto ,prodotto=0, INSERITI=0;

const int LED_B=8, LED_V=3, LED_R=5, BIP=6; 

const int CENT10=2,CENT20=4,CENT50=7;

BdStepper motore(MEZZO_PASSO, 9,10,11,12);

void setup() {
  Serial.begin(9600);

  pinMode (LED_B, OUTPUT);
  pinMode (LED_V, OUTPUT);
  pinMode (LED_R, OUTPUT);

  pinMode (BIP, OUTPUT);

  pinMode (CENT10, INPUT_PULLUP);
  pinMode (CENT20, INPUT_PULLUP);
  pinMode (CENT50, INPUT_PULLUP);

  digitalWrite(LED_V, 1);
  digitalWrite(LED_R, 0);
  digitalWrite(LED_B, 0);

  Serial.println("MACCHINETTA DA AMEDEO ");
  Serial.println("I NOSTRI PRODOTTI SONO:");
  Serial.println("1) KINDER   70 CENT");
  Serial.println("2) FIESTA   90 CENT");
  Serial.println("3) GRESSINI 20 CENT");
  Serial.println("4) BIBITA   60 CENT");
}

void loop() {

  if(Serial.available()){

    prodotto=Serial.read();

    Serial.println("prodotto selezionato");
    
    switch (prodotto){
    case 49:
      inporto=70;
      Serial.println("importo 70 CENT");
      break;

    case 50:
      inporto=90;
      Serial.println("importo 90 CENT");
      break;

    case 51:
      inporto=20;
      Serial.println("importo 20 CENT");
      break;
    
    case 52:
      inporto=60;
      Serial.println("importo 60 CENT");
      break;
    }

    Serial.println("INSERIRE SOLDI");
    digitalWrite(LED_R, 1);

    while(inporto>soldi){

      if(digitalRead(CENT10)==LOW){
        
        soldi+=10;
        //INSERITI=INSERITI+soldi;
        Serial.println("HAI INSERITO 10 CENT");
        Serial.println("TOTALE");
        Serial.println(soldi);
        delay(200);
      }

      else if(digitalRead(CENT20)==LOW){
        
        soldi+=20;
        //INSERITI=soldi+INSERITI;
        Serial.println("HAI INSERITO 20 CENT");
        Serial.println("TOTALE");
        Serial.println(soldi);
        delay(200);
      }

      else if(digitalRead(CENT50)==LOW){
        
        soldi+=50;
        //INSERITI+=soldi;
        Serial.println("HAI INSERITO 50 CENT");
        Serial.println("TOTALE");
        Serial.println(soldi);
        delay(200);
      }

    }

    INSERITI=soldi-inporto;
    soldi=0;

    digitalWrite(LED_R, 0);
    digitalWrite(LED_V, 0);
    digitalWrite(LED_B, 1);
    Serial.println("SODLI SUFFICIENTI");
    Serial.println("EROGAZIONE IN CORSO....");

    
    motore.ruotaPerMillisecondi(2000, SENSO_ORARIO);
    digitalWrite(LED_B, 0);

    tempo=millis();
    Serial.println("RESTO");
    Serial.println(INSERITI);
    
    while((millis()-tempo)<3000){
      beep(600,300);
    }
    digitalWrite(LED_V, 1);

    Serial.println("MACCHINETTA DA AMEDEO ");
    Serial.println("I NOSTRI PRODOTTI SONO:");
    Serial.println("1) KINDER   70 CENT");
    Serial.println("2) FIESTA   90 CENT");
    Serial.println("3) GRESSINI 20 CENT");
    Serial.println("4) BIBITA   60 CENT");    
    
  }
  
}

void beep(int note, int duration){
  tone(BIP,note,duration);
  delay(duration);
  noTone(BIP);
  delay(50);
}