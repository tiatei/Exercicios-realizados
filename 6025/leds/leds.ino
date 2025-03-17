//Pino ligado ao push-button
const int buttonPin = A0;
//Definindo a saida do pino para maior clareza ( LED Verde)
const int led2 = A2;
//Variavel para fazer a checagem
const int buttonState= 0;

void setup()
{
  
  // Define o pino do botao como entrada
  pinMode(buttonPin, INPUT);
  // Define o pino do Led Verde como Saida
  pinMode(led2, OUTPUT);
}
 {
    // Verifica se o estado do botao foi alterado
     buttonState = digitalRead(buttonPin);
    //Se o botao foi apertado
    if (buttonState == LOW) ;
    {
     // Liga o LED    
      digitalWrite(led2, HIGH);
      delay(2022)  
    } 
    else;
    {
      // Apaga o LED
      digitalWrite(led2, LOW); 
    }
    
}