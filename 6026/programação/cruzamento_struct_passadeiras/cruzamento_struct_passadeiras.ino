struct sem_carros
{
  int led_vermelho;
  int led_amarelo;
  int led_verde;
  const int porta_vermelho;
  const int porta_amarelo;
  const int porta_verde;
  unsigned int sem_vermelho;
  unsigned int sem_amarelo;
  unsigned int sem_verde;
};


struct sem_peao
{
  int led_pverde;
  int led_pvermelho;
  const int porta_pvermelho;
  const int porta_pverde;
  unsigned int sem_pvermelho;
  unsigned int sem_pverde;
};

struct sem_carros sc1 ={
  .sem_vermelho = 15000,
  .sem_amarelo = 2000,
  .sem_verde = 15000,
  .led_vermelho = 0,
  .led_amarelo = 0,
  .led_verde = 0,
  .porta_vermelho = 2,
  .porta_amarelo = 3,
  .porta_verde = 4,
};
struct sem_carros sc2={
  .sem_vermelho = 15000,
  .sem_amarelo = 2000,
  .sem_verde = 15000,
  .led_vermelho = 0,
  .led_amarelo = 0,
  .led_verde = 0,
  .porta_vermelho = 5,
  .porta_amarelo = 6,
  .porta_verde = 7,
};
struct sem_carros sc3={
  .sem_vermelho = 15000,
  .sem_amarelo = 2000,
  .sem_verde = 15000,
  .led_vermelho = 0,
  .led_amarelo = 0,
  .led_verde = 0,
  .porta_vermelho = 8,
  .porta_amarelo = 9,
  .porta_verde = 10,
};
struct sem_carros sc4={
  .sem_vermelho = 15000,
  .sem_amarelo = 2000,
  .sem_verde = 15000,
  .led_vermelho = 0,
  .led_amarelo = 0,
  .led_verde = 0,
  .porta_vermelho = 11,
  .porta_amarelo = 12,
  .porta_verde = 13,
};
struct sem_peao sp1 = {
  .sem_pvermelho = 15000,
  .sem_pverde = 15000,
  .led_pverde = 0,
  .led_pvermelho = 0,
  .porta_pvermelho= 14,
  .porta_pverde = 15,
};
struct sem_peao sp2= {
  .sem_pvermelho = 15000,
  .sem_pverde = 15000,
  .led_pverde = 0,
  .led_pvermelho = 0,
  .porta_pvermelho= 16,
  .porta_pverde = 17,
};
struct sem_peao sp3= {
  .sem_pvermelho = 15000,
  .sem_pverde = 15000,
  .led_pverde = 0,
  .led_pvermelho = 0,
  .porta_pvermelho= 18,
  .porta_pverde = 19,
};
struct sem_peao sp4= {
  .sem_pvermelho = 15000,
  .sem_pverde = 15000,
  .led_pverde = 0,
  .led_pvermelho = 0,
  .porta_pvermelho= 18,
  .porta_pverde = 19,
};
struct sem_peao sp5 = {
  .sem_pvermelho = 15000,
  .sem_pverde = 15000,
  .led_pverde = 0,
  .led_pvermelho = 0,
  .porta_pvermelho= 20,
  .porta_pverde = 21,
};
struct sem_peao sp6 = {
  .sem_pvermelho = 15000,
  .sem_pverde = 15000,
  .led_pverde = 0,
  .led_pvermelho = 0,
  .porta_pvermelho= 22,
  .porta_pverde = 23,
};
struct sem_peao sp7 = {
  .sem_pvermelho = 15000,
  .sem_pverde = 15000,
  .led_pverde = 0,
  .led_pvermelho = 0,
  .porta_pvermelho= 24,
  .porta_pverde = 25,
};
struct sem_peao sp8 = {
  .sem_pvermelho = 15000,
  .sem_pverde = 15000,
  .led_pverde = 0,
  .led_pvermelho = 0,
  .porta_pvermelho= 26,
  .porta_pverde = 27,
};

unsigned long tempo_anterior =0; 
unsigned long tempo_atual=millis();
int estado = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(sc1.porta_vermelho, OUTPUT);
pinMode(sc1.porta_amarelo, OUTPUT);
pinMode(sc1.porta_verde, OUTPUT);
pinMode (sc2.porta_vermelho, OUTPUT);
pinMode(sc2.porta_amarelo, OUTPUT);
pinMode(sc2.porta_verde, OUTPUT);
pinMode (sc3.porta_vermelho, OUTPUT);
pinMode(sc3.porta_amarelo, OUTPUT);
pinMode(sc3.porta_verde, OUTPUT);
pinMode (sc4.porta_vermelho, OUTPUT);
pinMode(sc4.porta_amarelo, OUTPUT);
pinMode(sc4.porta_verde, OUTPUT);


}

void loop() {
  
  // put your main code here, to run repeatedly:
  switch (estado) {
case 0:

        digitalWrite(sc1.porta_vermelha, ); // Apaga o verde
        
      
      tempo_anterior = millis();
        state = 1;
        break;
