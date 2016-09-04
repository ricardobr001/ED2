/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Lista 1                           */
/*	Exercicio 7                       */
/**************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    int RA;
    char nome[100];
    int ano;
    int cred;
} Aluno;

void cadastro(Aluno *a);

int main()
{
    FILE *fpRead;
    FILE *fpWrite;
    int op, exe = 1;
    Aluno a;

    while (exe)
    {
        printf("1. Cadastrar\n2. Alterar\n3. Remover\n4. Buscar\n5. Listar\n6. Sair\n");
        scanf("%d", &op);

        switch (op)
        {
            case 1:
                cadastro(&a);
            break;

            case 2:
                altera();
            break;

            case 3:
                remove();
            break;

            case 4:
                busca();
            break;

            case 5:
                lista();
            break;

            case 6:
                exe = 0;
            break;
        }
    }

    return 0;
}

Aluno* cadastro(Aluno *a)
{
    scanf("%d", &a->RA);
    scanf("%[^\n]s", a->nome);
    scanf("%d", &a->ano);
    scanf("%d", &a->cred);
    
}