int sensor_temperatura = 3;
int led_vermelho = 12;
int sensor_som = 6;
int sensor_luz = 7;
int led_azul = 8;


void setup() {
 Serial.begin(9600);

 
 Serial.println(sensor_temperatura);
 Serial.println(led_vermelho);
 Serial.println(sensor_som);
 Serial.println(led_azul);
 Serial.println(sensor_luz);
}

void loop() {
  
}
