double valor1 = 15;
double valor2=3;
double valor3 = 3.5;
double valor4 = 8;
double resultado = 0;


Serial.begin(9600);
void setup() {
  resultado = (valor1 + valor3) * valor3 / valor4;
  Serial.printf(resultado);
}

void loop() {
  // put your main code here, to run repeatedly:

}
