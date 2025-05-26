struct sem_carros
{  unsigned int sem_vermelho;
  unsigned int sem_amarelo;
  unsigned int sem_verde;
  int led_vermelho;
  int led_amarelo;
  int led_verde;
  const int porta_vermelho;
  const int porta_amarelo;
  const int porta_verde;
 
};


struct sem_peao
{
  unsigned int sem_pvermelho;
  unsigned int sem_pverde;
  int led_pverde;
  int led_pvermelho;
  const int porta_pvermelho;
  const int porta_pverde;

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
enum estado{
  cz1_3_vermelho_cz2_4_verde,
  cz1_3_vermelho_cz2_4_amarelo,
  cz1_3_verde_cz2_4_vermelho,
  cz1_3_amarelo_cz2_4_vermelho,
};

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
case cz1_3_vermelho_cz2_4_verde:
        sc1.led_vermelho = 1;
        sc1.led_amarelo = 0;
        sc1.led_verde = 0;
        sc3.led_vermelho = 1;
        sc3.led_amarelo = 0;
        sc3.led_verde = 0;
        sc2.led_vermelho = 0;
        sc2.led_amarelo = 0;
        sc2.led_verde =1;
        sc4.led_vermelho = 0;
        sc4.led_amarelo = 0;
        sc4.led_verde = 1;
        sp1.led_pverde = 1;
        sp1.led_pvermelho = 0;
        sp2.led_pverde = 1;
        sp2.led_pvermelho = 0;
        sp3.led_pverde = 0;
        sp3.led_pvermelho = 1;
        sp4.led_pverde = 0;
        sp4.led_pvermelho = 1;
        sp5.led_pverde = 1;
        sp5.led_pvermelho = 0;
        sp6.led_pverde = 1;
        sp6.led_pvermelho = 0;
        sp7.led_pverde = 0;
        sp7.led_pvermelho = 1;
        sp8.led_pverde = 0;
        sp8.led_pvermelho = 1;


      digitalWrite(sc1.porta_vermelho, sc2.led_vermelho ); 
      digitalWrite(sc2.porta_vermelho, sc2.led_vermelho ); 
      digitalWrite(sc3.porta_vermelho, sc3.led_vermelho ); 
      digitalWrite(sc4.porta_vermelho, sc4.led_vermelho ); 
      digitalWrite(sc1.porta_amarelo, sc1.led_amarelo ); 
      digitalWrite(sc2.porta_amarelo, sc2.led_amarelo ); 
      digitalWrite(sc3.porta_amarelo, sc3.led_amarelo ); 
      digitalWrite(sc4.porta_amarelo, sc4.led_amarelo ); 
      digitalWrite(sc1.porta_verde, sc1.led_verde); 
      digitalWrite(sc2.porta_verde, sc2.led_verde);
      digitalWrite(sc3.porta_verde, sc3.led_verde);
      digitalWrite(sc4.porta_verde, sc4.led_verde); 
      digitalWrite( sp1.porta_pverde, sp1.led_pverde);
      digitalWrite( sp2.porta_pverde, sp2.led_pverde);
      digitalWrite( sp3.porta_pverde, sp3.led_pverde);
      digitalWrite( sp4.porta_pverde, sp4.led_pverde);
      digitalWrite( sp5.porta_pverde, sp5.led_pverde);
      digitalWrite( sp6.porta_pverde, sp6.led_pverde);
      digitalWrite( sp7.porta_pverde, sp7.led_pverde);
      digitalWrite( sp1.porta_pvermelho, sp1.led_pvermelho);
      digitalWrite( sp2.porta_pvermelho, sp2.led_pvermelho);
      digitalWrite( sp3.porta_pvermelho, sp3.led_pvermelho);
      digitalWrite( sp4.porta_pvermelho, sp4.led_pvermelho);
      digitalWrite( sp5.porta_pvermelho, sp5.led_pvermelho);
      digitalWrite( sp6.porta_pvermelho, sp6.led_pvermelho);
      digitalWrite( sp7.porta_pvermelho, sp7.led_pvermelho);
      digitalWrite( sp8.porta_pvermelho, sp8.led_pvermelho);
        
      if(millis()- tempo_anterior > sc1.sem_vermelho){
  estado = cz1_3_vermelho_cz2_4_amarelo;
  
  tempo_anterior = millis();
      
      }
        break;

  case cz1_3_vermelho_cz2_4_amarelo :
        sc1.led_vermelho = 1;
        sc1.led_amarelo = 0;
        sc1.led_verde = 0;
        sc3.led_vermelho = 1;
        sc3.led_amarelo = 0;
        sc3.led_verde = 0;
        sc2.led_vermelho = 0;
        sc2.led_amarelo = 1;
        sc2.led_verde =0;
        sc4.led_vermelho = 0;
        sc4.led_amarelo = 1;
        sc4.led_verde = 0;
        sp1.led_pverde =1;
        sp1.led_pvermelho = 0;
        sp2.led_pverde = 1;
        sp2.led_pvermelho = 0;
        sp3.led_pverde = 0;
        sp3.led_pvermelho = 1;
        sp4.led_pverde = 0;
        sp4.led_pvermelho = 1;
        sp5.led_pverde = 1;
        sp5.led_pvermelho = 0;
        sp6.led_pverde = 1;
        sp6.led_pvermelho = 0;
        sp7.led_pverde = 0;
        sp7.led_pvermelho = 1;
        sp8.led_pverde = 0;
        sp8.led_pvermelho = 1;

