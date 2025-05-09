#include <stdio.h>

int main()
{
int leds[5];
int passadeiras = 0;
int soma = 0;


leds[0]=5;
leds[1]=3;
leds[2]=4;
leds[3]=9;
leds[4]=11;

passadeiras = leds[1];
soma = leds[0] + leds[1] + leds[2] + leds[3]+ leds[4] ;

    printf ("soma:%d\n", soma);
}