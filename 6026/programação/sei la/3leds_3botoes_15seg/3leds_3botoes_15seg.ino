// declarar os pinos dos leds
const int vermelho = 2;
const int verde = 3;
const int azul = 4;
// declarar os pinos dos botões
const int botao_vermelho = 8;
const int botao_verde = 9;
const int botao_azul = 10;

// Define o intervalo de tempo em milissegundos

unsigned long tempo_anterior = 0;
const unsigned long intervalo = 5000;
unsigned long tempo_atual  = millis();

//declarar os estados dos botões
int buttonState = 0;
int buttonState2 = 0;
int buttonState3 = 0;

// demonimar os estados 
enum State
{
  desligado = 0,
  LEDVERMELHO,
  LEDVERDE,
  LEDAZUL
};
int state = desligado;

void setup() {

  // Declarar os pinos dos leds como saída
  pinMode(vermelho, OUTPUT);
  pinMode (verde, OUTPUT);
  pinMode(azul, OUTPUT);

  // Declarar os pinos dos botões como entrada
  pinMode(botao_vermelho, INPUT_PULLUP);
  pinMode( botao_verde, INPUT_PULLUP);
  pinMode ( botao_azul, INPUT_PULLUP);

int buttonstate2 = digitalRead(botao_verde);
int buttonstate = digitalRead (botao_vermelho);
int buttonstate3 = digitalRead (botao_azul);
}

void loop() {


  if ( millis()- tempo_anterior >= intervalo){
  switch(state)
  {
  case desligado :
  {
    digitalWrite(vermelho, LOW);
    digitalWrite(verde, LOW);
    digitalWrite(azul,LOW);
    
    if(digitalRead(botao_vermelho) && (buttonState == LOW))
    {
      state = LEDVERMELHO;
      tempo_anterior = tempo_atual;
    }
    if(digitalRead(botao_verde) && (buttonState2 == LOW))
    {
      state = LEDVERDE;
      tempo_anterior = tempo_atual;
    }
    if(digitalRead(botao_azul) && (buttonState3 == LOW))
    {
    state = LEDAZUL;
    tempo_anterior = tempo_atual;
  }
  break;

   case LEDVERMELHO : //estado led vermelho ligado
   digitalWrite(vermelho, HIGH);
   digitalWrite(verde, LOW);
   digitalWrite(azul, LOW);
   if(tempo_atual- tempo_anterior < intervalo)
   {
    digitalWrite(vermelho,LOW);
    state = desligado;
   }

  break;

  case LEDVERDE :   //estado led verde ligado
  digitalWrite(vermelho, LOW);
  digitalWrite(verde, HIGH);
  digitalWrite(azul, LOW);
if(tempo_atual - tempo_anterior < intervalo)
{
  digitalWrite(verde, LOW);
  state = desligado;
}
break;

  case LEDAZUL :  //estado led azul ligado
  digitalWrite(vermelho, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(azul, HIGH);
  if (tempo_atual - tempo_anterior < intervalo)
  {
    digitalWrite(azul,LOW);
    state = desligado;
  }
  break;

    }
  }
  }
}