      digitalWrite(sc1.porta_vermelho, sc2.led_vermelho ); 
      digitalWrite(sc2.porta_vermelho, sc2.led_vermelho ); 
      digitalWrite(sc3.porta_vermelho, sc3.led_vermelho ); 
      digitalWrite(sc4.porta_vermelho, sc4.led_vermelho ); 
      digitalWrite(sc1.porta_amarelo, sc1.led_amarelo ); 
      digitalWrite(sc2.porta_amarelo, sc2.led_amarelo ); 
      digitalWrite(sc3.porta_amarelo, sc3.led_amarelo ); 
      digitalWrite(sc4.porta_amarelo, sc4.led_amarelo ); 
      digitalWrite(sc1.porta_verde, sc1.led_verde); 
      digitalWrite(sc2.porta_verde, sc2.led_verde);
      digitalWrite(sc3.porta_verde, sc3.led_verde);
      digitalWrite(sc4.porta_verde, sc4.led_verde); 
      digitalWrite( sp1.porta_pverde, sp1.led_pverde);
      digitalWrite( sp2.porta_pverde, sp2.led_pverde);
      digitalWrite( sp3.porta_pverde, sp3.led_pverde);
      digitalWrite( sp4.porta_pverde, sp4.led_pverde);
      digitalWrite( sp5.porta_pverde, sp5.led_pverde);
      digitalWrite( sp6.porta_pverde, sp6.led_pverde);
      digitalWrite( sp7.porta_pverde, sp7.led_pverde);
      digitalWrite( sp8.porta_pverde, sp8.led_pverde);
      digitalWrite( sp1.porta_pvermelho, sp1.led_pvermelho);
      digitalWrite( sp2.porta_pvermelho, sp2.led_pvermelho);
      digitalWrite( sp3.porta_pvermelho, sp3.led_pvermelho);
      digitalWrite( sp4.porta_pvermelho, sp4.led_pvermelho);
      digitalWrite( sp5.porta_pvermelho, sp5.led_pvermelho);
      digitalWrite( sp6.porta_pvermelho, sp6.led_pvermelho);
      digitalWrite( sp7.porta_pvermelho, sp7.led_pvermelho);
      digitalWrite( sp8.porta_pvermelho, sp8.led_pvermelho);

        if(millis()- tempo_anterior > sc1.sem_amarelo){
          estado= cz1_3_verde_cz2_4_vermelho;
          tempo_anterior=millis();
        }
  break;
  case cz1_3_verde_cz2_4_vermelho :
        sc1.led_vermelho = 0;
        sc1.led_amarelo = 0;
        sc1.led_verde = 1;
        sc3.led_vermelho = 0;
        sc3.led_amarelo = 0;
        sc3.led_verde = 1;
        sc2.led_vermelho = 1;
        sc2.led_amarelo = 0;
        sc2.led_verde =0;
        sc4.led_vermelho = 1;
        sc4.led_amarelo = 0;
        sc4.led_verde = 0;
        sp1.led_pverde = 0;
        sp1.led_pvermelho = 1;
        sp2.led_pverde = 0 ;
        sp2.led_pvermelho = 1;
        sp3.led_pverde = 1;
        sp3.led_pvermelho = 0;
        sp4.led_pverde = 1;
        sp4.led_pvermelho = 0;
        sp5.led_pverde = 0;
        sp5.led_pvermelho = 1;
        sp6.led_pverde = 0;
        sp6.led_pvermelho = 1;
        sp7.led_pverde = 1;
        sp7.led_pvermelho = 0;
        sp8.led_pverde = 1;
        sp8.led_pvermelho = 0;

