#define PI 3.14159

void setup() {
  Serial.begin(9600);
  float raio = 5.0;
  float area = PI * raio * raio;
  Serial.print("A área do círculo é: ");
  Serial.println(area);
}

void loop() {
  // O loop principal não faz nada neste exemplo
}