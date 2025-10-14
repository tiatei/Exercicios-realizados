// Variáveis para guardar o tempo inicial e o tempo final
int tempo_inicial;
int tempo_final;
//Variável para determinar o pinout 
int leituraDoCondensador = A0;
int esperaLeitura = 2000;
void setup() {
    Serial.begin(9600);
    pinMode(leituraDoCondensador, INPUT);
}

void loop() {
    // Espera o condensador carregar até 5V (valor máximo do ADC é 1023)
    while (analogRead(leituraDoCondensador) < 1020) {
        // Aguarda carregar
    }
    tempo_inicial = millis();

    // Espera o condensador descarregar (abaixo de 100, por exemplo)
    while (analogRead(leituraDoCondensador) > 100) {
        // Aguarda descarregar
    }
    tempo_final = millis();

    Serial.print("Tempo de descarga: ");
    Serial.print(tempo_final - tempo_inicial);
    Serial.println(" ms");

    
}