/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Lista 1                           */
/*	Exercicio 3                       */
/**************************************/

#include <stdio.h>

void conta(FILE *fpRead);		//Função que fara a contagem

int main(int argc, char *argv[])		//Argumentos da função main para executar a partir da linha de comando
{
	FILE *fpRead;			//Declaração de variáveis
	char *conteudo, *nome;

	fpRead = fopen(argv[1], "r");		//Abertura do fluxe de leitura
	conta(fpRead);						//Chamando a função que fara a contagem
	fclose(fpRead);						//Fechando o fluxo de escrita

	return 0;
}

void conta(FILE *fpRead)
{
	char c;
	int palavras = 0, caracteres = 0;

	while(fscanf(fpRead, "%c", &c) != EOF)		//Enquanto o arquivo não chegar ao EOF, continua contando a quantidade de caracteres e palavras
	{
		if (c == ' ' || c == '\n')		//Se for encontrado um espaço ou um '\n', teremos uma palavra
		{
			palavras++;
		}

		caracteres++;					//Todo vez que anda o laço conta 1 caractere
	}

	printf("palavras: %d\ncaracteres: %d\n", palavras+1, caracteres);
}