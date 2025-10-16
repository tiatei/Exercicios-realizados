#include <WiFi.h>
#include <WebServer.h>

#include <Arduino.h>


void handleRoot();
// Replace with your network credentials
String ssid = "IEFP-Formacao";
String password = "";

// Assign output variables to GPIO pins


const int sensor = A1;
int valorsensor = 0;
int Update = 0;
// Create a web server object
WebServer server(80);




// Function to handle turning GPIO 26 off
void handleLeituraSensor() {
  //valorsensor = analogRead(sensor);
  int valorsensor = random(0, 100); // Simulate sensor reading
  handleRoot();
}






// Function to handle the root URL and show the current states
void handleRoot() {
  String pagina = R"rawliteral(
 <!DOCTYPE html>
<html lang="pt pt" >
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
      html {
        font-family: Helvetica;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }
      body {
        background-color: #2196f3; /* azul */
        background-size: cover ;
        background-repeat: no-repeat;
        background-position: center;
        background-color: #e3d7d7;
      }
      .button { background-color: #e54308; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}
      .button2 { background-color: #db0b0b; }
    </style>
</head>
<body>
    <h1>Leitura sensor</h1>
     <p>LDR: <span id="sensorValue">%SENSOR_VALUE%</span></p>
    
    </p>
</body>
</html>
  )rawliteral";
   pagina.replace("%SENSOR_VALUE%", String(valorsensor));
  server.send(200, "text/html", pagina);
}
void setup() {
  Serial.begin(115200);

  // Initialize the output variables as outputs
  pinMode(sensor, INPUT);
  
  

  // Connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up the web server to handle different routes
  server.on("/", handleRoot);
  server.on("/26/on", handleLeituraSensor);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  if(millis() - Update > 2000){
    valorsensor = random(0,100);
    
  }
  Update = millis();
 
  server.handleClient();
}