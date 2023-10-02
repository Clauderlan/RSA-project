#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int salvarEmArquivo(long long mensagemencriptada[], int tamanho) {
    FILE *file;
    file = fopen("test.txt", "w"); 
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    
    for (int i = 0; i < tamanho-1; i++) {
        fprintf(file, "%lld ", mensagemencriptada[i]);
    }
    
    fclose(file);
    return 0; 
}

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

void encriptar(char *mensagem, long long mensagemencriptada[], long long n, long long e) {
    for (int i = 0; mensagem[i] != '\0'; i++) {
        mensagemencriptada[i] = mensagem[i];
        mensagemencriptada[i] = mod_pow(mensagemencriptada[i], e, n);
    }
}

int main() {
    char mensagem[1000000]; 
    long long n, e;

    printf("Digite o texto a ser encriptado: ");
    fgets(mensagem, sizeof(mensagem), stdin);

    printf("Digite a chave pÃºblica a ser utilizada (n, e): ");
    scanf("%lld %lld", &n, &e);

    long long mensagemencriptada[strlen(mensagem)];
    
    encriptar(mensagem, mensagemencriptada, n, e);

    salvarEmArquivo(mensagemencriptada, strlen(mensagem));

    return 0;
}