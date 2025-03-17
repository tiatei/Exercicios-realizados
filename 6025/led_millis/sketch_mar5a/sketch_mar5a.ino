// Definição dos pinos dos LEDs
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

// Intervalos de tempo para os LEDs (em milissegundos)
unsigned long intervalo1 = 1000;
unsigned long intervalo2 = 2200;
unsigned long intervalo3 = 1000;

// Variáveis para armazenar os últimos tempos em que os LEDs foram alterados
unsigned long ultimoTempo1 = 0;
unsigned long ultimoTempo2 = 0;
unsigned long ultimoTempo3 = 0;

// Estados dos LEDs
bool estadoLed1 = false;
bool estadoLed2 = false;
bool estadoLed3 = false;

void setup() {
  // Configuração dos pinos dos LEDs como saída
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Inicialização dos LEDs como apagados
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

void loop() {
  unsigned long tempoAtual = millis();

  // Verifica se é hora de alternar o estado do LED 1
  if (tempoAtual - ultimoTempo1 >= intervalo1) {
    estadoLed1 = !estadoLed1;
    digitalWrite(led1, estadoLed1 ? HIGH : LOW);
    ultimoTempo1 = tempoAtual;
  }

  // Verifica se é hora de alternar o estado do LED 2
  if (tempoAtual - ultimoTempo2 >= intervalo2) {
    estadoLed2 = !estadoLed2;
    digitalWrite(led2, estadoLed2 ? HIGH : LOW);
    ultimoTempo2 = tempoAtual;
  }

  // Verifica se é hora de alternar o estado do LED 3
  if (tempoAtual - ultimoTempo3 >= intervalo3) {
    estadoLed3 = !estadoLed3;
    digitalWrite(led3, estadoLed3 ? HIGH : LOW);
    ultimoTempo3 = tempoAtual;
  }
}