#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

// Valores do INPC: https://www.ibge.gov.br/estatisticas/economicas/precos-e-custos/9258-indice-nacional-de-precos-ao-consumidor.html?=&t=series-historicas
// Valores do PIB: https://sidra.ibge.gov.br/tabela/6784
// Valores dos salários mínimos: https://www.contabeis.com.br/tabelas/salario-minimo/
// Forma do cálculo: https://economia.uol.com.br/noticias/redacao/2022/10/25/salario-minimo-qual-e-a-regra-de-hoje-para-os-reajustes.htm#:~:text=Atualmente%2C%20o%20c%C3%A1lculo%20do%20governo,tamb%C3%A9m%20ser%C3%A1%20reajustado%20em%205%25.


int main (){
	
	int ano[28] = {1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022};
	float salario[28] = {100, 112, 120, 130, 136, 151, 180, 200, 240, 260, 300, 350, 380, 415, 465, 510, 545, 622, 678, 724, 788, 880, 937, 954, 998, 1045, 1100, 1212};
	float inpc[28] = {21.98, 9.12, 4.34, 2.49, 8.43, 5.27, 9.44, 14.74, 10.38, 6.13, 5.05, 2.81, 5.16, 6.48, 4.11, 6.46, 6.08, 6.20, 5.56, 6.23, 11.28, 6.58, 2.07, 3.43, 4.48, 5.45, 10.16, 0};
	float pib[28] = {0, 2.2, 3.4, 0.3, 0.5, 4.4, 1.4, 3.1, 1.1, 5.8, 3.2, 4, 6.1, 5.1, -0.1, 7.5, 4, 1.9, 3, 0.5, -3.5, -3.3, 1.3, 1.8, 1.2, -3.3, 0, 0};
	
	int *ptr_ano;
	float *ptr_salario, *ptr_inpc, *ptr_pib;
	
	ptr_ano = ano, ptr_salario = salario, ptr_inpc = inpc, ptr_pib = pib;
		
	exibeDados(ptr_ano, ptr_salario, ptr_inpc, ptr_pib);
	printf("\n--------------------------------------------------------------------------------------------------------\n\n");
	
	exibeAumentos(ptr_ano, ptr_salario, ptr_inpc, ptr_pib);
	
	printf("\n--------------------------------------------------------------------------------------------------------\n\n");
	
	float valor = simulaAumentoSemPIB(ptr_ano, salario[0], ptr_inpc);
	printf("Se o salario minimo nao tivesse aumento real e apenas cobrisse a inflacao, seu valor atual seria de R$ %.2f\n", valor);	
	printf("- Diferenca de R$ %.2f do valor atual.\n\n", calculaDiferenca(salario[TAM-1], valor));
	
	
	valor = simulaAumentoComPIB(ptr_ano, salario[0], ptr_inpc, ptr_pib);
	printf("Se o salario minimo tivesse aumento real considerando o INPC e o PIB, seu valor atual seria de R$ %.2f\n", valor);
	printf("- Diferenca de R$ %.2f do valor atual.\n\n", calculaDiferenca(salario[TAM-1], valor));

		

    return 0;
}

