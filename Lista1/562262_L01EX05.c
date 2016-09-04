/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Lista 1                           */
/*	Exercicio 5                       */
/**************************************/

#include <stdio.h>

void soma(FILE *fpRead, FILE *fpWrite);		//Função que fara a soma das duas colunas e imprimira no arq.out as duas colunas e a coluna resultante

int main()
{
	FILE *fpRead;			//Declaração das variáveis
	FILE *fpWrite;
	char *conteudo, *nome;

	fpRead = fopen("arq.in", "r");		//Abertura dos fluxos de leitura e escrita
	fpWrite = fopen("arq.out", "w");
	soma(fpRead, fpWrite);				//Chamada da função que fara a soma
	fclose(fpWrite);					//Fechamento dos fluxos
	fclose(fpRead);

	return 0;
}

void soma(FILE *fpRead, FILE *fpWrite)
{
	int a, b;

	while(fscanf(fpRead, "%d %d", &a, &b) != EOF)		//Enquanto o arquivo não chegar ao EOF, continua efetuando a soma e imprimindo o resultado no arq.out
	{		
		fprintf(fpWrite, "%d %d %d\n", a, b, a+b);	
	}
}