/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

TaskHandle_t Task1;
TaskHandle_t Task2;


#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <HardwareSerial.h>
//#include <analogWrite.h>

const char* ssid = "Amedee";  // Inserisci il nome della tua rete Wi-Fi Uno squalo bianco MITS LABORATORI  Amedee  Sanson VodafoneMobileWiFi-DBAF07
const char* password = "amedef12";  // Inserisci la password della tua rete Wi-Fi Raffaele17 MiTsWiFi2020! MITSLaboratori!  amedef12  CurlyStar976 1377681970

//variaili Handle
String dataValue;
int ciccio;

//MOVIMENTO
char s;
const int dirPin = 13;   //senso orario
const int stepPin = 12;  //senso antioraio
const int en = 14;
int Speed = 0, speed2 = 0, a = 0;

//STERZO
const int dirPinS = 27;   //scegli il senso
const int stepPinS = 26;  //1 passo
const int EN = 25; //1=freno
const int servo = 33; //servo
int posizione = 0, posizione2 = 0,b=0,tem2=0;


WebServer server(80);  // Crea un oggetto server sulla porta 80

HardwareSerial SerialPort(2); // use UART2
#define WIFIok 2

void handleRoot() {
  // Questo gestore non è necessario nel tuo caso, puoi anche eliminarlo
  String html = "<html><body><h1>ESP32 Web Server</h1>";
  html += "<p><button onclick=\"sendData(1)\">Accendi LED</button></p>";
  html += "<p><button onclick=\"sendData(0)\">Spegni LED</button></p>";
  html += "<div id=\"response\"></div>";
  html += "<script>function sendData(val) {var xhttp = new XMLHttpRequest();xhttp.open(\"GET\", \"/\"+val, true);xhttp.send();xhttp.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"response\").innerHTML = this.responseText;}}}</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);  // invia la pagina HTML al client
}

void handleData() {\
  dataValue = server.arg("value");  // Ottieni il valore passato come parametro "value" nella richiesta
  //Serial.println("Valore in arrivo...");
  //Serial.println(dataValue);
  dataValue.trim();
  ciccio = atoi(dataValue.c_str());
  // Invia il valore seriale all'Arduino
  
  SerialPort.println("dataValue=" + dataValue);
  if(ciccio <= 100 && ciccio >= -100){
    motore(dataValue);
  }

  if(ciccio <= 400 && ciccio >= 200){
    sterzo(dataValue);
  }

  server.send(200, "text/plain", "Dato ricevuto");  // Invia una risposta di conferma al client
}

void setup() {
  Serial.begin(115200); 
 
   pinMode(WIFIok,OUTPUT);
  pinMode(WIFIok,LOW);
  WiFi.begin(ssid, password);  // Connessione alla rete Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {  // Attendi la connessione
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  pinMode(WIFIok,HIGH);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);  // Questo gestore non è necessario nel tuo caso, puoi anche eliminarlo
  server.on("/data", handleData);  // Gestione della richiesta per la ricezione dei dati

  server.begin();  // Avvio del server

  Serial.println("Server started");

  //motore principale avanti ed indietro
  pinMode(stepPin, OUTPUT);  // 1 passo
  pinMode(dirPin, OUTPUT);   // se alto gira in un senso se basso nell' altro

  pinMode(en, OUTPUT);     //setto l'enable come output
  digitalWrite(en, HIGH);  // lo imposto alto così blocco qialsiasi movimento

  //motore sterzo
  pinMode(dirPinS, OUTPUT);  // 1 passo
  pinMode(stepPinS, OUTPUT);   // se alto gira in un senso se basso nell' altro

  pinMode(EN, OUTPUT);     //setto l'enable come output
  digitalWrite(EN, HIGH);  // lo imposto alto così blocco qialsiasi movimentori
 
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore( Task1code,  "Task1",      10000, NULL,   1,   &Task1,   0);                     
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore( Task2code,"Task2",  10000,    NULL,    1,    &Task2,   1);      
    delay(500); 
}

//Task1code: MOVIMENTO
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID()); 

  for(;;){ 
    //server.handleClient();  // Gestione delle richieste dei client
    //Serial.println("bro sto eseguendo il programma motore");
    //MOTORE
    if(speed2!=0){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(speed2);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(speed2);
    }
    delay(1);  // resetto il watchdog timer
  } 
}

//Task2code: STERZO
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    server.handleClient();  // Gestione delle richieste dei client
    //Serial.println("bro sto eseguendo il programma sterzo");
    //STERZO
    analogWrite(servo, posizione);

    //analogServo(servo, posizione);

    delay(1);  // resetto il watchdog timer
  }
}

void loop() {
  
}

void motore(String data){
    
    data.trim();
    Speed = atoi(data.c_str());
    Serial.println(Speed);
    // coversione 1-100 a 1188 a 297
    if (Speed > 0) {
      Speed = 9 * (133 - Speed);
    } else if (Speed == 0) {
      digitalWrite(en, HIGH);
    } else {
      Speed = -9 * (133 + Speed);
    }
    Serial.print(Speed);

  if (297 <= Speed && Speed <= 1188) {
    if (a != 1) {
      Serial.println("vado avanti");
      a = 1;
    }
    digitalWrite(dirPin, LOW);  //Motore in direzione oraria
    digitalWrite(en, LOW);      //abilito il movimento del motore
    speed2 = Speed;
  } else if (-297 >= Speed && Speed >= -1188) {

    if (a != 2) {
      Serial.println("vado indietro");
      a = 2;
    }

    digitalWrite(dirPin, HIGH);  //Motore in direzione anti-oraria
    digitalWrite(en, LOW);       //abilito il movimento del motore
    speed2 = Speed * (-1);
  } else {

    digitalWrite(en, HIGH);
  } 
}

void sterzo(String data){
    
  data.trim();
  tem2 = atoi(data.c_str());
    
  posizione=map(tem2,200,400,90,210);
  Serial.println(posizione);
  
}
