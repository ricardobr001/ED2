/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Lista 1                           */
/*	Exercicio 4                       */
/**************************************/

#include <stdio.h>

void copia(FILE *fpRead, FILE *fpWrite);		//Função que fara a copia somente de letras

int main(int argc, char *argv[])		//Argumentos da função main para executar a partir da linha de comando
{
	FILE *fpRead;			//Declaração das variáveis
	FILE *fpWrite;
	char *conteudo, *nome;

	fpRead = fopen(argv[1], "r");		//Abertura dos fluxos de leitura e escrita
	fpWrite = fopen(argv[2], "w");
	copia(fpRead, fpWrite);				//Chamada da função que fara a copia
	fclose(fpWrite);					//Fechamento dos fluxos
	fclose(fpRead);

	return 0;
}

void copia(FILE *fpRead, FILE *fpWrite)
{
	char c;

	while(fscanf(fpRead, "%c", &c) != EOF)			//Enquanto o arquivo não chegar ao EOF, continua efetuando a copia das letras
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		{
			fprintf(fpWrite, "%c", c);
		}
	}
}