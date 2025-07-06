//criar maquina de estados
//estado 1 inicia contagem inicial
//estado 2 tempo final descarga do condensador
//estado 3 consoante o tempo de descarga realiza diferentes tarefasenum Estado {INICIO, DESCARGA, ACOES};
enum Estado {INICIO, DESCARGA, ACOES, LED_ACESO};
Estado estadoAtual = INICIO;

int tempo_inicial = 0;
int tempo_final = 0;
int tempo_descarga = 0;
const int leituraDoCondensador = A0;
const int led_Vermelho = A1;
const int led_Verde = A2;
const int led_Azul = A3;

unsigned long ledAcendeMillis = 0;
int ledSelecionado = 0; 

void setup() {
    Serial.begin(9600);
    pinMode(leituraDoCondensador, INPUT);
    pinMode(led_Vermelho, OUTPUT);
    pinMode(led_Verde, OUTPUT);
    pinMode(led_Azul, OUTPUT);
}

void loop() {
    switch (estadoAtual) {
        case INICIO:
            // Espera o condensador carregar até 5V (valor máximo do ADC é 1023)
            if (analogRead(leituraDoCondensador) >= 1020) {
                tempo_inicial = millis();
                Serial.print("Consensador carregado");
                estadoAtual = DESCARGA;
            }
            break;

        case DESCARGA:
            // Espera o condensador descarregar (abaixo de 100, por exemplo)
            if (analogRead(leituraDoCondensador) <= 100) {
                tempo_final = millis();
                tempo_descarga = tempo_final - tempo_inicial;
                estadoAtual = ACOES;
            }
            break;

        case ACOES:
            Serial.print("Tempo de descarga: ");
            Serial.print(tempo_descarga);
            Serial.println(" ms");

            digitalWrite(led_Vermelho, LOW);
            digitalWrite(led_Verde, LOW);
            digitalWrite(led_Azul, LOW);

            if (tempo_descarga < 1000) {
                Serial.println("Descarga rápida: Aciona tarefa 1");
                digitalWrite(led_Vermelho, HIGH);
                ledSelecionado = 1;
            } else if (tempo_descarga < 2000) {
                Serial.println("Descarga média: Aciona tarefa 2");
                digitalWrite(led_Verde, HIGH);
                ledSelecionado = 2;
            } else {
                Serial.println("Descarga lenta: Aciona tarefa 3");
                digitalWrite(led_Azul, HIGH);
                ledSelecionado = 3;
            }
            ledAcendeMillis = millis();
            estadoAtual = LED_ACESO;
            break;

        case LED_ACESO:
            if (millis() - ledAcendeMillis >= 2000) { 
                digitalWrite(led_Vermelho, LOW);
                digitalWrite(led_Verde, LOW);
                digitalWrite(led_Azul, LOW);
                estadoAtual = INICIO;
            }
            break;
    }
}