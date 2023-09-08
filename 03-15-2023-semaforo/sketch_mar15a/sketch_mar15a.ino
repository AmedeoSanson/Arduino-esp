long int tempo;
const int LED_V=8, LED_G=7,LED_R=6;


void setup() {
  Serial.begin(9600);//trasmette dati con il cavo USB
  pinMode (LED_R, OUTPUT);// inizializzo come output digitale 
  pinMode (LED_G, OUTPUT);
  pinMode (LED_V, OUTPUT);
  //pinMode (PULSANTE, INPUT_PULLUP); //input digitale
  
}

void loop() {

  digitalWrite(LED_V, 1);
  digitalWrite(LED_R, 0);
  digitalWrite(LED_G, 0);
  tempo=millis();
  Serial.println(tempo);
  Serial.println("prima stazione");
  while((millis()-tempo)<3000){
  
  }
   
    digitalWrite(LED_V, 0);
    digitalWrite(LED_G, 1);
    tempo=millis();
    Serial.println(tempo);
    Serial.println("seconda stazione");
  while((millis()-tempo)<2000){
  
  }
        
    digitalWrite(LED_R, 1);
    digitalWrite(LED_G, 0);
    tempo=millis();
    Serial.println(tempo);
    Serial.println("terza stazione");
  while((millis()-tempo)<4000){
  
  }      
   
  digitalWrite(LED_V, 0);
  digitalWrite(LED_R, 0);
  digitalWrite(LED_G, 0);

  Serial.println(tempo);
  Serial.println("quarta stazione");
}
