#include <WiFi.h>

//DIAMO I DATI DEL WIFI CON LA PASSWORD
const char* ssid = "LABORATORI";
const char* password = "MITSLaboratori!";

// Creazione pagina web
WiFiServer server(80);

// Variable to store the HTTP request
String header;

String output32State = "off";
const int output32 = 32;

void setup() {
  Serial.begin(115200);

  pinMode(output32, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
   WiFiClient client = server.available();// attesa di comando

   if (client) {  

      String currentLine = "";

      while (client.connected()){

          if (client.available()) {             // if there's bytes to read from the client,
            char c = client.read();             // read a byte, then
            Serial.write(c);                    // print it out the serial monitor
            header += c;
            if (c == '\n') {                    // if the byte is a newline character
              // if the current line is blank, you got two newline characters in a row.
              // that's the end of the client HTTP request, so send a response:
              if (currentLine.length() == 0) {
                // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                // and a content-type so the client knows what's coming, then a blank line:
                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println("Connection: close");
                client.println();
                
                // turns the GPIOs on and off
                if (header.indexOf("GET /26/on") >= 0) {
                  Serial.println("GPIO 26 on");
                  output32State = "on";
                  digitalWrite(output32, HIGH);
                } else if (header.indexOf("GET /26/off") >= 0) {
                  Serial.println("GPIO 26 off");
                  output32State = "off";
                  digitalWrite(output32, LOW);
                } 
                
                // Display the HTML web page
                client.println("<!DOCTYPE html><html>");
                client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                client.println("<link rel=\"icon\" href=\"data:,\">");
                // CSS to style the on/off buttons 
                // Feel free to change the background-color and font-size attributes to fit your preferences
                client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
                client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                client.println(".button2 {background-color: #555555;}</style></head>");
                
                // Web Page Heading
                client.println("<body><h1>ESP32 Web Server</h1>");
                
                // Display current state, and ON/OFF buttons for GPIO 26  
                client.println("<p>GPIO 26 - State " + output32State + "</p>");
                // If the output26State is off, it displays the ON button       
                if (output32State=="off") {
                  client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
                } else {
                  client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
                } 
                  
                
                
                // The HTTP response ends with another blank line
                client.println();
                // Break out of the while loop
                break;
              } else { // if you got a newline, then clear currentLine
                currentLine = "";
              }
            } else if (c != '\r') {  // if you got anything else but a carriage return character,
              currentLine += c;      // add it to the end of the currentLine
            }
          }

      }
   }
}
