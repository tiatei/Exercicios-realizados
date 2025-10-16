#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <WebServer.h> // Include the WebServer library

// Create a WebServer object on port 80 (default HTTP port)
WebServer server(80);

// Function to get the MAC address as a String
String getMacAddressString() {
  uint8_t baseMac[6];
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
  if (ret == ESP_OK) {
    return String(baseMac[0], HEX) + ":" +
           String(baseMac[1], HEX) + ":" +
           String(baseMac[2], HEX) + ":" +
           String(baseMac[3], HEX) + ":" +
           String(baseMac[4], HEX) + ":" +
           String(baseMac[5], HEX);
  } else {
    return "Failed to read MAC address";
  }
}

// Handler for the root URL ("/")
void handleRoot() {
  String macAddress = getMacAddressString();
  String html = "<html><body>";
  html += "<h1>ESP32 MAC Address</h1>";
  html += "<p>The MAC address of this ESP32 is: <strong>" + macAddress + "</strong></p>";
  html += "</body></html>";
  server.send(200, "text/html", html); // Send the HTML response
}

void setup() {
  Serial.begin(115200);

  // Set the ESP32 to Wi-Fi station mode
  WiFi.mode(WIFI_STA);

  // IMPORTANT: Replace with your Wi-Fi credentials
  const char* ssid = "IEFP-Formacao";
  const char* password = "";

  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Register the root URL handler
  server.on("/", handleRoot);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); // Handle incoming client requests
}