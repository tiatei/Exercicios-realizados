const int ledPin = 3;      // Pino do LED
const int ImanPin = 2;    // Pino do botão

unsigned long tempoAnterior = 0;
const unsigned long intervaloLeitura = 1; // 1 ms

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ImanPin, INPUT_PULLUP); // Usa pull-up interno
}

void loop() {
  unsigned long tempoAtual = millis();
  if (tempoAtual - tempoAnterior >= intervaloLeitura) {
    tempoAnterior = tempoAtual;

    int estadoIman = digitalRead(ImanPin);

    if (estadoIman == HIGH) { // Iman pressionado (pull-up)
      digitalWrite(ledPin, HIGH); // Liga o LED
    } else {
      digitalWrite(ledPin, LOW);  // Apaga o LED
    }
  }
}