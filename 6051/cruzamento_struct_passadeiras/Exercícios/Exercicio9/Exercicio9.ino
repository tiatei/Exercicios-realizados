
String inputString = ""; // String para armazenar os dados recebidos
bool stringComplete = false; // Flag para indicar quando uma linha completa foi recebida

int valorInt;
float valorFloat;
char valorChar;

void setup() {
  Serial.begin(9600);
  Serial.println("Introduza um inteiro, um float e um char separados por espaços (ex: 10 3.14 a):");
  inputString.reserve(200); // Reserva espaço para a string de entrada
}

void loop() {
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
      break;
    }
    if (inChar != '\r') { // Ignora o caractere de retorno de carro (CR) comum em novas linhas
      inputString += inChar;
    }
  }

  if (stringComplete) {
    sscanf(inputString.c_str(), "%d %f %c", &valorInt, &valorFloat, &valorChar);

    Serial.print("Inteiro lido: ");
    Serial.println(valorInt);
    Serial.print("Float lido: ");
    Serial.println(valorFloat);
    Serial.print("Char lido: '");
    Serial.print(valorChar);
    Serial.println("'");

    inputString = "";
    stringComplete = false;
  }
}