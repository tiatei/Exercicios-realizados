// criar variaveis basicas
double unsigned sensortemp = 0.0;
double unsigned sensorsom = 0.0;
int unsigned botao = 5;
int unsigned ledvermelho = 10;
int unsigned ledverde = 20;

void setup() {
   Serial.begin(9600);
// ler as variaveis
   Serial.println(sensortemp);
   Serial.println(sensorsom);
   Serial.println(botao)
   Serial.println(ledvermelho)
   Serial.println(ledverde)
   
}

void loop() {

}
