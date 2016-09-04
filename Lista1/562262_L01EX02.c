/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Lista 1                           */
/*	Exercicio 2                       */
/**************************************/

#include <stdio.h>

void copia(FILE *fpRead, FILE *fpWrite);		//Função que fara a copia de um arquivo para outro

int main(int argc, char *argv[])		//Argumentos da função main para executar a partir da linha de comando
{
	FILE *fpRead;			//Declaração de variáveis
	FILE *fpWrite;

	fpRead = fopen(argv[1], "r");					//Abertudo do fluxo de leitura
	fpWrite = fopen(strcat(argv[1], "2"), "w");		//Abertura do fluxo de escrita
	copia(fpRead, fpWrite);							//Chamando a função copia
	fclose(fpWrite);								//Fechando ambos os fluxos
	fclose(fpRead);

	return 0;
}

void copia(FILE *fpRead, FILE *fpWrite)
{
	char c;

	while(fscanf(fpRead, "%c", &c) != EOF)		//Enquanto o arquivo não chegar ao EOF, continua copiando o conteudo do arquivo 1 para o arquivo 2
	{
		fprintf(fpWrite, "%c", c);
	}
}