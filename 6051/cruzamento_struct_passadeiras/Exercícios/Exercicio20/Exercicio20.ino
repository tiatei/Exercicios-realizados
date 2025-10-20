void setup() {
  Serial.begin(9600);

  // Declaração e atribuição de valores às duas variáveis inteiras
  int numeroA = 25;
  int numeroB = 18;

  Serial.print("Número A: ");
  Serial.println(numeroA);
  Serial.print("Número B: ");
  Serial.println(numeroB);

  // Estrutura condicional para comparar os números
  if (numeroA > numeroB) {
    Serial.println("Número A é maior que Número B.");
  } else if (numeroB > numeroA) {
    Serial.println("Número B é maior que Número A.");
  } else {
    Serial.println("Número A e Número B são iguais.");
  }
}

void loop() {
  // O loop principal não faz nada neste exemplo
}