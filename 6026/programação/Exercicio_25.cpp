#include <stdio.h>

int main()
{

   
 
  int valor = 26;
  int contador = 0;

  while((valor %10) > 0)
  {
      valor/=10;
      contador++;
      printf("%d\n",contador);
  }
}
    
    
    
