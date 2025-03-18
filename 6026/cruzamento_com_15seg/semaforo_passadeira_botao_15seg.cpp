#include <Arduino.h>

const int ledPinV = 13; // Pino do Verde pedestre
const int ledPinR = 12; // Pino do VERmelho pedestre
const int buttonPin = 9; // Pino do botão

const int redLight1 = 2;
const int yellowLight1 = 3;
const int greenLight1 = 4;

const int redLight2 = 5;
const int yellowLight2 = 6;
const int greenLight2 = 7;

// Define os intervalos de tempo em milissegundos
const unsigned long redDuration = 5000;   // 5 segundos
const unsigned long yellowDuration = 5000; // 5 segundos
const unsigned long greenDuration = 5000;  // 5 segundos
const unsigned long verdepedestreDuration = 15000; // 15 segundos
const unsigned long buttonCooldown = 7000; // 7 segundos

// Variáveis para armazenar o tempo anterior
unsigned long previousMillis = 0;
unsigned long buttonPressMillis = 0;

// Variável para armazenar o estado atual do semáforo
int state = 0;

// Funções para controlar os semáforos
void ligar_semaforo_verde1() {
  digitalWrite(greenLight1, HIGH);
  digitalWrite(yellowLight1, LOW);
  digitalWrite(redLight1, LOW);
}

void ligar_semaforo_vermelho1() { 
  digitalWrite(greenLight1, LOW);
  digitalWrite(yellowLight1, LOW);
  digitalWrite(redLight1, HIGH);
}

void ligar_semaforo_vermelho2() { 
  digitalWrite(greenLight2, LOW);
  digitalWrite(yellowLight2, LOW);
  digitalWrite(redLight2, HIGH);
}

void ligar_semaforo_amarelo1() { 
  digitalWrite(greenLight1, LOW);
  digitalWrite(yellowLight1, HIGH);
  digitalWrite(redLight1, LOW);
}

void ligar_semaforo_amarelo2() { 
  digitalWrite(greenLight2, LOW);
  digitalWrite(yellowLight2, HIGH);
  digitalWrite(redLight2, LOW);
}

void ligar_semaforo_verde2() {
  digitalWrite(greenLight2, HIGH);
  digitalWrite(yellowLight2, LOW);
  digitalWrite(redLight2, LOW);
}

void setup() {
  pinMode(ledPinR, OUTPUT); // Define o pino do Vermelho pedestre como saída
  pinMode(ledPinV, OUTPUT); // Define o pino do Verde pedestre como saída
  pinMode(buttonPin, INPUT_PULLUP); // Define o pino do botão como entrada com pull-up interno
  
  pinMode(redLight1, OUTPUT);
  pinMode(yellowLight1, OUTPUT);
  pinMode(greenLight1, OUTPUT);
  pinMode(redLight2, OUTPUT);
  pinMode(yellowLight2, OUTPUT);
  pinMode(greenLight2, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && (digitalRead(ledPinV) == LOW || (currentMillis - buttonPressMillis >= buttonCooldown))) {
    digitalWrite(ledPinV, HIGH); // Acende o verde
    digitalWrite(ledPinR, LOW); // Apaga o vermelho
    digitalWrite(greenLight1, LOW);
    digitalWrite(yellowLight1, LOW);
    digitalWrite(redLight1, HIGH);
    digitalWrite(greenLight2, LOW);
    digitalWrite(yellowLight2, LOW);
    digitalWrite(redLight2, HIGH);


    buttonPressMillis = currentMillis; // Salva o tempo atual
  }

  if (state == 0) {
    digitalWrite(ledPinV, LOW); // Apaga o verde
    digitalWrite(ledPinR, HIGH); // Acende o vermelho
    ligar_semaforo_verde1();
    ligar_semaforo_vermelho2();
    previousMillis = currentMillis; // Salva o tempo atual
    state = 1;
  } else if (state == 1 && (currentMillis - previousMillis >= greenDuration)) {
    digitalWrite(ledPinR, HIGH);
    digitalWrite(ledPinV, LOW);
    ligar_semaforo_amarelo1();
    ligar_semaforo_vermelho2();
    previousMillis = currentMillis; // Salva o tempo atual
    state = 2;
  } else if (state == 2 && (currentMillis - previousMillis >= yellowDuration)) {
    digitalWrite(ledPinR, HIGH);
    digitalWrite(ledPinV, LOW);
    ligar_semaforo_vermelho1();
    ligar_semaforo_verde2();
    previousMillis = currentMillis; // Salva o tempo atual
    state = 3;
  } else if (state == 3 && (currentMillis - previousMillis >= yellowDuration)) {
    digitalWrite(ledPinR, HIGH);
    digitalWrite(ledPinV, LOW);
    ligar_semaforo_vermelho1();
    ligar_semaforo_amarelo2();
    previousMillis = currentMillis; // Salva o tempo atual
    state = 4;
  } else if (state == 4 && (currentMillis - previousMillis >= redDuration)) {
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinV, HIGH);
    ligar_semaforo_vermelho1();
    ligar_semaforo_vermelho2();
    previousMillis = currentMillis; // Salva o tempo atual
    state = 5;
  } else if (state == 5 && (currentMillis - previousMillis >= verdepedestreDuration)) {
    state = 0;
  }
}