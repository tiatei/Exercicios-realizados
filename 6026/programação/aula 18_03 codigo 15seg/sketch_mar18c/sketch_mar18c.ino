const int Vermelho_passadeira = 12; // pino passadeira vermelho
const int Verde_passadeira = 13; // pino passadeira verde

const int vermelho1 = 2;// pino semaforo vermelho
const int amarelo1 = 3; // pino semaforo amarelo
const int verde1 = 4;   // pino semaforo verde
const int vermelho2 = 5;// pinosemaforo vermelho
const int amarelo2 = 6;// pino semaforo amarelo
const int verde2 = 7;// pino semaforo verde

//definir os tempos de duração dos semaforos
const unsigned long duração_verde = 15000;
const unsigned long duração_amarelo = 15000;
const unsigned long duração_vermelho = 15000;
const unsigned long duração_verde_passadeira = 15000;


// O estado atual do semáforo
int state = 0;
unsigned long tempo_anterior = 0;

// Funções para controlar os semáforos

void ligar_semaforo_verde1() {
  digitalWrite(greenLight1, HIGH);
  digitalWrite(yellowLight1, LOW);
  digitalWrite(redLight1, LOW);
}

void ligar_semaforo_vermelho1() { 
  digitalWrite(greenLight1, LOW);
  digitalWrite(yellowLight1, LOW);
  digitalWrite(redLight1, HIGH);
}

void ligar_semaforo_vermelho2() { 
  digitalWrite(greenLight2, LOW);
  digitalWrite(yellowLight2, LOW);
  digitalWrite(redLight2, HIGH);
}

void ligar_semaforo_amarelo1() { 
  digitalWrite(greenLight1, LOW);
  digitalWrite(yellowLight1, HIGH);
  digitalWrite(redLight1, LOW);
}

void ligar_semaforo_amarelo2() { 
  digitalWrite(greenLight2, LOW);
  digitalWrite(yellowLight2, HIGH);
  digitalWrite(redLight2, LOW);
}

void ligar_semaforo_verde2() {
  digitalWrite(greenLight2, HIGH);
  digitalWrite(yellowLight2, LOW);
  digitalWrite(redLight2, LOW);
}


void setup() {
  // definir os pinos saída
  pinmode ( vermelho1, output );
  pinmode ( amarelo1, output );
  pinmode ( verde1, output);
  pinmode (vermelho2, output);
  pinmode (amarelo2, output);
  pinmode (verde2, output);

  //definir pinos passadeira como saída
  pinmode (vermelho_passadeira, output);
  pinmode (verde_passadeira, output);

}

void loop() {

  unsigned long tempo_atual = millis();
  
  if (state== 0 )
{
  digitalwrite(verde_passadeira, LOW);
  digitalwrite(vermelho_passadeira, HIGH);
  ligar_semaforo_verde1();
  ligar_semaforo_vermelho2();
  tampo_anterior = tempo atual;
  state= 1 ; 
}
else if 
}
}
