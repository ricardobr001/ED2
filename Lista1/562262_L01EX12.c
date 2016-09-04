/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Lista 1                           */
/*	Exercicio 12                      */
/**************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;

typedef struct no{
  elem_t info;
  struct no *prox;
} No_lista;

typedef No_lista *Lista;

int main()
{
    Lista l;
	FILE *fp;
	int q, i, n, primo = 0;

	fp = fopen("arq.out", "w");
	scanf("%d", &q);
	srand(time(NULL));

	cria_arvore(&a);

	for (i = 0 ; i < q ; i++)
	{
		n = rand() % 100;
		insere(&a, n, &primo);
	}

	imprimeArquivo(a, fp);
	liberaArvore(a);

	printf("Soma dos primos: %d\n", primo);
	return 0;
}