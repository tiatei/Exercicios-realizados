void setup() {
  Serial.begin(9600);

  char char1 = 'X';
  char char2 = 'Y';
  char resultado[3]; // Array para armazenar os dois caracteres mais o caractere nulo de terminação

  resultado[0] = char1;
  resultado[1] = char2;
  resultado[2] = '\0'; // Caractere nulo para indicar o fim da "string"

  Serial.print("Os caracteres juntos são: ");
  Serial.println(resultado);
}

void loop() {
  // Nada para fazer aqui
}
