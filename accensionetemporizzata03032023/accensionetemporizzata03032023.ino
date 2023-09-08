int a=0;
int tempo;
const int LED_1=8, PULSANTE=7;

void setup() {
  Serial.begin(9600);//trasmette dati con il cavo USB
  pinMode (LED_1, OUTPUT);// inizializzo come output digitale 
  pinMode (PULSANTE, INPUT_PULLUP);
  
}

void loop() {
  int b=1;
  tempo=millis();

    while(digitalRead(PULSANTE)==0){

      if((millis()-tempo)>2000){
        if(a==1){
          a=0;
        }
        else{
          a=1;
        }
        digitalWrite(LED_1, a);
        delay(200);
        b=0;
      tempo=millis();
      }
        
    }
      
  }

 
  
 