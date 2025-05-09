int sensor = A1;
double media = 0.0;
double valor = 0.0;
int leitura = 0; 
double ldr[5];
unsigned long tempo_anterior = 0;
unsigned long intervalo = 200;

void setup() {
  // Configuração do sensor
  pinMode(sensor, INPUT);
  Serial.begin(9600); 
}

void loop() {
  // Verifica se o intervalo de tempo foi atingido
  if (millis() - tempo_anterior >= intervalo) {
    tempo_anterior = millis();

    // Lê o valor do sensor
    valor = analogRead(sensor);
    ldr[leitura] = valor;
    leitura++;

    // Verifica se todas as leituras foram feitas
    if (leitura >= 5) {
      leitura = 0;
      // Calcula a média
      media = (ldr[0] + ldr[1] + ldr[2] + ldr[3] + ldr[4]) / 5.0;

      // Exibe o resultado
      Serial.println("Média do sensor:");
      Serial.println(media);
    }
  }
}




  // put your main code here, to run repeatedly:


