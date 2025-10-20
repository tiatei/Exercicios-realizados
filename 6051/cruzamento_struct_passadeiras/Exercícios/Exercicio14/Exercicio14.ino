   int dias = 10;
   int semana = 0;
   int restantes = 0;


void setup() {
   Serial.begin(9600);
   semana = dias / 7;
   restantes = dias % 7; 
}

void loop() {   
   Serial.println(dias);
   Serial.println(semana);
   Serial.println(restantes);
   delay(2000);
}
