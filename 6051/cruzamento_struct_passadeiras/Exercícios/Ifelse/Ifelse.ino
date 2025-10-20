int numero1 = 10;
int numero2 = 20;

void setup() {
  Serial.begin(9600);
  if(numero1 > numero2){
    Serial.print("numero1 maior que numero2");
    Serial.println("numero1 maior que numero2");
  }
  else if (numero1 < numero2){
    Serial.print("numero1 menor que numero2");
    Serial.println("numero1 menor que numero2");
  }
  else {
  Serial.print("numero1 vais ser igual numero2");
  Serial.println("numero1 vais ser igual numero2");
  }
}


void loop() {


}
