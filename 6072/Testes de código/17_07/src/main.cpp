#include <WiFi.h>
#include <Arduino.h>
#include <WebServer.h>
#include <vector>

// --- Credenciais Wi-Fi ---
const String meu_ssid = "NOS-03C0";
const String minha_password = "NMKNTZWG";

// --- Credenciais de Autenticação para o Servidor Web ---
const String UTILIZADOR_WEB = "admin";
const String PASSWORD_WEB = "1234";

// --- Definição dos Pinos ---
#define PINO_LDR 35

// Criar objeto WebServer na porta 80
WebServer servidor_web(80);

// --- Variáveis globais para as leituras do sensor ---
int valor_ldr = 0;

// --- Histórico das leituras ---
const int MAX_HISTORICO = 10;
std::vector<int> historico_ldr;

// --- Limiares para detecção de luminosidade (LÓGICA INVERTIDA - PERSONALIZADA) ---
const int LIMIAR_NOITE_PERSONALIZADO = 50;
const int LIMIAR_POUCA_LUZ_PERSONALIZADO = 150;

// --- Variáveis para controle de tempo com millis() ---
unsigned long lastReadTime = 0;
const long readInterval = 2000; // Intervalo de leitura do sensor (2 segundos)

// --- Variáveis para controle de tentativas de conexão WiFi ---
unsigned long wifiConnectAttemptStartTime = 0;
const long WIFI_CHECK_TIMEOUT = 15000; // Tempo máximo para verificar conexão WiFi em cada tentativa (15 segundos)
const long WIFI_RETRY_DELAY = 3000;    // Espera antes de uma nova tentativa de conexão WiFi
int wifi_retry_count = 0;
const int MAX_WIFI_RETRIES = 10;

// --- Nova variável para controlar a leitura do sensor ---
bool sensorReadingsEnabled = true; // Começa ativo por padrão

// --- Forward Declarations ---
String obterHTMLLeiturasSensores(int ldr);
void lidarComRaiz();
void lerDadosSensores();
void lidarComNaoEncontrado();
String obterIconeLuminosidade(int valorLDR);
String obterHistoricoHTML();
void lidarComToggleSensor();

