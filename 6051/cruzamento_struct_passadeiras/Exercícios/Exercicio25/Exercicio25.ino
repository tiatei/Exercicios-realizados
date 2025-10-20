int numero = 2530;
int contador = 0;

void setup() {
Serial.begin(9600);
while(((numero%10) > 0) || ((numero / 10) > 0))
{
numero /= 10;
contador++;
Serial.print("contador");
Serial.println(contador);
}
}

void loop() {

}
