const int pirPin = 2;    // Pino de sinal do sensor PIR HC-SR501
const int ledPin = 3;    // Pino do LED
const int buzzerPin = 5; // Pino do buzzer 
const int ledverde = 4;

unsigned long tempoAnterior = 0;
const unsigned long intervaloLeitura = 200; // 2000 ms = 2 segundos

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledverde, OUTPUT); // Pino do LED verde
  digitalWrite(ledverde, HIGH); // Liga o LED verde para indicar que o sistema
  Serial.begin(9600);
}

void loop() {
  unsigned long tempoAtual = millis();
  if (tempoAtual - tempoAnterior >= intervaloLeitura) {
    tempoAnterior = tempoAtual;

    int movimento = digitalRead(pirPin);

    if (movimento == HIGH) { // Movimento detectado
      digitalWrite(ledPin, HIGH); // Liga o LED
      Serial.println("Movimento detectado!");
      digitalWrite(buzzerPin, HIGH); // Liga o buzzer
      digitalWrite(ledverde, LOW); // Desliga o LED verde
    } else {
      digitalWrite(ledPin, LOW);  // Apaga o LED
      digitalWrite(buzzerPin, LOW); // Desliga o buzzer
      digitalWrite(ledverde, HIGH); // Liga o LED verde para indicar que o sistema
    }
  }
}