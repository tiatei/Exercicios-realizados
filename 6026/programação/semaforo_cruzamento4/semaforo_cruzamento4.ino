const int ledPinV = 13; // Pino do Verde pedestre
const int ledPinR = 12;// Pino do VERmelho pedestre
const int buttonPin = 8; // Pino do botão
int buttonState = 0; // Variável para armazenar o estado do botão
// Define os pinos dos LEDs dos semáforos
const int redLight1 = 2;
const int yellowLight1 = 3;
const int greenLight1 = 4;

const int redLight2 = 5;
const int yellowLight2 = 6;
const int greenLight2 = 7;

// Define os intervalos de tempo em milissegundos
const unsigned long redDuration = 3000;   // 5 segundos
const unsigned long yellowDuration = 2000; // 2 segundos
const unsigned long greenDuration = 3000;  // 3 segundos
const unsigned long verdepedestreDuration = 10000;

// Variáveis para armazenar o tempo anterior
unsigned long previousMillis = 0;

// Variável para armazenar o estado atual do semáforo
int currentState = 0;
//ligar semaforo verde1
void ligar_semaforo_verde1()
{
  digitalWrite(greenLight1, HIGH);
  digitalWrite(yellowLight1, LOW);
  digitalWrite(redLight1, LOW);
}
// ligar semaforo vermelho1
void ligar_semaforo_vermelho1()
{ 
  digitalWrite(greenLight1, LOW);
  digitalWrite(yellowLight1, LOW);
  digitalWrite(redLight1, HIGH);
}
// ligar semaforo vermelho2
void ligar_semaforo_vermelho2()
{ 
  digitalWrite(greenLight2, LOW);
  digitalWrite(yellowLight2, LOW);
  digitalWrite(redLight2, HIGH);
}
// ligar semaforo amarelo1
void ligar_semaforo_amarelo1()
{ 
  digitalWrite(greenLight1, LOW);
  digitalWrite(yellowLight1, HIGH);
  digitalWrite(redLight1, LOW);
}
  //ligar semaforo amarelo2
void ligar_semaforo_amarelo2()
{ 
  digitalWrite(greenLight2, LOW);
  digitalWrite(yellowLight2, HIGH);
  digitalWrite(redLight2, LOW);
}
//ligar semaforo verde2
void ligar_semaforo_verde2()
{
  digitalWrite(greenLight2, HIGH);
  digitalWrite(yellowLight2, LOW);
  digitalWrite(redLight2, LOW);
}
void setup() {
  pinMode(ledPinR, OUTPUT); // Define o pino do Vermelho pedestre como saída
  pinMode( ledPinV, OUTPUT); // Define o pino do Verde pedestre como saída
  pinMode(buttonPin, INPUT_PULLUP); // Define o pino do botão como entrada com pull-up interno
  // Configura os pinos dos LEDs como saída
  pinMode(redLight1, OUTPUT);
  pinMode(yellowLight1, OUTPUT);
  pinMode(greenLight1, OUTPUT);
  pinMode(redLight2, OUTPUT);
  pinMode(yellowLight2, OUTPUT);
  pinMode(greenLight2, OUTPUT);
}
void loop() {
  static unsigned long previousMillis = 0;
  
  static int state = 0;
 
  unsigned long currentMillis = millis();

  // Lê o estado do botão
  buttonState = digitalRead(buttonPin);

  // Verifica se o botão está pressionado
  if (buttonState == HIGH) {
    switch (state) {
      case 0:
        digitalWrite(ledPinV, LOW); // Apaga o verde
        digitalWrite(ledPinR, HIGH); // Acende o vermelho
        ligar_semaforo_verde1();
        ligar_semaforo_vermelho2();
        previousMillis = currentMillis;
        state = 1;
        break;
      case 1:
        if (currentMillis - previousMillis >= greenDuration) {
          digitalWrite(ledPinR, HIGH);
          digitalWrite(ledPinV, LOW);
          ligar_semaforo_amarelo1();
          ligar_semaforo_vermelho2();
          previousMillis = currentMillis;
          state = 2;
        }
        break;
      case 2:
        if (currentMillis - previousMillis >= yellowDuration) {
          digitalWrite(ledPinR, HIGH);
          digitalWrite(ledPinV, LOW);
          ligar_semaforo_vermelho1();
          ligar_semaforo_verde2();
          previousMillis = currentMillis;
          state = 3;
        }
        break;
      case 3:
        if (currentMillis - previousMillis >= yellowDuration) {
          digitalWrite(ledPinR, HIGH);
          digitalWrite(ledPinV, LOW);
          ligar_semaforo_vermelho1();
          ligar_semaforo_amarelo2();
          previousMillis = currentMillis;
          state = 4;
        }
        break;
      case 4:
        if (currentMillis - previousMillis >= redDuration) {
          state = 0;
        }
        break;
    }
  } else {
    if (buttonState == LOW) {
      digitalWrite(ledPinV, HIGH); // Acende o verde
      digitalWrite(ledPinR, LOW);
      ligar_semaforo_vermelho1();
      ligar_semaforo_vermelho2();
      unsigned long startMillis = millis();
      while (millis() - startMillis < verdepedestreDuration) {
        // Aguarda até que o tempo definido por verdepedestreDuration tenha passado
      }
      digitalWrite(ledPinV, LOW); // Apaga o verde após o tempo definido
      state = 0;
    }
  }
  }