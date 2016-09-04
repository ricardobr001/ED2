/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Lista 1                           */
/*	Exercicio 8                       */
/**************************************/

#include <stdio.h>

int calcula(FILE *fp);				//Função que retorna o tamanho do arquivo em bytes

int main(int argc, char *argv[])
{
	FILE *fp;						//Declaração das variáveis

	fp = fopen(argv[1], "r");		//Abertura do fluxo de leitura
	printf("%d\n", calcula(fp));	//Impressão na tela do tamanho do arquivo e chamada da função calcula
	fclose(fp);						//Fechamento do fluxo

	return 0;
}

int calcula(FILE *fp)
{
	fseek(fp, 0 ,SEEK_END);		//O ponteiro fpRead vai para o final do arquivo
	return ftell(fp);			//A função ftell me diz a posição que eu estou no arquivo
}