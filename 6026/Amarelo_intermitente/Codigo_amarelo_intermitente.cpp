#include <Arduino.h>

// Definir pino LED amarelo
const int amarelo = 8;




void setup() {
  // Configura o pino do LED como saída
  pinMode(amarelo, OUTPUT);
}

void loop() {
  // Obtém o tempo atual
  unsigned long tempo_anterior = millis();
  unsigned long tempo_anterior2 = millis();
  // Verifica se o intervalo de tempo passou
  while (1)
  {
   
  
  if (millis() - tempo_anterior >= 1000) {
    // Alterna o estado do LED
    digitalWrite(amarelo, HIGH);
    // Salva o tempo atual
  tempo_anterior = millis();
  }
  if (millis()- tempo_anterior2 >= 500){ {
    // Alterna o estado do LED
    digitalWrite(amarelo, LOW);
    // Salva o tempo atual
  
    tempo_anterior2 = millis();
  }
}
}
}