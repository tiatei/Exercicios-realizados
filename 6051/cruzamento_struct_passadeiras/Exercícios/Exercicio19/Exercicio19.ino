int numero_inteiro = 101;
 
void setup() {
 Serial.begin(9600);
  if(numero_inteiro%2 == 0){
    Serial.print("numero_inteiro");
    Serial.println(numero_inteiro);
  }
  else
{
  Serial.print("numero_impar");
  Serial.println("numero_impar");
}
}


void loop() {


}
