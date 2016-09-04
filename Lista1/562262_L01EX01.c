/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Lista 1                           */
/*	Exercicio 1                       */
/**************************************/

#include <stdio.h>

void imprime(FILE *fpRead);		//Função que ira imprimir o conteúdo do arquivo na tela

int main(int argc, char *argv[])		//Argumentos da função main para executar a partir da linha de comando
{
	FILE *fpRead;		//Declaração de variáveis

	fpRead = fopen(argv[1], "r");		//Abrindo o fluxo de leitura
	imprime(fpRead);					//Chamando a função imprime
	fclose(fpRead);						//Fechando o fluxo de leitura

	return 0;
}

void imprime(FILE *fpRead)
{
	char c;

	while(fscanf(fpRead, "%c", &c) != EOF)		//Enquanto o arquivo não chegar ao EOF, continua imprimindo
	{
		printf("%c", c);
	}
}