      digitalWrite(sc1.porta_vermelho, sc2.led_vermelho ); 
      digitalWrite(sc2.porta_vermelho, sc2.led_vermelho ); 
      digitalWrite(sc3.porta_vermelho, sc3.led_vermelho ); 
      digitalWrite(sc4.porta_vermelho, sc4.led_vermelho ); 
      digitalWrite(sc1.porta_amarelo, sc1.led_amarelo ); 
      digitalWrite(sc2.porta_amarelo, sc2.led_amarelo ); 
      digitalWrite(sc3.porta_amarelo, sc3.led_amarelo ); 
      digitalWrite(sc4.porta_amarelo, sc4.led_amarelo ); 
      digitalWrite(sc1.porta_verde, sc1.led_verde); 
      digitalWrite(sc2.porta_verde, sc2.led_verde);
      digitalWrite(sc3.porta_verde, sc3.led_verde);
      digitalWrite(sc4.porta_verde, sc4.led_verde); 
      digitalWrite( sp1.porta_pverde, sp1.led_pverde);
      digitalWrite( sp2.porta_pverde, sp2.led_pverde);
      digitalWrite( sp3.porta_pverde, sp3.led_pverde);
      digitalWrite( sp4.porta_pverde, sp4.led_pverde);
      digitalWrite( sp5.porta_pverde, sp5.led_pverde);
      digitalWrite( sp6.porta_pverde, sp6.led_pverde);
      digitalWrite( sp7.porta_pverde, sp7.led_pverde);
       digitalWrite( sp8.porta_pverde, sp8.led_pverde);
      digitalWrite( sp1.porta_pvermelho, sp1.led_pvermelho);
      digitalWrite( sp2.porta_pvermelho, sp2.led_pvermelho);
      digitalWrite( sp3.porta_pvermelho, sp3.led_pvermelho);
      digitalWrite( sp4.porta_pvermelho, sp4.led_pvermelho);
      digitalWrite( sp5.porta_pvermelho, sp5.led_pvermelho);
      digitalWrite( sp6.porta_pvermelho, sp6.led_pvermelho);
      digitalWrite( sp7.porta_pvermelho, sp7.led_pvermelho);
      digitalWrite( sp8.porta_pvermelho, sp8.led_pvermelho);
      if(millis()- tempo_anterior > sc1.sem_verde){
          estado=  cz1_3_amarelo_cz2_4_vermelho;
          tempo_anterior=millis();
  }
  break;
  case  cz1_3_amarelo_cz2_4_vermelho:
        sc1.led_vermelho = 0;
        sc1.led_amarelo = 1;
        sc1.led_verde = 0;
        sc3.led_vermelho = 0;
        sc3.led_amarelo = 1;
        sc3.led_verde = 0;
        sc2.led_vermelho = 1;
        sc2.led_amarelo = 0;
        sc2.led_verde =0;
        sc4.led_vermelho = 1;
        sc4.led_amarelo = 0;
        sc4.led_verde = 0;
        sp1.led_pverde =1;
        sp1.led_pvermelho = 0;
        sp2.led_pverde = 1;
        sp2.led_pvermelho = 0;
        sp3.led_pverde = 0;
        sp3.led_pvermelho = 1;
        sp4.led_pverde = 0;
        sp4.led_pvermelho = 1;
        sp5.led_pverde = 1;
        sp5.led_pvermelho = 0;
        sp6.led_pverde = 1;
        sp6.led_pvermelho = 0;
        sp7.led_pverde = 0;
        sp7.led_pvermelho = 1;
        sp8.led_pverde = 0;
        sp8.led_pvermelho = 1;

      digitalWrite(sc1.porta_vermelho, sc2.led_vermelho ); 
      digitalWrite(sc2.porta_vermelho, sc2.led_vermelho ); 
      digitalWrite(sc3.porta_vermelho, sc3.led_vermelho ); 
      digitalWrite(sc4.porta_vermelho, sc4.led_vermelho ); 
      digitalWrite(sc1.porta_amarelo, sc1.led_amarelo ); 
      digitalWrite(sc2.porta_amarelo, sc2.led_amarelo ); 
      digitalWrite(sc3.porta_amarelo, sc3.led_amarelo ); 
      digitalWrite(sc4.porta_amarelo, sc4.led_amarelo ); 
      digitalWrite(sc1.porta_verde, sc1.led_verde); 
      digitalWrite(sc2.porta_verde, sc2.led_verde);
      digitalWrite(sc3.porta_verde, sc3.led_verde);
      digitalWrite(sc4.porta_verde, sc4.led_verde); 
      digitalWrite( sp1.porta_pverde, sp1.led_pverde);
      digitalWrite( sp2.porta_pverde, sp2.led_pverde);
      digitalWrite( sp3.porta_pverde, sp3.led_pverde);
      digitalWrite( sp4.porta_pverde, sp4.led_pverde);
      digitalWrite( sp5.porta_pverde, sp5.led_pverde);
      digitalWrite( sp6.porta_pverde, sp6.led_pverde);
      digitalWrite( sp7.porta_pverde, sp7.led_pverde);
      digitalWrite( sp8.porta_pverde, sp8.led_pverde);
      digitalWrite( sp1.porta_pvermelho, sp1.led_pvermelho);
      digitalWrite( sp2.porta_pvermelho, sp2.led_pvermelho);
      digitalWrite( sp3.porta_pvermelho, sp3.led_pvermelho);
      digitalWrite( sp4.porta_pvermelho, sp4.led_pvermelho);
      digitalWrite( sp5.porta_pvermelho, sp5.led_pvermelho);
      digitalWrite( sp6.porta_pvermelho, sp6.led_pvermelho);
      digitalWrite( sp7.porta_pvermelho, sp7.led_pvermelho);
      digitalWrite( sp8.porta_pvermelho, sp8.led_pvermelho);
      if(millis()- tempo_anterior > sc1.sem_amarelo){
          estado= cz1_3_vermelho_cz2_4_verde ;
          tempo_anterior=millis();
       

}
  }
}