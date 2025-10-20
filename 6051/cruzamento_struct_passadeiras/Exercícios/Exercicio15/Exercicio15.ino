double temperatura_em_Celsius = 25.0f;
double temperatura_em_Fahrenheit = 0.0f;
double temperatura_em_Kelvin = 0.0f;



void setup() {
  Serial.begin(9600);
temperatura_em_Fahrenheit = (temperatura_em_Celsius * 9.0f /5) + 32.0f;
temperatura_em_Kelvin = (temperatura_em_Celsius + 273.15f);

Serial.print("temperatura_em_Celsius: ");
Serial.println(temperatura_em_Celsius);
Serial.print("temperatura_em_Fahrenheit: ");
Serial.println(temperatura_em_Fahrenheit);
Serial.print("temperatura_em_Kelvin: ");
Serial.println(temperatura_em_Kelvin);
}

void loop() {

}
