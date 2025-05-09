int main()
{
    int posicao = 0;
    int valores[5];
    
    
    
    
    while(1)
    {
        valores[posicao]=10;
        posicao++;
        if(posicao < 4){
        printf("posiçao:%d\n", posicao);
        }
        
        if(posicao > 4)
        {
            posicao = 0;
        }
        
           
    }
}