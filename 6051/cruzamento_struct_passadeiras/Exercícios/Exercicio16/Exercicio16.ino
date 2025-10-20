int numero_de_dias = 52;
int numero_de_semana = 0;
int numero_de_dias_restantes = 0;




void setup(){
Serial.begin(9600);

numero_de_semana = numero_de_dias / 7;
numero_de_dias_restantes = numero_de_dias %7;

Serial.print("numero_de_dias");
Serial.println(numero_de_dias);
Serial.print("numero_de_semana");
Serial.println(numero_de_semana);
Serial.print("numero_de_dias_restantes");
Serial.println(numero_de_dias_restantes);

}

void loop() {
  // put your main code here, to run repeatedly:

}
