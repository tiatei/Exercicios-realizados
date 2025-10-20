void setup() {
  Serial.begin(9600);

  float valorFloat = 7.8;
  int valorInt = (int)valorFloat; // Casting explícito de float para int

  Serial.print("Valor original (float): ");
  Serial.println(valorFloat);

  Serial.print("Valor convertido (int): ");
  Serial.println(valorInt);
}

void loop() {
  // O loop principal não faz nada neste exemplo
}