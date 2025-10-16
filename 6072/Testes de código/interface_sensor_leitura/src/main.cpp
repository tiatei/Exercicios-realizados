#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
void handleRoot();
// Replace with your network credentials
String ssid = "IEFP-Formacao";
String password = "";

// Assign output variables to GPIO pins


const int sensor = A1;
int valorsensor = 0;
// Create a web server object
WebServer server(80);




// Function to handle turning GPIO 26 off
void handleLeituraSensor() {
  valorsensor = analogRead(sensor);
  
  handleRoot();
}






// Function to handle the root URL and show the current states
void handleRoot() {
  String pagina = R"rawtype(
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
      margin: 0;km
      padding: 0;
     
    }
    .sensor-box {
      background: #fff;
      border: 2px solid #e54308;
      border-radius: 8px;
      display: inline-block;
      padding: 20px 40px;
      font-size: 28px;
      margin-top: 40px;
      box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    }
  </style>
</head>
<body>
  <h1>Leituras de Sensor</h1>
  <div class="sensor-box" id="sensorLeitura">
    Leitura do sensor: <span id="valorSensor">---</span>
  </div>
  <script>
    // Gera valores falsos de leitura do sensor a cada 2 segundos
    function gerarLeituraFalsa() {
      const valor = (Math.random() * 100).toFixed(2); // valor entre 0 e 100
      document.getElementById('valorSensor').textContent = valor;
    }
    setInterval(gerarLeituraFalsa, 2000); // atualiza a cada 2 segundos
    gerarLeituraFalsa(); // primeira leitura imediata
  </script>
</body>
</html>)rawtype";

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
  

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}