// Declarar as variáveis com double
double variavel1 = 10.5; // Removido o 'f' para indicar que é um double
double variavel2 = 5.2;  // Removido o 'f' para indicar que é um double
double soma = 0;
double subtracao = 0;
double multiplicacao = 0; 
double divisao = 0;
int resto = 0; 

void setup() {
  // Inicializa a comunicação serial para imprimir os resultados
  Serial.begin(9600);

  // Realiza as operações aritméticas
  double soma = variavel1 + variavel2;
  double subtracao = variavel1 - variavel2;
  double multiplicacao = variavel1 * variavel2;
  double divisao = variavel1 / variavel2;

  // Imprime os resultados com duas casas decimais
  Serial.print("Variável 1: ");
  Serial.println(variavel1, 2);
  Serial.print("Variável 2: ");
  Serial.println(variavel2, 2);
  Serial.print("Soma: ");
  Serial.println(soma, 2);
  Serial.print("Subtração: ");
  Serial.println(subtracao, 2);
  Serial.print("Multiplicação: ");
  Serial.println(multiplicacao, 2);
  Serial.print("Divisão: ");
  Serial.println(divisao, 2);

  // O operador de módulo (%) não funciona diretamente com doubles no Arduino
  // Para obter o resto de uma divisão entre doubles, podemos usar a função fmod() da biblioteca math.h
  // Certifique-se de incluir a biblioteca no início do seu código

  double resto = fmod(variavel1, variavel2);
  Serial.print("Resto (usando fmod): ");
  Serial.println(resto, 2);
}

void loop() {
  // O loop principal fica vazio, pois as operações e impressões são feitas no setup
}
