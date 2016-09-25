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
    int i = 0, j = 0, k = 0, n = 0, op, buscar, listar;
    char chave[13];
    Pokemon info;
    Indice codigo[50]; 
    Nome nome[50], equipe[50];
    FILE *fpPokemonDAT, *fpChavePrimaria, *fpNome, *fpEquipe;
    FILE *auxPokemon, *auxChavePrimaria, *auxNome, *auxEquipe;

    auxPokemon = fopen("pokemons.dat", "r");

    if (!auxPokemon)
    {   
        fpPokemonDAT = fopen("pokemons.dat", "w+");      //Criando um novo arquivo pokemons.dat
    }
    else
    {
        fpPokemonDAT = fopen("pokemons.dat", "a+");      //Abrindo o fluxo de leitura e escrita no final do arquivo
        fseek(fpPokemonDAT, 0 ,SEEK_END);
    }

    auxChavePrimaria = fopen("iprimary.idx", "r");

    if (!auxChavePrimaria)
    {   
        fpChavePrimaria = fopen("iprimary.idx", "w+");      //Criando um novo arquivo pokemons.dat
    }
    else
    {
        fpChavePrimaria = fopen("iprimary.idx", "a+");      //Abrindo o fluxo de leitura e escrita no começo do arquivo
        rewind(fpChavePrimaria);         
    }

    auxNome = fopen("ipokemon.idx", "r");

    if (!auxNome)
    {   
        fpNome = fopen("ipokemon.idx", "w+");      //Criando um novo arquivo pokemons.dat
    }
    else
    {
        fpNome = fopen("ipokemon.idx", "a+");      //Abrindo o fluxo de leitura e escrita no começo do arquivo
        rewind(fpNome);         
    }

    auxEquipe = fopen("iteam.idx", "r");

    if (!auxEquipe)
    {   
        fpEquipe = fopen("iteam.idx", "w+");      //Criando um novo arquivo pokemons.dat
    }
    else
    {
        fpEquipe = fopen("iteam.idx", "a+");      //Abrindo o fluxo de leitura e escrita no começo do arquivo
        rewind(fpEquipe);         
    }

    do
    {
        //printf("1. Cadastrar\n2. Remover\n3. Mudar CP\n4. Buscar\n5. Listar\n6. Limpar banco\n7. Sair\n");
        scanf("%d", &op);

        switch (op)     //Switch do menu do opções
        {
            case 1:
                info = cadastro();      //Leitura de um pokemon do teclado
                colocaChavePrimaria(codigo, info.codigo, &i);       //Colocando o código do pokemon no vetor de código e RRN
                colocaNome(nome, info.codigo, info.nomePokemon, &k);         //Colocando o nome do pokemon no vetor de código e nome
                colocaNome(equipe, info.codigo, info.nomeEquipe, &n);      //Colocando o nome da equipe do pokemon no vetor de código e equipe
                ordenaChavePrimaria(codigo, k);     //Ordenando os vetores após a incersão
                ordenaIndice(nome, n);
                ordenaIndice(equipe, i);
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

                j = buscaChavePrimaria(chave, codigo, 0, i);
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
                gravaChavePrimaria(fpChavePrimaria, codigo, i);
                gravaIndice(fpNome, nome, k);
                gravaIndice(fpEquipe, equipe, n);
                //Descarrega a memória no disco
                //Implementar funções
            break;
        }

    } while (op != 7);

    return 0;
}