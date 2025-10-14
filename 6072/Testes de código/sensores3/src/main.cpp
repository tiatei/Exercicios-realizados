#include <WiFi.h>
#include <Arduino.h>
#include <WebServer.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

// --- Credenciais Wi-Fi (agora como String) ---
const String meu_ssid = "NOS-03C0";          // Substitua pelo seu SSID Wi-Fi
const String minha_password = "NMKNTZWG"; // Substitua pela sua password Wi-Fi

// --- Credenciais de Autenticação para o Servidor Web ---
// Nome de utilizador e palavra-passe para aceder à página web
const String UTILIZADOR_WEB = "admin";
const String PASSWORD_WEB = "1234";

// --- Definição dos Pinos ---
// Use os números GPIO exatos da sua placa ESP32.
// Para LDR e Sensor de Som, escolha pinos ADC (Analógico-Digital Converter).
// Os GPIOs 32, 33, 34, 35, 36, 39 são entradas analógicas válidas.
#define PINO_LDR        35 // GPIO 35 (corresponde a A1 em algumas placas)
#define PINO_SENSOR_SOM 39 // GPIO 39 (corresponde a A3 em algumas placas)
#define PINO_DHT        4 // GPIO 4 (um pino digital seguro para o DHT)

// --- Tipo de Sensor DHT ---
#define TIPO_DHT DHT11      // Ou DHT22 se estiver a usar DHT22

// Inicializar o sensor DHT
DHT dht(PINO_DHT, TIPO_DHT);

// Criar objeto WebServer na porta 80
WebServer servidor_web(80);

// --- Variáveis globais para as leituras dos sensores ---
int valor_ldr = 0;
float temperatura_celsius = 0.0;
float humidade_percentagem = 0.0;
int valor_som = 0;

// --- DECLARAÇÕES DAS FUNÇÕES (Forward Declarations) ---
// Note que a função obterHTMLLeiturasSensores agora recebe os valores como parâmetros.
String obterHTMLLeiturasSensores(int ldr, float temp, float hum, int som);
void lidarComRaiz();
void lerDadosSensores();
void lidarComNaoEncontrado();

// --- CONTEÚDO HTML como uma String Multilinhas (Raw String Literal) ---
// Este é o TEMPLATE. Ele não é modificado diretamente.
// Adicionada a meta tag para refresh automático e um script para auto-click no botão
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

// Adiciona esta função para atualizar automaticamente a cada 5 segundos
window.onload = function() {
    setInterval(refreshPage, 5000); // 5000 milissegundos = 5 segundos
};
</script>
</head>
<body>
<div class='container'>
<h1>Dashboard de Sensores ESP32</h1>
<div class='sensor-data'>
<div class='card'><h2>LDR (Luz)</h2><p>%LDR_VALUE%</p></div>
<div class='card'><h2>Temperatura</h2><p>%TEMPERATURE_VALUE%&deg;C</p></div>
<div class='card'><h2>Humidade</h2><p>%HUMIDITY_VALUE%%</p></div>
<div class='card'><h2>Som (Anal&oacute;gico)</h2><p>%SOUND_VALUE%</p></div>
</div>
<p class='last-updated'>Última atualização: %UPTIME_SECONDS% segundos atrás</p>
<button class='refresh-button' onclick='refreshPage()'>Atualizar Dados</button>
</div>
</body>
</html>
)rawliteral";

// --- Função para Gerar o HTML com os Dados dos Sensores ---
String obterHTMLLeiturasSensores(int ldr, float temp, float hum, int som) {
  // Cria uma cópia mutável do template HTML para poder fazer as substituições.
  String htmlPagina = HTML_TEMPLATE;

  htmlPagina.replace("%LDR_VALUE%", String(ldr));
  htmlPagina.replace("%TEMPERATURE_VALUE%", String(temp, 1)); // 1 casa decimal
  htmlPagina.replace("%HUMIDITY_VALUE%", String(hum, 1));     // 1 casa decimal
  htmlPagina.replace("%SOUND_VALUE%", String(som));
  htmlPagina.replace("%UPTIME_SECONDS%", String(millis() / 1000)); // Tempo de funcionamento em segundos

  return htmlPagina;
}

