#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

// Valores do INPC: https://www.ibge.gov.br/estatisticas/economicas/precos-e-custos/9258-indice-nacional-de-precos-ao-consumidor.html?=&t=series-historicas
// Valores do PIB: https://sidra.ibge.gov.br/tabela/6784
// Valores dos salários mínimos: https://www.contabeis.com.br/tabelas/salario-minimo/
// Forma do cálculo: https://economia.uol.com.br/noticias/redacao/2022/10/25/salario-minimo-qual-e-a-regra-de-hoje-para-os-reajustes.htm#:~:text=Atualmente%2C%20o%20c%C3%A1lculo%20do%20governo,tamb%C3%A9m%20ser%C3%A1%20reajustado%20em%205%25.
// Valores IPCA: https://www.ibge.gov.br/estatisticas/economicas/precos-e-custos/9256-indice-nacional-de-precos-ao-consumidor-amplo.html?=&t=series-historicas

int main (){
		
	int ano[TAM] = {1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022};
	float salario[TAM] = {100, 112, 120, 130, 136, 151, 180, 200, 240, 260, 300, 350, 380, 415, 465, 510, 545, 622, 678, 724, 788, 880, 937, 954, 998, 1045, 1100, 1212};
	float inpc[TAM] = {21.98, 9.12, 4.34, 2.49, 8.43, 5.27, 9.44, 14.74, 10.38, 6.13, 5.05, 2.81, 5.16, 6.48, 4.11, 6.46, 6.08, 6.20, 5.56, 6.23, 11.28, 6.58, 2.07, 3.43, 4.48, 5.45, 10.16, 0};
	float pib[TAM] = {0, 2.2, 3.4, 0.3, 0.5, 4.4, 1.4, 3.1, 1.1, 5.8, 3.2, 4, 6.1, 5.1, -0.1, 7.5, 4, 1.9, 3, 0.5, -3.5, -3.3, 1.3, 1.8, 1.2, -3.3, 0, 0};

	float *ipca = (float *) malloc (TAM * sizeof(float));
	leArquivo(ipca, "./ipca.txt");
	
	int *ptr_ano;
	float *ptr_salario, *ptr_inpc, *ptr_pib;
	
	ptr_ano = ano, ptr_salario = salario, ptr_inpc = inpc, ptr_pib = pib;
	
		
	exibeDados(ptr_ano, ptr_salario, ptr_inpc, ptr_pib);
	separaConteudo();
	
	exibeAumentos(ptr_ano, ptr_salario, ptr_inpc, ptr_pib);
	separaConteudo();
	
	mostraSimulacoes(ptr_salario, ptr_inpc, "INPC", ptr_pib);
	separaConteudo();
	
	mostraSimulacoes(ptr_salario, ipca, "IPCA", ptr_pib);
	separaConteudo();
	
	aumentoRealPorGoverno("fernando henrique", ptr_ano, ptr_inpc, ptr_salario);
	aumentoRealPorGoverno("Lula", ptr_ano, ptr_inpc, ptr_salario);
	aumentoRealPorGoverno("diLma", ptr_ano, ptr_inpc, ptr_salario);
	aumentoRealPorGoverno("Temer", ptr_ano, ptr_inpc, ptr_salario);
	aumentoRealPorGoverno("BOLSONARO", ptr_ano, ptr_inpc, ptr_salario);
	aumentoRealPorGoverno("termer", ptr_ano, ptr_inpc, ptr_salario);
	separaConteudo();
	
	exibeAumentos(ptr_ano, ptr_salario, ipca, ptr_pib);

    return 0;
}

