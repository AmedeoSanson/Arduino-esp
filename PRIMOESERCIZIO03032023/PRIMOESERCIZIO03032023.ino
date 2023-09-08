int a=5;
const int LED_1=8, LED_2=7;

void setup() {
  Serial.begin(9600);//trasmette dati con il cavo USB
  pinMode (LED_1, OUTPUT);// inizializzo come output digitale 
  pinMode (LED_2, OUTPUT);
}

void loop() {
  Serial.print("Ciao da arduino\n ciao bro\n");//invia questa frase lungo il cavo USB

  digitalWrite(LED_1, 1);

  digitalWrite(LED_2, 1);
  delay(350);
  digitalWrite(LED_2, 0);
  //Serial.println(a);
 // a++;
  delay(350);

  digitalWrite(LED_1, 0);
  digitalWrite(LED_2, 1);
  delay(350);
  digitalWrite(LED_2, 0);
  delay(350);

  
  
  
  
}
