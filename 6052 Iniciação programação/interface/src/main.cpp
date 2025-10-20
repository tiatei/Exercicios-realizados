#include <WiFi.h>
#include <WebServer.h>
void handleRoot();
// Replace with your network credentials
String ssid = "IEFP-Formacao";
String password = "";

// Assign output variables to GPIO pins
const int output26 = D9;
const int output27 = D10;
String output26State = "off";
String output27State = "off";

// Create a web server object
WebServer server(80);

// Function to handle turning GPIO 26 on
void handleGPIO26On() {
  output26State = "on";
  digitalWrite(output26, HIGH);
  handleRoot();
}

// Function to handle turning GPIO 26 off
void handleGPIO26Off() {
  output26State = "off";
  digitalWrite(output26, LOW);
  handleRoot();
}

// Function to handle turning GPIO 27 on
void handleGPIO27On() {
  output27State = "on";
  digitalWrite(output27, HIGH);
  handleRoot();
}

// Function to handle turning GPIO 27 off
void handleGPIO27Off() {
  output27State = "off";
  digitalWrite(output27, LOW);
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
      background-image: url('images.jfif');
      background-size: cover ;
      background-repeat: no-repeat;
      background-position: center; 
      background-color: #e3d7d7;
    }
    .button { background-color: #e54308; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}
    .button2 { background-color: #db0b0b; }
  </style>
  <script>
    function sendRequest(url) {
      fetch(url)
        .then(response => location.reload());
    }
  </script>
</head>
<body>
  <h1>PDyddi</h1>
  <p>Justin </p>
  <p>
    <button class="button" onclick="sendRequest('/26/on')">Sim</button>
  </p>
  <p>Crianças</p>
  <p>
    <button class="button" onclick="sendRequest('/27/on')">Sim</button>
  </p>
</body>
</html>
  )rawliteral";
  server.send(200, "text/html", pagina);
}

void setup() {
  Serial.begin(115200);

  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);

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
  server.on("/26/on", handleGPIO26On);
  server.on("/26/off", handleGPIO26Off);
  server.on("/27/on", handleGPIO27On);
  server.on("/27/off", handleGPIO27Off);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}