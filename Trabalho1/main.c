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
    int i = 0, j, op, buscar, listar;
    char chave[13];
    Pokemon info;
    Primaria vet[50];
    FILE *fpPokemonDAT;
    //FILE *fpChavePrimaria, *fpNome, *fpEquipe;

    abreArquivoPokemon(fpPokemonDAT);
    //abreArquivo(fpChavePrimaria, "iprimary.idx");
    //abreArquivo(fpNome, "ipokemon.idx");
    //abreArquivo(fpEquipe, "iteam.idx");

    do
    {
        printf("1. Cadastrar\n2. Remover\n3. Mudar CP\n4. Buscar\n5. Listar\n6. Limpar banco\n7. Sair\n");
        scanf("%d", &op);

        switch (op)
        {
            case 1:
                info = cadastro();
                colocaChavePrimaria(vet, info.codigo, &i);
                ordenaChavePrimaria(vet, i+1);
                gravaPokemonNoArquivo(fpPokemonDAT, info);
            break;

            case 2:
                //implementar remoção
            break;

            case 3:
                //implementar modificação do CP
            break;

            case 4:
                scanf("%d", &buscar);
                scanf("\n%[^\n]s", chave);

                j = buscaChavePrimaria(chave, vet, 0, i+1);
                printf("Chave: %s\n", vet[j].codigo);
                printf("RRN: %d\n", vet[j].RRN);
                //implementar busca a partir do nome do pokemon
                //implementar busca a partir do nome da equipe
            break;

            case 5:
                scanf("%d", &listar);

                //listar os pokemons ordenados a partir do codigo
                //listar os pokemons ordenados a partir do nome do pokemon
                //listar os pokemons ordenados a partir do nome da equipe
            break;

            case 6:
                //implementar a função de limpar o banco
            break;

            case 7:

                //Descarrega a memória no disco
                //Implementar funções
            break;
        }

    } while (op != 7);

    return 0;
}