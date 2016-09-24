/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Data de enrega: 05/10/2016        */
/*	Trabalho 1                        */
/*  Professor: Tiago                  */
/**************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "562262_ED2_T01.h"

int main()
{
    int i = 0;
    //char chave[13];
    Pokemon info[50];

    while (i < 3)
    {
        info[i] = cadastro(&i);
    }

    i = 0;

    /*while (i < 30)
    {
        printf("\n\n");
        printf("Código do pokemon: %s\n", info[i].codigo);
        printf("Nome do pokemon: %s\n", info[i].nomePokemon);
        printf("Tipo: %s\n", info[i].tipo);
        printf("CP: %s\n", info[i].cp);
        printf("Data: %s\n", info[i].data);
        printf("Hora: %s\n", info[i].hora);
        printf("Treinador: %s\n", info[i].treinador);
        printf("Nivel: %s\n", info[i].nivelTreinador);
        printf("Equipe: %s\n", info[i].nomeEquipe);
        printf("=================================================================");
        printf("\n\n");
        i++;
    }*/

    //ordenaChavePrimaria(info, 30);

    //printf("Ordenou!!\n\n");

    while (i < 3)
    {
        printf("\n\n");
        /*printf("Código do pokemon: %s\n", info[i].codigo);
        printf("Nome do pokemon: %s\n", info[i].nomePokemon);
        printf("Tipo: %s\n", info[i].tipo);
        printf("CP: %s\n", info[i].cp);*/
        printf("Data: %s\n", info[i].data);
        /*printf("Hora: %s\n", info[i].hora);
        printf("Treinador: %s\n", info[i].treinador);
        printf("Nivel: %s\n", info[i].nivelTreinador);
        printf("Equipe: %s\n", info[i].nomeEquipe);
        printf("=================================================================");
        printf("\n\n");*/
        i++;
    }

    /*scanf("\n%[^\n]s", chave);
    i = buscaChavePrimaria(chave, info, 0, 30);

    printf("Efetuou a busca!!\n");
    printf("\n\n");
    printf("i = %d\n", i);
    printf("=================================================================");
    printf("Código do pokemon: %s\n", info[i].codigo);
    printf("Nome do pokemon: %s\n", info[i].nomePokemon);
    printf("Tipo: %s\n", info[i].tipo);
    printf("CP: %s\n", info[i].cp);
    printf("Data: %s\n", info[i].data);
    printf("Hora: %s\n", info[i].hora);
    printf("Treinador: %s\n", info[i].treinador);
    printf("Nivel: %s\n", info[i].nivelTreinador);
    printf("Equipe: %s\n", info[i].nomeEquipe);
    printf("=================================================================");
    printf("\n\n");*/

    return 0;
}