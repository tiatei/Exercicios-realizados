
unsigned long millis()
unsigned long previousMillis = 0;
const unsigned long intervalo = 1000;

enum State 
{
   Off = 0,
   on;
};
State state = off;

void setup() {
  // put your setup code here, to run once:

}
 




void loop() {

  While(1)
  {
    if ( millis()- previousMillis >= intervalo)
    {
      switch(state)
      {
        case off :
        digitalwrite(vermelho, Low);

      state = On;

      break;
        case On :
        digitalwrite(vermelho, high);

        state Off;

        break;

      }
    }
    
  }

}
