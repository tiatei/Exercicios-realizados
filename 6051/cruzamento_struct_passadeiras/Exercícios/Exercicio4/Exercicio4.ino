int A = 1;
int B = 2;
int C = 3;
int intermediario = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("A - escrever o que eu quiser");
  Serial.println(A);
  Serial.print("B - resultado");
  Serial.println(B);
  Serial.print("C - resultado");
  Serial.println(C);
  // ou Serial.pint("A, B, C"); Serial.println(A, B, C); (Pode ficar tudo junto)
  intermediario = B;
  B = A;
  A = C;
  C = intermediario;
  Serial.print("B - resultado");
  Serial.println(B);
  Serial.print("A - resultado");
  Serial.println(A);
  Serial.print("C - resultado");
  Serial.println(C);
}

void loop() {


}
