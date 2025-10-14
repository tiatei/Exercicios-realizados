#include <Arduino.h>
#include "../../../.platformio/packages/framework-arduinoespressif32/cores/esp32/esp32-hal-ledc.h"

// Define o pino PWM para ESP32 (GPIO 26)
#define LED_PIN  12

// Intensidades do LED (0=apagado, 255=brilho máximo)
const int intensidades[] = {255, 30, 15, 10, 5, 1, 0};
const unsigned long intervalo = 5; // 1000 milissegundos = 1 segundo

// Configuração do PWM para ESP32
const int canalPWM = 0;
const int frequenciaPWM = 50000;    // 600Hz
const int resolucaoPWM = 8;        // 8 bits (0-255)

unsigned long tempoAnterior = 0;
int indiceEstado = 0;

void setup() {
  // Configura o canal PWM com a frequência desejada
  ledcSetup(canalPWM, frequenciaPWM, resolucaoPWM);
  // Associa o canal ao pino GPIO 25
  ledcAttachPin(LED_PIN, canalPWM);

  ledcWrite(canalPWM, intensidades[indiceEstado]);
}

void loop() {
  unsigned long tempoAtual = millis();

  // Verifica se passou o intervalo de tempo
  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual;
    indiceEstado++;
    if (indiceEstado >= 7) indiceEstado = 0;
    ledcWrite(canalPWM, intensidades[indiceEstado]);
  }
}