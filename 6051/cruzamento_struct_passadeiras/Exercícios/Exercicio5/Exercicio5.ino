void setup() {
  Serial.begin(9600);
  Serial.println("Tamanho dos Tipos de Dados:");
  Serial.print("int: ");
  Serial.print(sizeof(int));
  Serial.println(" bytes");

  Serial.print("float: ");
  Serial.print(sizeof(float));
  Serial.println(" bytes");

  Serial.print("double: ");
  Serial.print(sizeof(double));
  Serial.println(" bytes");

  Serial.print("char: ");
  Serial.print(sizeof(char));
  Serial.println(" bytes");
}

void loop() {
  // Nada para fazer aqui no loop principal
}