// --- Lidar com o Pedido Principal (/) ---
void lidarComRaiz() {
  Serial.println("Pedido recebido para /"); // Mensagem de depuração

  // Verificar autenticação
  if (!servidor_web.authenticate(UTILIZADOR_WEB.c_str(), PASSWORD_WEB.c_str())) {
    Serial.println("Autenticação falhou ou não fornecida. A pedir credenciais."); // Mensagem de depuração
    return servidor_web.requestAuthentication(); // Envia o cabeçalho 401 Unauthorized e pede credenciais
  }

  // Este código só é executado se a autenticação for bem-sucedida
  Serial.println("Autenticação bem-sucedida."); // Mensagem de depuração
  lerDadosSensores(); // Ler os dados antes de enviar o HTML
  servidor_web.send(200, "text/html", obterHTMLLeiturasSensores(valor_ldr, temperatura_celsius, humidade_percentagem, valor_som));
  Serial.println("Página HTML enviada."); // Mensagem de depuração
}

// --- Lidar com Páginas Não Encontradas ---
void lidarComNaoEncontrado() {
  String mensagem = "Ficheiro Não Encontrado\n\n";
  mensagem += "URI: ";
  mensagem += servidor_web.uri();
  mensagem += "\nMétodo: ";
  mensagem += (servidor_web.method() == HTTP_GET) ? "GET" : "POST";
  mensagem += "\nArgumentos: ";
  mensagem += servidor_web.args();
  mensagem += "\n";
  for (uint8_t i = 0; i < servidor_web.args(); i++) {
    mensagem += " " + servidor_web.argName(i) + ": " + servidor_web.arg(i) + "\n";
  }
  servidor_web.send(404, "text/plain", mensagem);
}


// --- Ler Dados dos Sensores ---
void lerDadosSensores() {
  // Ler valor do LDR (0-4095 para ADC do ESP32)
  valor_ldr = analogRead(PINO_LDR);

  // Ler dados do sensor DHT11/DHT22
  humidade_percentagem = dht.readHumidity();
  temperatura_celsius = dht.readTemperature();

  // Verificar se alguma leitura falhou e sair cedo (para evitar valores NaN)
  if (isnan(humidade_percentagem) || isnan(temperatura_celsius)) {
    Serial.println("Falha ao ler do sensor DHT!");
    temperatura_celsius = 0.0; // Reiniciar para 0 ou valor anterior
    humidade_percentagem = 0.0;     // Reiniciar para 0 ou valor anterior
  }

  // Ler valor do Sensor de Som (analógico, 0-4095 para ADC do ESP32)
  valor_som = analogRead(PINO_SENSOR_SOM);
}

// --- Função Setup ---
void setup() {
  Serial.begin(115200);
  delay(10);

  // Inicializar o sensor DHT
  dht.begin();

  // Ligar ao Wi-Fi
  Serial.print("A ligar a ");
  Serial.println(meu_ssid);
  // WiFi.begin() espera const char*, por isso usamos .c_str() nas Strings.
  WiFi.begin(meu_ssid.c_str(), minha_password.c_str());
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 40) {
    delay(500);
    Serial.print(".");
    tentativas++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi ligado.");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());

    // Configurar rotas do servidor web
    servidor_web.on("/", lidarComRaiz);
    servidor_web.onNotFound(lidarComNaoEncontrado);

    // Iniciar servidor
    servidor_web.begin();
    Serial.println("Servidor HTTP iniciado.");
  } else {
    Serial.println("\nFalha ao ligar ao Wi-Fi. Por favor, verifique o seu SSID e password.");
    // Em caso de falha de conexão, pode querer reiniciar o ESP32 ou entrar num modo de recuperação.
    // ESP.restart(); // Pode adicionar isto se quiser que o ESP32 tente novamente
  }
}

// --- Função Loop ---
void loop() {
  servidor_web.handleClient(); // Lidar com pedidos de clientes recebidos
  // Pequeno atraso para manter o servidor responsivo
  delay(10);
}