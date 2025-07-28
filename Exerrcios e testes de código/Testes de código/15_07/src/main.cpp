#include <WiFi.h>
#include <Arduino.h>
#include <WebServer.h>

// --- Credenciais Wi-Fi ---
const String meu_ssid = "NOS-03C0";
const String minha_password = "NMKNTZWG";

// --- Credenciais de Autenticação para o Servidor Web ---
const String UTILIZADOR_WEB = "admin";
const String PASSWORD_WEB = "1234";

// --- Definição dos Pinos ---
#define PINO_LDR        35  // GPIO 35 (entrada analógica)
#define PINO_SENSOR_SOM 39  // GPIO 39 (entrada analógica)

// Criar objeto WebServer na porta 80
WebServer servidor_web(80);

// --- Variáveis globais para as leituras dos sensores ---
int valor_ldr = 0;
int valor_som = 0;

// --- Forward Declarations ---
String obterHTMLLeiturasSensores(int ldr, int som);
void lidarComRaiz();
void lerDadosSensores();
void lidarComNaoEncontrado();
int lerSomMedia(int pino, int amostras = 10);

// --- Template HTML ---
const char* HTML_TEMPLATE = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<meta charset='UTF-8'>
<title>Dados dos Sensores ESP32</title>
<style>
body { font-family: Arial, sans-serif; background-color: #f0f0f0; margin: 0; padding: 20px; color: #333; }
.container { max-width: 600px; margin: 20px auto; background-color: #fff; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); padding: 30px; }
h1 { text-align: center; color: #007bff; margin-bottom: 30px; }
.sensor-data { display: flex; flex-wrap: wrap; justify-content: space-around; gap: 20px; }
.card { flex: 1 1 200px; background-color: #e9ecef; border-radius: 6px; padding: 20px; text-align: center; min-width: 180px; }
.card h2 { color: #555; margin-top: 0; margin-bottom: 10px; font-size: 1.2em; }
.card p { font-size: 1.8em; font-weight: bold; color: #007bff; margin: 0; }
.last-updated { text-align: center; margin-top: 30px; font-size: 0.9em; color: #666; }
.refresh-button { display: block; width: 150px; margin: 20px auto; padding: 10px 15px; background-color: #28a745; color: white; border: none; border-radius: 5px; cursor: pointer; font-size: 1em; text-align: center; text-decoration: none; }
.refresh-button:hover { background-color: #218838; }
@media (max-width: 480px) { .sensor-data { flex-direction: column; } .card { flex-basis: auto; } }
</style>
<script>
function refreshPage() { location.reload(); }
window.onload = function() {
    setInterval(refreshPage, 1000); // Atualiza a cada 1 segundo
};
</script>
</head>
<body>
<div class='container'>
<h1>Dashboard de Sensores ESP32</h1>
<div class='sensor-data'>
<div class='card'><h2>LDR (Luz)</h2><p>%LDR_VALUE%</p></div>
<div class='card'><h2>Som (Anal&oacute;gico)</h2><p>%SOUND_VALUE%</p></div>
</div>
<p class='last-updated'>Última atualização: %UPTIME_SECONDS% segundos atrás</p>
</div>
</body>
</html>
)rawliteral";

// --- Função para Gerar HTML com os Dados ---
String obterHTMLLeiturasSensores(int ldr, int som) {
  String htmlPagina = HTML_TEMPLATE;
  htmlPagina.replace("%LDR_VALUE%", String(ldr));
  htmlPagina.replace("%SOUND_VALUE%", String(som));
  htmlPagina.replace("%UPTIME_SECONDS%", String(millis() / 1000));
  return htmlPagina;
}

// --- Leitura Média do Sensor de Som ---
int lerSomMedia(int pino, int amostras) {
  long soma = 0;
  for (int i = 0; i < amostras; i++) {
    soma += analogRead(pino);
    delay(5);
  }
  int media = soma / amostras;
  return map(media, 0, 4095, 0, 100);
}

// --- Lê os Dados dos Sensores ---
void lerDadosSensores() {
  valor_ldr = analogRead(PINO_LDR);
  valor_som = lerSomMedia(PINO_SENSOR_SOM, 10);
}

// --- Página Principal ---
void lidarComRaiz() {
  if (!servidor_web.authenticate(UTILIZADOR_WEB.c_str(), PASSWORD_WEB.c_str())) {
    return servidor_web.requestAuthentication();
  }

  lerDadosSensores();
  servidor_web.send(200, "text/html", obterHTMLLeiturasSensores(valor_ldr, valor_som));
}

// --- Página 404 ---
void lidarComNaoEncontrado() {
  String mensagem = "Ficheiro Não Encontrado\n\n";
  mensagem += "URI: ";
  mensagem += servidor_web.uri();
  mensagem += "\nMétodo: ";
  mensagem += (servidor_web.method() == HTTP_GET) ? "GET" : "POST";
  mensagem += "\nArgumentos: ";
  mensagem += servidor_web.args();
  for (uint8_t i = 0; i < servidor_web.args(); i++) {
    mensagem += " " + servidor_web.argName(i) + ": " + servidor_web.arg(i) + "\n";
  }
  servidor_web.send(404, "text/plain", mensagem);
}

// --- Setup ---
void setup() {
  // Serial.begin(115200); // REMOVIDO
  delay(10);

  pinMode(PINO_LDR, INPUT);
  pinMode(PINO_SENSOR_SOM, INPUT);

  WiFi.begin(meu_ssid.c_str(), minha_password.c_str());
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 40) {
    delay(500);
    tentativas++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    servidor_web.on("/", lidarComRaiz);
    servidor_web.onNotFound(lidarComNaoEncontrado);
    servidor_web.begin();
  }
}

// --- Loop ---
void loop() {
  servidor_web.handleClient();
  delay(10);
}
