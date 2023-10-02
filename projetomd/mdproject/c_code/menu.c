#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int primo(int n)
{
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

int mdc(int n1, int n2)
{
    if (n2 == 0)
    {
        return n1;
    }
    return mdc(n2, n1 % n2);
}

void criarChavePub(int n, int e)
{
    FILE *file;

    file = fopen("chavePub.txt", "w");
    fprintf(file, "%d %d", n, e);
    fclose(file);
    return;
}

int gerarChavePub(long long primo1, long long primo2, long long expoente){
    if(primo1 * primo2 < 256){
        if(!primo(primo1)){
            return 1;
        }
        if (!primo(primo2)){
            return 2;
        }
    }
    long long totiente = (primo1 - 1) * (primo2 - 1);
    long long n = primo1 * primo2;
    if(mdc(totiente, expoente) != 1){
        if (mdc(totiente, expoente) != 1){
            return 3;
        }
    }
    criarChavePub(n, expoente);
    return 0;
}

// ------------------------------- ENCRYPT

int salvarEmArquivo(long long mensagemencriptada[], int tamanho){
    FILE *file;
    file = fopen("textEncript.txt", "w");
    if (file == NULL){
        return 1;
    }

    for (int i = 0; i < tamanho; i++){
        fprintf(file, "%lld ", mensagemencriptada[i]);
    }

    fclose(file);
    return 0;
}

long long mod_pow(long long base, long long exponent, long long modulus)
{
    long long result = 1;
    base = base % modulus;

    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result = (result * base) % modulus;
        }

        base = (base * base) % modulus;
        exponent /= 2;
    }

    return result;
}

void encriptar(char *mensagem, long long mensagemencriptada[], long long n, long long e){
    for (int i = 0; mensagem[i] != '\0'; i++){
        mensagemencriptada[i] = mensagem[i];
        mensagemencriptada[i] = mod_pow(mensagemencriptada[i], e, n);
    }
}

// ---------------------- DESENCRIPTY


int salvarEmArquivoD(char mensagemdesencriptada[], int tamanho){
    FILE *file;
    file = fopen("textDencript.txt", "w");

    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    for (int i = 0; i < tamanho; i++)
    {
        if(mensagemdesencriptada[i] != ' ') fprintf(file, "%c", mensagemdesencriptada[i]);
        else fprintf(file," ");
    }

    fclose(file);
    return 0;
}


void descriptografar(long long mensagemencriptada[], int tamanho, long long d, long long n)
{
    for (int i = 0; i < tamanho; i++)
    {
        mensagemencriptada[i] = mod_pow(mensagemencriptada[i], d, n);
    }
}

void convertascii(char mensagem[], long long mensagemencriptada[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        mensagem[i] = (char)mensagemencriptada[i];
    }
}

long long encotrarD(long long e, long long p, long long q)
{
    int D = 2;
    int totient = (p - 1) * (q - 1);
    while ((D * e) % totient != 1)
    {
        D++;
    }
    return D;
}

void converterParaLongLong(char *str, long long a[], long long *tamanho)
{
    char *token = strtok(str, " ");
    long long i = 0;
    while (token != NULL)
    {
        a[i] = atoll(token);
        i++;
        token = strtok(NULL, " ");
    }
    *tamanho = i;
}



int encriptarMenu(char* mensagem, long long n, long long e){
    int tamanho = strlen(mensagem);
    long long mensagemencriptada[tamanho];
    encriptar(mensagem, mensagemencriptada, n, e);
    salvarEmArquivo(mensagemencriptada, tamanho);
    return 0;
}




int desencriptarMenu(long long p, long long q, int e){
    long long mensagemenc[100000], D, tamanho;
    char mensagem[10000];
    char linha[10000];
    int i = 0;

    FILE *file;
    file = fopen("textEncript.txt", "r");
    

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fgets(mensagem, sizeof(mensagem), file);
    if (mensagem[strlen(mensagem) - 1] == '\n'){
        mensagem[strlen(mensagem) - 1] = '\0';
    }

    fclose(file);

    converterParaLongLong(mensagem, mensagemenc, &tamanho);
    
    long long n = p * q;

    D = encotrarD(e, p, q);
    descriptografar(mensagemenc, tamanho, D, n);
    convertascii(mensagem, mensagemenc, tamanho);
    salvarEmArquivoD(mensagem, tamanho);
    return 0;
}