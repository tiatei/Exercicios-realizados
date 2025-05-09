struct sensor {
  int ldr[5];
  double media = 0.0;
  double valor = 0.0;
  int leitura = 0;
};

// Declare sensors with proper initialization
sensor S1;
sensor S2;

unsigned long tempo_anterior = 0;
unsigned long intervalo = 500;

void setup() {
  // Configure sensor pins as input
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  Serial.begin(9600); // Initialize Serial communication
}

void loop() {
  if (millis() - tempo_anterior >= intervalo) {
    tempo_anterior = millis();

    // Read value from sensor S1
    S1.valor = analogRead(A0);
    S1.ldr[S1.leitura] = S1.valor;
    S1.leitura++;

    // Check if all readings have been collected for S1
    if (S1.leitura >= 5) {
      S1.leitura = 0;

      // Calculate the average
      S1.media = (S1.ldr[0] + S1.ldr[1] + S1.ldr[2] + S1.ldr[3] + S1.ldr[4]) / 5.0;

      // Display the result for S1
      Serial.println("Média do sensor S1:");
      Serial.println(S1.media);
    }

    // Repeat the same process for sensor S2
    S2.valor = analogRead(A1);
    S2.ldr[S2.leitura] = S2.valor;
    S2.leitura++;

    if (S2.leitura >= 5) {
      S2.leitura = 0;

      // Calculate the average
      S2.media = (S2.ldr[0] + S2.ldr[1] + S2.ldr[2] + S2.ldr[3] + S2.ldr[4]) / 5.0;

      // Display the result for S2
      Serial.println("Média do sensor S2:");
      Serial.println(S2.media);
    }
  }
}