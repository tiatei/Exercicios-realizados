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


  while (1){

   if (millis() - tempo_anterior >= 1000)
   
   {
    if(digitalRead(amarelo)){
      digitalWrite(amarelo,LOW);
    }
    else {
      digitalWrite(amarelo,HIGH);
    }
    tempo_anterior= millis();
   }
  }
}