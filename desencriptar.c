#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long mod_pow(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus; 

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }

        base = (base * base) % modulus;
        exponent /= 2;
    }

    return result;
}

void descriptografar(long long mensagemencriptada[], int tamanho, long long d, long long n) {
    for (int i = 0; i < tamanho; i++) {
        mensagemencriptada[i] = mod_pow(mensagemencriptada[i], d, n);
    }
}

void convertascii(char mensagem[],long long mensagemencriptada[],int tamanho){
    for (int i = 0; i < tamanho; i++) {
        mensagem[i] = (char) mensagemencriptada[i];
    }
}

void printArrayLongLong(char arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%c", arr[i]);
    }
    printf("\n");
}

long long encotrarD(long long e,long long p,long long q){
    int D = 2;
    int totient = (p - 1) * (q - 1);    
    while((D*e)%totient!=1) {
        D++;
    }
    return D;
}

void converterParaLongLong(char *str, long long a[], int *tamanho) {
    char *token = strtok(str, " ");
    int i = 0;
    while (token != NULL) {
        a[i] = atoll(token);
        i++;
        token = strtok(NULL, " ");
    }
    *tamanho = i;
}


int main() {
    long long mensagemenc[10000],D;
    char mensagem[10000];
    long long p,q,e,tamanho;

    printf("Digite o texto a ser encriptado:");
    fgets(mensagem, sizeof(mensagem), stdin);
    if (mensagem[strlen(mensagem) - 1] == '\n') {
        mensagem[strlen(mensagem) - 1] = '\0';
    }
    
    converterParaLongLong(mensagem,mensagemenc,&tamanho);
    

    printf("Digite a chave pÃºblica a ser utilizada (p, q, e): ");
    scanf("%lld %lld %lld",&p,&q,&e);

    D = encotrarD(e,p,q);
    descriptografar(mensagemenc,tamanho,D,100160063);
    convertascii(mensagem,mensagemenc,tamanho);
    printArrayLongLong(mensagem,tamanho);
    return 0;
}