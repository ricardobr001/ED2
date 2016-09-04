/**************************************/
/*  Nome: Ricardo Mendes Leal Junior  */
/*  RA: 562262                        */
/*  Lista 1                           */
/*  Exercicio 13                      */
/**************************************/
 
#include <stdio.h>
#include <stdlib.h>
 
typedef struct no{
  int info;
  struct no *prox;
} No_lista;
 
typedef No_lista *Lista;

void leitura(FILE *fp, int *maior, int *menor, Lista *l);
void inicLista(Lista *l);
void insereFim(Lista *l, int chave);
void inverte(Lista *l);
void imprime(Lista *l);
void libera(Lista *l);
 
int main()
{
    Lista l;
    FILE *fp;
    int maior, menor;
 
    fp = fopen("arq.out", "r");
    inicLista(&l);
    leitura(fp, &maior, &menor, &l);
    inverte(&l);
    imprime(&l);
    libera(&l);
 
    printf("Maior: %d\t Menor: %d\n", maior, menor);
    return 0;
}

void leitura(FILE *fp, int *maior, int *menor, Lista *l)
{
    int n;

    fscanf(fp, "%d", &n);

    *maior = n;
    *menor = n;
    insereFim(l, n);

    while(fscanf(fp, "%d", &n) != EOF)      //Enquanto o arquivo não chegar ao EOF, continua contando a quantidade de caracteres e palavras
    {
        insereFim(l, n);

        if (n > (*maior))
        {
            *maior = n;
        }
        else if (maior < (*menor))
        {
            *menor = n;
        }
    }
}

void inicLista(Lista *l)
{
    *l = NULL;
}

void insereFim(Lista *l, int chave)
{
    No_lista *aux, *novo;
    aux = *l;
    novo = (No_lista*)malloc(sizeof(No_lista));

    if (aux == NULL)
    {
        *l = novo;
        novo->info = chave;
        novo->prox = NULL;
    }
    else
    {
        novo->info = chave;
        novo->prox = NULL;

        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }

        aux->prox = novo;
    }
}

void inverte(Lista *l)
{
    No_lista *antes, *atual, *proximo;
    antes = NULL;
    atual = *l;

    while (atual != NULL)
    {
        proximo = atual->prox;
        atual->prox = antes;
        antes = atual;
        atual = proximo;
    }

    *l = antes;
}

void imprime(Lista *l)
{
    Lista aux;
    aux = *l;

    while(aux != NULL)
    {
        printf("%d\n", aux->info);
        aux = aux->prox;
    }
}

void libera(Lista *l)
{
    No_lista *aux;
    aux = *l;

    while (*l != NULL)
    {
        *l = (*l)->prox;
        free(aux);
        aux = *l;
    }

    *l = NULL;
}