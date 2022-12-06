#include <stdio.h>
#include <stdlib.h>

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

	for(i=1;i<28;i++) {
		float aumento = aumentoTotal(salario[i-1], salario[i]);
		printf("%d | %05.2f%%              | %05.2f%%        | %05.2f%% \n", *(ano+i), *(inpc+(i-1)), aumento, calculaDiferenca(aumento, *(inpc+(i-1))));
	}
}

float simulaAumentoSemPIB(int *ano, float salario, float *inpc){	
	int i;
	for(i=0; i<TAM; i++){		
		salario += calculaValorDoAumento(salario, *(inpc+i));
	}
	return salario;
}	

float simulaAumentoComPIB(int *ano, float salario, float *inpc, float *pib){	
	int i;
	for(i=0; i<TAM; i++){
		salario += calculaValorDoAumento(salario, calculaAumento(i, *(inpc+i), *(pib+(i-1))));
	}
	return salario;
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