// --- Template HTML ---
const char* HTML_TEMPLATE = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<meta charset='UTF-8'>
<title>Sensor de Luminosidade</title>
<style>
body {
  font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
  background: linear-gradient(to right, #4facfe, #00f2fe); /* Gradiente de azul claro */
  margin: 0;
  padding: 20px;
  color: #333;
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 100vh; /* Ocupa a altura total da viewport */
}
.container {
  max-width: 800px;
  width: 90%; /* Responsivo */
  background-color: #ffffff;
  border-radius: 15px;
  box-shadow: 0 10px 30px rgba(0,0,0,0.2); /* Sombra mais pronunciada */
  padding: 30px 40px;
  box-sizing: border-box; /* Inclui padding na largura total */
}
h1 {
  text-align: center;
  color: #2c3e50; /* Azul escuro */
  margin-bottom: 30px;
  font-size: 2.5em;
  text-shadow: 1px 1px 2px rgba(0,0,0,0.1);
}
.sensor-data {
  display: flex;
  flex-wrap: wrap;
  justify-content: center; /* Centraliza o card */
  gap: 25px;
  margin-bottom: 35px;
}
.card {
  flex: 1 1 280px; /* Mais largura para o card principal */
  background: linear-gradient(to right, #6dd5ed, #2193b0); /* Gradiente azul para o card */
  border-radius: 12px;
  padding: 25px;
  text-align: center;
  min-width: 250px;
  position: relative;
  box-shadow: 0 5px 15px rgba(0,0,0,0.15);
  color: white; /* Texto branco no card */
}
.card h2 {
  color: #e0f7fa; /* Azul claro */
  margin-top: 0;
  margin-bottom: 12px;
  font-size: 1.5em;
}
.card p {
  font-size: 2.5em; /* Valor maior */
  font-weight: bold;
  color: #ffffff;
  margin: 0;
}
.icon {
  font-size: 4em; /* Ícone maior */
  margin-bottom: 15px;
  display: block; /* Para centralizar melhor */
  text-shadow: 2px 2px 5px rgba(0,0,0,0.3);
}
.button-container {
  text-align: center;
  margin-top: 25px;
  margin-bottom: 35px;
}
.button {
  padding: 12px 25px;
  font-size: 1.3em;
  font-weight: bold;
  border-radius: 8px; /* Cantos mais arredondados */
  cursor: pointer;
  border: none;
  color: white;
  margin: 0 15px;
  min-width: 120px;
  transition: all 0.3s ease; /* Transição suave ao passar o mouse */
  box-shadow: 0 4px 10px rgba(0,0,0,0.15);
}
.button.on {
  background: linear-gradient(to right, #28a745, #218838); /* Gradiente verde */
}
.button.on:hover {
  background: linear-gradient(to right, #218838, #1e7e34);
  transform: translateY(-2px); /* Efeito de elevação */
}
.button.off {
  background: linear-gradient(to right, #dc3545, #c82333); /* Gradiente vermelho */
}
.button.off:hover {
  background: linear-gradient(to right, #c82333, #bd2130);
  transform: translateY(-2px); /* Efeito de elevação */
}
.history-box {
  background-color: #f8f9fa;
  border: 1px solid #dee2e6;
  border-radius: 10px;
  padding: 20px;
  margin-top: 30px;
  max-height: 220px; /* Um pouco mais alto */
  overflow-y: auto;
  box-shadow: inset 0 2px 5px rgba(0,0,0,0.05); /* Sombra interna */
}
.history-box h2 {
  color: #495057;
  margin-top: 0;
  margin-bottom: 15px;
  font-size: 1.3em;
  text-align: center;
  border-bottom: 1px solid #e9ecef;
  padding-bottom: 10px;
}
.history-item {
  padding: 8px 0;
  border-bottom: 1px dashed #e9ecef;
  font-size: 1.1em;
  color: #555;
}
.history-item:last-child {
  border-bottom: none;
}
.footer {
  text-align: right;
  margin-top: 40px;
  font-size: 0.9em;
  color: #6c757d;
  border-top: 1px solid #e9ecef;
  padding-top: 15px;
}
</style>
<script>
let sensorStatus = %SENSOR_STATUS%; // true para ON, false para OFF

function refreshPage() { location.reload(); }

function toggleSensor(action) {
  const xhr = new XMLHttpRequest();
  xhr.open('GET', '/toggleSensor?state=' + action, true);
  xhr.onload = function() {
    if (xhr.status === 200) {
      console.log('Comando enviado: ' + action);
      sensorStatus = (action === 'on');
    } else {
      console.error('Erro ao enviar comando: ' + xhr.status);
    }
  };
  xhr.send();
}

window.onload = function() {
    setInterval(refreshPage, 2000); // Atualiza a cada 2 segundos
};
</script>
</head>
<body>
<div class='container'>
<h1>Sensor de Luminosidade</h1>
<div class='sensor-data'>
<div class='card'><h2>Leitura Atual do LDR</h2><p>%LDR_ICON% %LDR_VALUE%</p></div>
</div>

<div class='button-container'>
  <button class='button on' onclick="toggleSensor('on')">ON</button>
  <button class='button off' onclick="toggleSensor('off')">OFF</button>
</div>

<div class='history-box'>
<h2>Últimas 10 Leituras</h2>
%HISTORY_DATA%
</div>

<div class='footer'>
<p>Tiago Teixeira</p>
<p>TEAC 6052</p>
</div>

</div>
</body>
</html>
)rawliteral";

// --- Função para Gerar HTML com os Dados ---
String obterHTMLLeiturasSensores(int ldr) {
  String htmlPagina = HTML_TEMPLATE;
  htmlPagina.replace("%LDR_VALUE%", String(ldr));
  htmlPagina.replace("%LDR_ICON%", obterIconeLuminosidade(ldr));
  htmlPagina.replace("%HISTORY_DATA%", obterHistoricoHTML());
  htmlPagina.replace("%SENSOR_STATUS%", sensorReadingsEnabled ? "true" : "false"); // Passa o estado atual para o JS
  return htmlPagina;
}

// --- Lê os Dados do Sensor e Armazena no Histórico ---
void lerDadosSensores() {
  // Apenas lê e armazena se as leituras estiverem ativadas
  if (sensorReadingsEnabled) {
    valor_ldr = analogRead(PINO_LDR);

    // Adiciona ao histórico, removendo o mais antigo se exceder o limite
    historico_ldr.insert(historico_ldr.begin(), valor_ldr);

    if (historico_ldr.size() > MAX_HISTORICO) {
      historico_ldr.pop_back();
    }
  } else {
    // Se as leituras estiverem desativadas, o valor exibido será 0 (ou outro valor de sua escolha)
    // Para que o display não fique "parado" na última leitura quando desativado
    valor_ldr = 0; // Ou um valor que indique "desativado", como -1
  }
}

// --- Obtém o ícone de luminosidade (LÓGICA INVERTIDA - PERSONALIZADA) ---
String obterIconeLuminosidade(int valorLDR) {
  if (!sensorReadingsEnabled) {
    return "<span class='icon'>&#10060;</span>"; // Ícone de 'X' ou 'parado'
  }
  if (valorLDR <= LIMIAR_NOITE_PERSONALIZADO) {
    return "<span class='icon'>&#127769;</span>"; // Lua
  } else if (valorLDR > LIMIAR_NOITE_PERSONALIZADO && valorLDR <= LIMIAR_POUCA_LUZ_PERSONALIZADO) {
    return "<span class='icon'>&#127773;</span>"; // Sol (sem raios / nublado)
  } else { // valorLDR > LIMIAR_POUCA_LUZ_PERSONALIZADO
    return "<span class='icon'>&#127774;</span>"; // Sol (com raios)
  }
}

// --- Gera o HTML para as últimas leituras em parágrafos (Sem Destaque) ---
String obterHistoricoHTML() {
  String historicoHTML = "";
  if (!sensorReadingsEnabled) {
    historicoHTML += "<p class='history-item'>Leituras do sensor desativadas.</p>";
  } else {
    for (size_t i = 0; i < historico_ldr.size(); i++) {
      historicoHTML += "<p class='history-item'>Leitura: " + String(historico_ldr[i]) + "</p>";
    }
  }
  return historicoHTML;
}

// --- Lida com a requisição de ligar/desligar o sensor ---
void lidarComToggleSensor() {
  if (!servidor_web.authenticate(UTILIZADOR_WEB.c_str(), PASSWORD_WEB.c_str())) {
    return servidor_web.requestAuthentication();
  }

  String state = servidor_web.arg("state");
  if (state == "on") {
    sensorReadingsEnabled = true;
    Serial.println("Leituras do sensor ATIVADAS.");
  } else if (state == "off") {
    sensorReadingsEnabled = false;
    Serial.println("Leituras do sensor DESATIVADAS.");
    valor_ldr = 0; // Opcional: Resetar o valor LDR para 0 quando desativado
  }
  servidor_web.send(200, "text/plain", "OK");
}


// --- Página Principal ---
void lidarComRaiz() {
  if (!servidor_web.authenticate(UTILIZADOR_WEB.c_str(), PASSWORD_WEB.c_str())) {
    return servidor_web.requestAuthentication();
  }
  servidor_web.send(200, "text/html", obterHTMLLeiturasSensores(valor_ldr));
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

// --- Sinaliza se o servidor web já foi iniciado ---
bool webServerStarted = false;

// --- Setup ---
void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando Sensor de Luminosidade...");

  pinMode(PINO_LDR, INPUT);

  // Iniciar a primeira tentativa de conexão WiFi
  Serial.print("A tentar conectar ao WiFi (tentativa 1 de ");
  Serial.print(MAX_WIFI_RETRIES);
  Serial.print("): ");
  WiFi.begin(meu_ssid.c_str(), minha_password.c_str());
  wifiConnectAttemptStartTime = millis(); // Guarda o tempo de início da tentativa
}

// --- Loop ---
void loop() {
  unsigned long currentMillis = millis();

  // --- Lógica de Conexão WiFi (não-bloqueante) ---
  if (WiFi.status() != WL_CONNECTED) {
    // Se o servidor web já estava ligado e perdeu a conexão, resetar a flag
    if (webServerStarted) {
        Serial.println("\nWiFi desconectado. A tentar reconectar...");
        webServerStarted = false; // Resetar para tentar iniciar o servidor novamente após a reconexão
        wifi_retry_count = 0; // Resetar contador de tentativas
        wifiConnectAttemptStartTime = currentMillis; // Iniciar nova contagem para reconexão
        WiFi.begin(meu_ssid.c_str(), minha_password.c_str()); // Tentar reconectar
    }

    if (wifi_retry_count < MAX_WIFI_RETRIES) {
      // Se ainda não se conectou e está dentro do tempo limite para esta tentativa
      if (currentMillis - wifiConnectAttemptStartTime < WIFI_CHECK_TIMEOUT) {
        // Continuar a imprimir pontos a cada segundo para feedback
        // Evita imprimir múltiplos pontos no mesmo milissegundo se o loop for muito rápido
        if (currentMillis / 1000 != (currentMillis - 1) / 1000) {
            Serial.print(".");
        }
      } else {
        // Tempo limite para esta tentativa excedido, tentar novamente
        Serial.println("\nFalha na tentativa. SSID/Password errados ou sinal fraco. Esperando para tentar novamente...");
        wifi_retry_count++;
        if (wifi_retry_count < MAX_WIFI_RETRIES) {
          wifiConnectAttemptStartTime = currentMillis + WIFI_RETRY_DELAY;
          Serial.print("A tentar conectar ao WiFi (tentativa ");
          Serial.print(wifi_retry_count + 1);
          Serial.print(" de ");
          Serial.print(MAX_WIFI_RETRIES);
          Serial.print("): ");
          WiFi.begin(meu_ssid.c_str(), minha_password.c_str()); // Reinicia a conexão
        } else {
          Serial.println("\n*************************************************************");
          Serial.println("Falha crítica: Não foi possível conectar ao WiFi após múltiplas tentativas.");
          Serial.println("Por favor, verifique as credenciais ('meu_ssid', 'minha_password') ou a rede.");
          Serial.println("O servidor web não será iniciado.");
          Serial.println("*************************************************************");
        }
      }
    }
  } else {
    // WiFi está conectado
    if (!webServerStarted) { // Inicia o servidor web apenas uma vez
      Serial.println("\nWiFi conectado com sucesso!");
      Serial.print("Endereço IP: ");
      Serial.println(WiFi.localIP());

      servidor_web.on("/", lidarComRaiz);
      servidor_web.on("/toggleSensor", lidarComToggleSensor);
      servidor_web.onNotFound(lidarComNaoEncontrado);
      servidor_web.begin();
      Serial.println("Servidor Web iniciado.");
      webServerStarted = true; // Marca que o servidor foi iniciado
    }
    servidor_web.handleClient(); // Lida com as requisições do cliente
  }

  // --- Lógica de Leitura do Sensor (não-bloqueante) ---
  // Apenas lê e armazena se o servidor web já estiver a funcionar
  if (webServerStarted && (currentMillis - lastReadTime >= readInterval)) {
    lastReadTime = currentMillis; // Atualiza o tempo da última leitura
    lerDadosSensores();
  }
}