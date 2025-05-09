  char letra_Maiuscula = 'A'; // Declaração da variável char e inicialização com o caractere 'A'



  char letra_Minuscula = 'a';
    
    
Serial.begin (9600);



void setup() {
  // put your setup code here, to run once:
  Serial.println("O valor da variável letra é: %c\n", letra_Maiuscula); 
  Serial.println("O valor da variável letra é: %c\n", letra_minuscula);

}

void loop() {
  // put your main code here, to run repeatedly:

}
