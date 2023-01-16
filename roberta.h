#define TAM 28

// funcoes principais
void exibeDados(int *ano, float *salario, float *inpc, float *pib);

void exibeAumentos(int *ano, float *salario, float *inpc, float *pib);

float simulaAumentoSemPIB(float salario, float *inpc);

float simulaAumentoSemPIBRecursivo(int i, float salario, float *inpc);

float simulaAumentoComPIB(float salario, float *inpc, float *pib);

void aumentoRealPorGoverno(char *nome, int *ano, float *inpc, float *salario);

// funcoes de calculo
float calculaValorDoAumento(float salario, float aumento);

float calculaAumento(int posicao, float inpc, float pib);	

float aumentoTotal(float salario1, float salario2);

float calculaDiferenca(float valor1, float valor2);

int retornaPosicao(int ano, int *vetAno);

float calculaAumentoRealPorPeriodo(int anoInicial, int anoFinal, int *ano, float *inpc, float *salario);

// funcoes de strings
char maiuscula(char letra);

char mainuscula(char letra);

void formataString(char *str);

