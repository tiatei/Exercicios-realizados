void setup() {
  Serial.begin(9600);

  // Declaração e atribuição de valores às três variáveis inteiras
  int numero1 = 15;
  int numero2 = 28;
  int numero3 = 7;

  // Calcula a soma dos três números
  int soma = numero1 + numero2 + numero3;

  // Imprime a soma no Monitor Serial
  Serial.print("O primeiro número é: ");
  Serial.println(numero1);
  Serial.print("O segundo número é: ");
  Serial.println(numero2);
  Serial.print("O terceiro número é: ");
  Serial.println(numero3);
  Serial.print("A soma total é: ");
  Serial.println(soma);
}

void loop() {
  // O loop principal não faz nada neste exemplo
}
