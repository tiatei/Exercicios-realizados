
void setup()
{
  Serial.begin(9600);
}

void loop() 
{
 unsigned long tempo_anterior = millis();
 unsigned long tempo_anterior2 = millis();
 // indica o tempo no momento em que corre esta instrução.
 Serial.println("milisegundos desde que o codigo começou %lu/n");

 while(1)
 {
  if(millis() - tempo_anterior >= 2000)
  {
    Serial.print("milisegundos desde que o codigo começou: ");
    Serial.println(tempo_anterior);

    tempo_anterior = millis();
  }
  if(millis() - tempo_anterior2 > 10000 )
  {
  Serial.print("passou muito tempo ");
    Serial.println(tempo_anterior);
    tempo_anterior2 = millis();
  }
 }
}
 