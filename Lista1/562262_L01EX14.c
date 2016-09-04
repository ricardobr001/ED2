/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Lista 1                           */
/*	Exercicio 14                      */
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no {
  int info; /* chave */
  struct no *esq, *dir;
} No;

typedef No* Arvore;

int arvoreVazia(Arvore *a);
void cria_arvore(Arvore *p);
int insere(Arvore *p, int chave, int *primo);
int verificaPrimo(int n);
void imprimeArquivo(Arvore a, FILE *fp);
void liberaArvore(Arvore a);

int main()
{
	Arvore a;
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

//Retorna 1 se a arvore estiver vazia, 0 caso tenha pelo menos 1 item
int arvoreVazia(Arvore *a)
{
	if ((*a) == NULL)
	{
		return 1;
	}

	return 0;
}

//Inicializa um porteiro de arvore
void cria_arvore(Arvore *p)
{
	*p = NULL;
}

//Insere uma nova chave, caso seja repetido, retorna 0
int insere(Arvore *a, int chave, int *primo)
{
	No *novo;
	
	if (*a == NULL)
	{

		if (verificaPrimo(chave))
		{
			*primo += chave;
		}

		novo = malloc(sizeof(No));
		novo->info = chave;
		novo->esq = NULL;
		novo->dir = NULL;
		*a = novo;
		return 1;
	}
	
	if (chave < (*a)->info)
	{
		return insere (&(*a)->esq, chave, primo);
	}
	else if (chave > (*a)->info)
	{
		return insere (&(*a)->dir, chave, primo);
	}
	else
	{
		return 0;
	}
}

//Retorna 1 caso o número seja primo, caso contrário retorna 0
int verificaPrimo (int n)
{
	int i, j;

	for (i = 2 ; i < n ; i++)
	{
		if (n % i == 0)
		{
			return 0;
		}
	}

    return 1;
}

//Imprime conteudo da árvore no arquivo
void imprimeArquivo(Arvore a, FILE *fp)
{
	if (a != NULL)
	{
		imprimeArquivo(a->esq, fp);
		fprintf(fp, "%d\n", a->info);
		imprimeArquivo(a->dir, fp);	
	}
}

//Desaloca os nós da arvore
void liberaArvore(Arvore a)
{
	if (!arvoreVazia(&a))
	{
		liberaArvore(a->esq);
		liberaArvore(a->dir);
		free(a);
		a = NULL;
	}
}