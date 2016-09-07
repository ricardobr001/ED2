/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Lista 1                           */
/*	Exercicio 7                       */
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
    int RA;
    char nome[100];
    int ano;
    int cred;
} Aluno;

typedef struct no {
    Aluno x;
    struct no *esq, *dir;
} No;

typedef No* Arvore;

int insere(Arvore *a, Aluno x);
void cadastro(Arvore *a);
void altera(Arvore *a);
void cria_arvore(Arvore *a);
int modifica(Arvore *a, Aluno x);
void inorder(Arvore p);
void liberaArvore(Arvore a);
int arvoreVazia(Arvore *a);
//void remove(Arvore *a);

int main()
{
    FILE *fpRead;
    FILE *fpWrite;
    int op, exe = 1;
    Arvore a;

    cria_arvore(&a);

    while (exe)
    {
        printf("1. Cadastrar\n2. Alterar\n3. Remover\n4. Buscar\n5. Listar\n6. Sair\n");
        scanf("%d", &op);

        switch (op)
        {
            case 1:
                cadastro(&a);
                inorder(a);
            break;

            case 2:
                altera(&a);
            break;

            case 3:
                //remove();
            break;

            case 4:
                //busca();
            break;

            case 5:
                //lista();
            break;

            case 6:
                exe = 0;
                liberaArvore(a);
            break;
        }
    }

    return 0;
}

void cria_arvore(Arvore *p)
{
	*p = NULL;
}

void cadastro(Arvore *a)
{
    Aluno x;
    scanf("%d %[\n]s %d %d", &x.RA, x.nome, &x.ano, &x.cred);
    //scanf("%[^\n]s", x.nome);
    //scanf("%d", &x.ano);
    //scanf("%d", &x.cred);
    
    insere(a, x);
}

void altera(Arvore *a)
{
    Aluno x;
    scanf("%d", &x.RA);
    
    if(busca(a, x))
    {
        scanf("%s", x.nome);
        scanf("%d", &x.ano);
        scanf("%d", &x.cred);

        modifica(a, x);
    }
    else
    {
        printf("Aluno não cadastrado\n");
    }  
}

int insere(Arvore *a, Aluno x)
{
	No *novo;
	
	if (*a == NULL) {
		novo = malloc(sizeof(No));
		novo->x = x;
		novo->esq = NULL;
		novo->dir = NULL;
		*a = novo;
		return 1;
	}
	
	if (x.RA < (*a)->x.RA)
    {
        return insere (&(*a)->esq, x);
    }		
	else if (x.RA > (*a)->x.RA)
    {
        return insere (&(*a)->dir, x);
    }		
	else
		return 0;
}

int busca (Arvore a, Aluno x)
{
	if (a == NULL) {
		return 0;
	}
	
	if (x.RA < a->x.RA)
    {
		return busca (a->esq, x);
    }
	else if (x.RA > a->x.RA)
    {
		return busca (a->dir, x);
    }
	else
		return 1;
}

int modifica(Arvore *a, Aluno x)
{
	No *novo;
	
	if ((*a)->x.RA == x.RA) 
    {
		strcpy((*a)->x.nome, x.nome);
        (*a)->x.ano = x.ano;
        (*a)->x.cred = x.cred;

		return 1;
	}
	
	if (x.RA < (*a)->x.RA)
    {
        return insere (&(*a)->esq, x);
    }		
	else if (x.RA > (*a)->x.RA)
    {
        return insere (&(*a)->dir, x);
    }
}

void inorder(Arvore p) {
	if (p != NULL) {
		inorder (p->esq);
		printf("RA: %d\n ", p->x.RA);
        printf("Nome: %s\n", p->x.nome);
        printf("Ano: %d\n", p->x.ano);
        printf("Créditos: %d\n", p->x.cred);
        printf("============================\n"); 
		inorder (p->dir);    
	}
}

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

int arvoreVazia(Arvore *a) //Retorna 1 se a arvore estiver vazia, 0 caso tenha pelo menos 1 item
{
	if ((*a) == NULL)
	{
		return 1;
	}

	return 0;
}