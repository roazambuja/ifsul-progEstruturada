#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "roberta.h"

void exibeDados(int *ano, float *salario, float *inpc, float *pib){
	printf("ANO   | SALARIO  |  INPC   | PIB\n");
	int i;
	for(i=0; i<TAM; i++){
		printf("%d  | %07.2f  | %05.2f%%  | %05.2f%%\n", *(ano+i), *(salario+i), *(inpc+i), *(pib+i));
	}
}

void exibeAumentos(int *ano, float *salario, float *inpc, float *pib) {
	int i;
	printf("ANO  | INPC (ANO ANTERIOR) | AUMENTO TOTAL | AUMENTO REAL\n");

	for(i=1;i<TAM;i++) {
		float aumento = aumentoTotal(*(salario+(i-1)), *(salario+i));
		printf("%d | %05.2f%%              | %05.2f%%        | %05.2f%% \n", *(ano+i), *(inpc+(i-1)), aumento, calculaDiferenca(aumento, *(inpc+(i-1))));
	}
}

float simulaAumentoSemPIB(float salario, float *inpc){	
	int i;
	for(i=0; i<TAM; i++){		
		salario += calculaValorDoAumento(salario, *(inpc+i));
	}
	return salario;
}	

float simulaAumentoSemPIBRecursivo(int i, float salario, float *inpc){	
	float *ptr_inpc = inpc+i;
		
	if (i == TAM-1){
		return salario;
	} else {
		salario += calculaValorDoAumento(salario, *ptr_inpc);
		return simulaAumentoSemPIBRecursivo(i+1, salario, inpc+0);
	}
}	

float simulaAumentoComPIB(float salario, float *inpc, float *pib){	
	int i;
	for(i=0; i<TAM; i++){
		salario += calculaValorDoAumento(salario, calculaAumento(i, *(inpc+i), *(pib+(i-1))));
	}
	return salario;
}

void aumentoRealPorGoverno(char *nome, int *ano, float *inpc, float *salario) {
	char presidente[30];
	strcpy(presidente, nome);
	formataString(presidente);
	
	if(strcmp(presidente, "Fernando Henrique") == 0){
		printf("No governo %s o percentual total de aumento real foi de %.2f%%\n", presidente, calculaAumentoRealPorPeriodo(1996, 2002, ano, inpc, salario));
	} else if(strcmp(presidente, "Lula") == 0) {
		printf("No governo %s o percentual total de aumento real foi de %.2f%%\n", presidente, calculaAumentoRealPorPeriodo(2003, 2010, ano, inpc, salario));
	} else if (strcmp(presidente, "Dilma") == 0) {
		printf("No governo %s o percentual total de aumento real foi de %.2f%%\n", presidente, calculaAumentoRealPorPeriodo(2011, 2016, ano, inpc, salario));
	} else if (strcmp(presidente, "Temer") == 0) {
		printf("No governo %s o percentual total de aumento real foi de %.2f%%\n", presidente, calculaAumentoRealPorPeriodo(2017, 2018, ano, inpc, salario));
	} else if (strcmp(presidente, "Bolsonaro") == 0) {
		printf("No governo %s o percentual total de aumento real foi de %.2f%%\n", presidente, calculaAumentoRealPorPeriodo(2019, 2022, ano, inpc, salario));
	} else {
		printf("O presidente informado nao foi encontrado.");
	}
}

float calculaValorDoAumento(float salario, float aumento){
	return salario * aumento / 100;
}

float calculaAumento(int posicao, float inpc, float pib){
	if (posicao != 0 && pib > 0) {
		return (inpc+pib);	
	} else {
		return inpc;
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

float calculaAumentoRealPorPeriodo(int anoInicial, int anoFinal, int *ano, float *inpc, float *salario){
	int inicio = retornaPosicao(anoInicial, ano);
	int fim = retornaPosicao(anoFinal, ano);
	
	float aumento = 0;
	float aumentoReal = 0;
	int i;
	for(i=inicio; i<=fim; i++){
		aumento = aumentoTotal(*(salario+(i-1)), *(salario+i));
		aumentoReal += calculaDiferenca(aumento, *(inpc+(i-1)));
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
