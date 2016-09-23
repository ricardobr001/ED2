/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Data de enrega: 05/10/2016        */
/*	Trabalho 1                        */
/*  Professor: Tiago                 */
/**************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "562262_ED2_T01.h"

int main()
{
    int i = 0;
    Pokemon info[10];

    while (i < 3)
    {
        info[i] = cadastro(&i);
    }

    i = 0;

    while (i < 3)
    {
        printf("Nome do pokemon: %s\n", info[i].nomePokemon);
        printf("Tipo: %s\n", info[i].tipo);
        printf("CP: %s\n", info[i].cp);
        printf("Data: %s\n", info[i].data);
        printf("Hora: %s\n", info[i].hora);
        printf("Nivel: %s\n", info[i].nivelTreinador);
        printf("Equipe: %s\n", info[i].nomeEquipe);
        printf("=================================================================");
        printf("\n\n");
        i++;
    }

    return 0;
}