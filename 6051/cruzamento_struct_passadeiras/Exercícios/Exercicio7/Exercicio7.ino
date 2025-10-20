float numero1 = 0.1;
int numero2 = 10;
int somaint = 0;
float somafloat = 0;
void setup() {
  Serial.begin(9600);

  somaint = numero1 + numero2;
  somafloat = numero1 + numero2;

  Serial.print("soma int = ");
  Serial.println(somaint);
  Serial.print("soma float = ");
  Serial.println(somafloat);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
