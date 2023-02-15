#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "roberta.h"

void exibeDados(int *ano, float *salario, float *inflacao, float *pib){
	printf("ANO   | SALARIO  |  INFLACAO   | PIB\n");
	int i;
	for(i=0; i<TAM; i++){
		printf("%d  | %07.2f  | %05.2f%%      | %05.2f%%\n", *(ano+i), *(salario+i), *(inflacao+i), *(pib+i));
	}
}

void exibeAumentos(int *ano, float *salario, float *inflacao, float *pib) {
	int i;
	printf("ANO  | INFLACAO (ANO ANTERIOR) | AUMENTO TOTAL | AUMENTO REAL\n");

	for(i=1;i<TAM;i++) {
		float aumento = aumentoTotal(*(salario+(i-1)), *(salario+i));
		printf("%d | %05.2f%%                  | %05.2f%%        | %05.2f%% \n", *(ano+i), *(inflacao+(i-1)), aumento, calculaDiferenca(aumento, *(inflacao+(i-1))));
	}
}

float simulaAumentoSemPIB(float salario, float *inflacao){	
	int i;
	for(i=0; i<TAM; i++){		
		salario += calculaValorDoAumento(salario, *(inflacao+i));
	}
	return salario;
}	

float simulaAumentoSemPIBRecursivo(int i, float salario, float *inflacao){	
	float *ptr_inflacao = inflacao+i;
		
	if (i == TAM-1){
		return salario;
	} else {
		salario += calculaValorDoAumento(salario, *ptr_inflacao);
		return simulaAumentoSemPIBRecursivo(i+1, salario, inflacao+0);
	}
}	

float simulaAumentoComPIB(float salario, float *inflacao, float *pib){	
	int i;
	for(i=0; i<TAM; i++){
		salario += calculaValorDoAumento(salario, calculaAumento(i, *(inflacao+i), *(pib+(i-1))));
	}
	return salario;
}

void mostraSimulacoes(float *salario, float *inflacao, char *tipo, float *pib) {
	float valor = simulaAumentoSemPIB(*(salario+0), inflacao);
	printf("Se o salario minimo nao tivesse aumento real e apenas cobrisse a inflacao (%s), seu valor atual seria de R$ %.2f\n", tipo, valor);	
	printf("- Diferenca de R$ %.2f do valor atual.\n", calculaDiferenca(*(salario+(TAM-1)), valor));
	
	printf("Calculando com a funcao recursiva: R$ %.2f\n", simulaAumentoSemPIBRecursivo(0, *(salario+0), inflacao));
			
	valor = simulaAumentoComPIB(*(salario+0), inflacao, pib);
	printf("Se o salario minimo tivesse aumento real considerando o %s e o PIB, seu valor atual seria de R$ %.2f\n", tipo, valor);
	printf("- Diferenca de R$ %.2f do valor atual.\n", calculaDiferenca(*(salario+(TAM-1)), valor));
}

void aumentoRealPorGoverno(char *nome, int *ano, float *inflacao, float *salario) {
	char presidente[30];
	strcpy(presidente, nome);
	formataString(presidente);
	
	if(strcmp(presidente, "Fernando Henrique") == 0){
		printf("No governo %s o percentual total de aumento real foi de %.2f%%\n", presidente, calculaAumentoRealPorPeriodo(1996, 2002, ano, inflacao, salario));
	} else if(strcmp(presidente, "Lula") == 0) {
		printf("No governo %s o percentual total de aumento real foi de %.2f%%\n", presidente, calculaAumentoRealPorPeriodo(2003, 2010, ano, inflacao, salario));
	} else if (strcmp(presidente, "Dilma") == 0) {
		printf("No governo %s o percentual total de aumento real foi de %.2f%%\n", presidente, calculaAumentoRealPorPeriodo(2011, 2016, ano, inflacao, salario));
	} else if (strcmp(presidente, "Temer") == 0) {
		printf("No governo %s o percentual total de aumento real foi de %.2f%%\n", presidente, calculaAumentoRealPorPeriodo(2017, 2018, ano, inflacao, salario));
	} else if (strcmp(presidente, "Bolsonaro") == 0) {
		printf("No governo %s o percentual total de aumento real foi de %.2f%%\n", presidente, calculaAumentoRealPorPeriodo(2019, 2022, ano, inflacao, salario));
	} else {
		printf("O presidente informado nao foi encontrado.");
	}
}

void leArquivo(float *vet, char *arquivo){
	FILE *fp = fopen(arquivo, "r");
	float x;
	int i = 0;
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo.");
		return;
	}
	while (!feof(fp)) {
		fscanf(fp, "%f\n", &*(vet+i));
		i++;
	}
	fclose(fp);
}

float calculaValorDoAumento(float salario, float aumento){
	return salario * aumento / 100;
}

float calculaAumento(int posicao, float inflacao, float pib){
	if (posicao != 0 && pib > 0) {
		return (inflacao+pib);	
	} else {
		return inflacao;
	}
}

float aumentoTotal(float salario1, float salario2){
	float diferenca = calculaDiferenca(salario2, salario1);
	return (diferenca * 100 / salario1);
}

float calculaDiferenca(float valor1, float valor2) {
	return (valor1 - valor2);
}

int retornaPosicao(int ano, int *vetAno) {
	int i;
	for(i=0; i<TAM; i++){
		if(*(vetAno+i) == ano) {
			return i;
		}
	}
}

float calculaAumentoRealPorPeriodo(int anoInicial, int anoFinal, int *ano, float *inflacao, float *salario){
	int inicio = retornaPosicao(anoInicial, ano);
	int fim = retornaPosicao(anoFinal, ano);
	
	float aumento = 0;
	float aumentoReal = 0;
	int i;
	for(i=inicio; i<=fim; i++){
		aumento = aumentoTotal(*(salario+(i-1)), *(salario+i));
		aumentoReal += calculaDiferenca(aumento, *(inflacao+(i-1)));
	}
	return aumentoReal;
}

char maiuscula(char letra){
	if(letra >= 97 && letra <= 122){
		letra = letra - 32;
	} 
	return letra;
}

char minuscula(char letra){
	if(letra >= 65 && letra <= 90){
		letra = letra + 32;
	} 
	return letra;
}

void formataString(char * str){
    char formatada[30];
    strcpy(formatada, str);
    int i;

 	for(i=0; i<=strlen(str); i++){
 		if (i==0) {
 			formatada[i] = maiuscula(*(str+i));	
		} else if (formatada[i] == 32){
			i++;
			formatada[i] = maiuscula(*(str+i));
		} else {
			formatada[i] = minuscula(*(str+i));
		}
    }      
    strcpy(str, formatada);
}

void separaConteudo(){
	printf("\n--------------------------------------------------------------------------------------------------------\n\n");
}

