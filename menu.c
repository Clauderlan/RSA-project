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

void gerarChavePub()
{

    printf("Gerando chave pub\n");
    long long primo1 = 0, primo2 = 0, expoente;

    while (primo1 * primo2 < 256)
    {

        printf("Primeiro primo :\n");
        scanf("%lld", &primo1);

        if (!primo(primo1))
        {
            printf("Digite um número primo válido!\n");
            scanf("%lld", &primo1);
        }

        printf("Segundo primo :\n");
        scanf("%lld", &primo2);
        if (!primo(primo2))
        {
            printf("Digite um número primo válido!\n");
            scanf("%lld", &primo2);
        }
    }

    long long totiente = (primo1 - 1) * (primo2 - 1);
    long long n = primo1 * primo2;
    while (mdc(totiente, expoente) != 1)
    {
        printf("O Expoente agora :\n");
        scanf("%lld", &expoente);

        if (mdc(totiente, expoente) != 1)
        {
            printf("Expoente inválido !\n");
        }
    }
    criarChavePub(n, expoente);
    return;
}

// ------------------------------- ENCRYPT

int salvarEmArquivo(long long mensagemencriptada[], int tamanho)
{
    FILE *file;
    file = fopen("textEncript.txt", "w");

    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    for (int i = 0; i < tamanho - 1; i++)
    {
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

void encriptar(char *mensagem, long long mensagemencriptada[], long long n, long long e)
{
    for (int i = 0; mensagem[i] != '\0'; i++)
    {
        mensagemencriptada[i] = mensagem[i];
        mensagemencriptada[i] = mod_pow(mensagemencriptada[i], e, n);
    }
}

// ---------------------- DESENCRIPTY

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

int salvarEmArquivoD(char mensagemdesencriptada[], int tamanho)
{
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

void printArrayChar(char arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%c", arr[i]);
    }
    printf("\n");
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

void converterParaLongLong(char *str, long long a[], int *tamanho)
{
    char *token = strtok(str, " ");
    int i = 0;
    while (token != NULL)
    {
        a[i] = atoll(token);
        i++;
        token = strtok(NULL, " ");
    }
    *tamanho = i;
}

void encriptarMenu()
{
    char mensagem[1000000];
    long long n, e;

    printf("Digite o texto a ser encriptado: ");
    limparBufferEntrada();
    fgets(mensagem, sizeof(mensagem), stdin);

    printf("Digite a chave pública a ser utilizada (n, e): ");
    scanf("%lld %lld", &n, &e);

    long long mensagemencriptada[strlen(mensagem)];

    encriptar(mensagem, mensagemencriptada, n, e);

    salvarEmArquivo(mensagemencriptada, strlen(mensagem));

    return;
}

void desencriptarMenu()
{
    long long mensagemenc[10000], D;
    char mensagem[10000];
    long long p, q, tamanho;

    printf("Digite o texto a ser desencriptado:");
    limparBufferEntrada();
    fgets(mensagem, sizeof(mensagem), stdin);
    if (mensagem[strlen(mensagem) - 1] == '\n')
    {
        mensagem[strlen(mensagem) - 1] = '\0';
    }

    converterParaLongLong(mensagem, mensagemenc, &tamanho);

    printf("Digite a chave pública a ser utilizada (p, q): ");
    scanf("%lld %lld", &p, &q);

    FILE *file;
    file = fopen("chavePub.txt", "r");
    int n, e;
    fscanf(file, "%i %i", &n, &e);
    fclose(file);

    D = encotrarD(e, p, q);
    descriptografar(mensagemenc, tamanho, D, n);
    convertascii(mensagem, mensagemenc, tamanho);
    salvarEmArquivoD(mensagem, tamanho);
    printf("Mensagem -> ");
    printArrayChar(mensagem, tamanho);
    return;
}

int main()
{

    int menu;
    while (menu != 4)
    {
        printf("\n1 - Gerar chave pública\n");
        printf("2 - Encriptar\n");
        printf("3 - Desencriptar\n");
        printf("4 - Encerrar\n");

        scanf("%d", &menu);

        if (menu == 1)
            gerarChavePub();
        else if (menu == 2)
            encriptarMenu();
        else if (menu == 3)
            desencriptarMenu();
        else if (menu != 4)
            printf("Opção invalida !\n");
    }

    return 0;
}