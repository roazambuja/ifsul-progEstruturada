#define TAM 28

void exibeDados(int *ano, float *salario, float *inpc, float *pib);

void exibeAumentos(int *ano, float *salario, float *inpc, float *pib);

float simulaAumentoSemPIB(int *ano, float salario, float *inpc);

float simulaAumentoComPIB(int *ano, float salario, float *inpc, float *pib);

float calculaValorDoAumento(float salario, float aumento);

float calculaAumento(int posicao, float inpc, float pib);	

float aumentoTotal(float salario1, float salario2);

float calculaDiferenca(float valor1, float valor2);
