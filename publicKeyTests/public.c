#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int primo(int n){
    if (n < 2)
    {
        return 0;
    }
    for (int x = 2; x <= sqrt(n); x++)
    {
        if (n % x == 0)
        {
            return 0;
        }
    }
    return 1;
}

int mdc(int n1, int n2){
    if(n2 == 0){
        return n1;
    }
    return mdc(n2, n1 % n2);

}

void criarChavePub(int n, int e){

    FILE *file;

    file = fopen("chavePub.txt", "w");
    fprintf(file,"%d %d", n, e);
    fclose(file);
    return;
}

void gerarChavePub(){

    printf("Gerando chave pub\n");
    int primo1 = 0, primo2 = 0, expoente;

    while(primo1 * primo2 < 256){

        printf("Primeiro primo :\n");
        scanf("%d", &primo1);
        
        if(!primo(primo1)){
            printf("Digite um número primo válido!\n");
            scanf("%d", &primo1);
        }

        printf("Segundo primo :\n");
        scanf("%d", &primo2);
        if(!primo(primo2)){
            printf("Digite um número primo válido!\n");
            scanf("%d", &primo2);
        }
    }
    
    int totiente = (primo1 -1) * (primo2 -1); 
    int n = primo1*primo2;
    while(mdc(totiente, expoente) != 1){
        printf("O Expoente agora :\n");
        scanf("%d", &expoente);

        if(mdc(totiente,expoente) != 1){
            printf("Expoente inválido !\n");
        }
    }
    criarChavePub(n, expoente);
    return;
}

int main(void){
    gerarChavePub();
    return 0;
}