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
#include <ctype.h>
#include <stdio_ext.h>
#include "562262_ED2_T01.h"

int main()
{
    int contCodigo = 0, retorno = 0, contNome = 0, contEquipe = 0, op, buscar, listar, okCodigo, okNome, okEquipe;
    char chave[13];
    Pokemon info, aux;
    Indice codigo[500]; 
    Nome nome[500], equipe[500];
    FILE *fpPokemonDAT, *fpChavePrimaria, *fpNome, *fpEquipe;
    FILE *auxPokemon, *auxChavePrimaria, *auxNome, *auxEquipe;

    auxPokemon = fopen("pokemons.dat", "r");

    if (!auxPokemon)
    {   
        fpPokemonDAT = fopen("pokemons.dat", "w+");      //Criando um novo arquivo pokemons.dat
    }
    else
    {
        fpPokemonDAT = fopen("pokemons.dat", "r+");      //Abrindo o fluxo de leitura e escrita no final do arquivo
        fseek(fpPokemonDAT, 0 ,SEEK_END);
    }

    auxChavePrimaria = fopen("iprimary.idx", "r");

    if (!auxChavePrimaria)
    {   
        fpChavePrimaria = fopen("iprimary.idx", "w+");      //Criando um novo arquivo pokemons.dat
    }
    else
    {
        okCodigo = leituraChaveRRN(auxChavePrimaria, codigo, &contCodigo);
        fpChavePrimaria = fopen("iprimary.idx", "w");      //Abrindo o fluxo de leitura e escrita no começo do arquivo
        fprintf(fpChavePrimaria, "0\n");
        rewind(fpChavePrimaria);
    }

    auxNome = fopen("ipokemon.idx", "r");

    if (!auxNome)
    {   
        fpNome = fopen("ipokemon.idx", "w+");      //Criando um novo arquivo pokemons.dat
    }
    else
    {
        okNome = leituraNomeEquipe(auxNome, nome, &contNome);
        fpNome = fopen("ipokemon.idx", "w");      //Abrindo o fluxo de leitura e escrita no começo do arquivo
        fprintf(fpNome, "0\n");
        rewind(fpNome);         
    }

    auxEquipe = fopen("iteam.idx", "r");

    if (!auxEquipe)
    {   
        fpEquipe = fopen("iteam.idx", "w+");      //Criando um novo arquivo pokemons.dat
    }
    else
    {
        okEquipe = leituraNomeEquipe(auxEquipe, equipe, &contEquipe);
        fpEquipe = fopen("iteam.idx", "w");      //Abrindo o fluxo de leitura e escrita no começo do arquivo
        fprintf(fpEquipe, "0\n");
        rewind(fpEquipe);         
    }

    if (okCodigo == 0 || okNome == 0 || okEquipe == 0)
    {
        contCodigo = reconstroiIndice(fpPokemonDAT, nome, equipe, codigo);
        contNome = contCodigo;
        contEquipe = contCodigo; 
        fclose(fpPokemonDAT);
        fclose(fpChavePrimaria);
        fclose(fpNome);
        fclose(fpEquipe);
    }

    do
    {
        scanf("%d", &op);

        switch (op)     //Switch do menu do opções
        {
            case 1:
                do
                {
                    info = cadastro();      //Leitura de um pokemon do teclado

                    if (!verificaChave(info, codigo, contCodigo))
                    {
                        printf("ERRO: Já existe um registro com a chave primária %s.\n", info.codigo);
                    }

                } while (!verificaChave(info, codigo, contCodigo));

                colocaChavePrimaria(codigo, info.codigo, &contCodigo);       //Colocando o código do pokemon no vetor de código e RRN
                colocaNome(nome, info.codigo, info.nomePokemon, &contNome);         //Colocando o nome do pokemon no vetor de código e nome
                colocaNome(equipe, info.codigo, info.nomeEquipe, &contEquipe);      //Colocando o nome da equipe do pokemon no vetor de código e equipe                

                ordenaChavePrimaria(codigo, contCodigo);
                ordenaNome(nome, contNome);
                ordenaNome(equipe, contEquipe);

                fpPokemonDAT = fopen("pokemons.dat", "r+");      //Abrindo o fluxo de leitura e escrita no final do arquivo
                fseek(fpPokemonDAT, 0 ,SEEK_END);
                gravaPokemonNoArquivo(fpPokemonDAT, info);
                fclose(fpPokemonDAT);
            break;

            case 2:
                fpPokemonDAT = fopen("pokemons.dat", "r+");      //Abrindo o fluxo de leitura e escrita no final do arquivo
                fseek(fpPokemonDAT, 0 ,SEEK_END);
                modificaCP(fpPokemonDAT, codigo, contCodigo);
                fclose(fpPokemonDAT);
            break;

            case 3:
                scanf("\n%[^\n]s", chave);      //Lendo a chave para efetuar a busca
                fpPokemonDAT = fopen("pokemons.dat", "r+");      //Abrindo o fluxo de leitura e escrita no final do arquivo
                fseek(fpPokemonDAT, 0 ,SEEK_END);
                marcaRegistro(fpPokemonDAT, codigo, chave, contCodigo);
                fclose(fpPokemonDAT);
            break;

            case 4:
                scanf("%d", &buscar);       //Selecionando qual tipo de busca será feita
                scanf("\n%[^\n]s", chave);      //Lendo a chave para efetuar a busca
                fpPokemonDAT = fopen("pokemons.dat", "r+");      //Abrindo o fluxo de leitura e escrita no final do arquivo
                fseek(fpPokemonDAT, 0 ,SEEK_END);

                switch (buscar)
                {
                    case 1:
                        retorno = buscaChavePrimaria(chave, codigo, 0, contCodigo);     //Encontrando a posição que se encontra a chave

                        if (retorno != -1)      //Se a posição for diferente de -1, encontrou a chave, entra no if e imprime seu conteúdo
                        {
                            aux = recuperaPokemon(fpPokemonDAT, codigo, retorno);
                            printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n", aux.codigo, aux.nomePokemon, aux.tipo, aux.cp, aux.data, aux.hora, aux.treinador, aux.nivelTreinador, aux.nomeEquipe);
                        }
                        else        //Caso contrário imprime que não encontrou o registro
                        {
                            printf("Registro não encontrado!\n");
                        }
                        
                    break;

                    case 2:
                        retorno = buscaIndice(chave, nome, contNome);       //Encontrando a posição que se encontra a chave

                        if (retorno != -1)      //Se a posição for diferente de -1, encontrou a chave, entra no if e imprime seu conteúdo
                        {
                            imprimePokemonEquipe(fpPokemonDAT, chave, nome, codigo, retorno, contNome);
                        }
                        else        //Caso contrário imprime que não encontrou o registro
                        {
                            printf("Registro não encontrado!\n");
                        }
                    break;

                    case 3:
                        retorno = buscaIndice(chave, equipe, contEquipe);       //Encontrando a posição que se encontra a chave

                        if (retorno != -1)      //Se a posição for diferente de -1, encontrou a chave, entra no if e imprime seu conteúdo
                        {
                            imprimePokemonEquipe(fpPokemonDAT, chave, equipe, codigo, retorno, contEquipe);
                        }   
                        else        //Caso contrário imprime que não encontrou o registro
                        {
                            printf("Registro não encontrado!\n");
                        }
                    break;
                }

                fclose(fpPokemonDAT);
            break;

            case 5:
                scanf("%d", &listar);       //Selecionando qual tipo de listagem será feita
                fpPokemonDAT = fopen("pokemons.dat", "r+");      //Abrindo o fluxo de leitura e escrita no final do arquivo
                fseek(fpPokemonDAT, 0 ,SEEK_END);              

                switch (listar)
                {
                    case 1:
                        listaPokemonCodigo(fpPokemonDAT, codigo, contCodigo);       //Listando os pokemons pelo o seu código
                    break;

                    case 2:                                                
                        listaPokemonNomeEquipe(fpPokemonDAT, nome, codigo, contNome);       //Listando os pokemons a partir do seu nome
                    break;

                    case 3:                                                
                        listaPokemonNomeEquipe(fpPokemonDAT, equipe, codigo, contEquipe);       //Listando os pokemons a partir da sua equipe
                    break;
                }

                fclose(fpPokemonDAT);
            break;

            case 6:
                fpPokemonDAT = fopen("pokemons.dat", "r+");      //Abrindo o fluxo de leitura e escrita no final do arquivo
                fseek(fpPokemonDAT, 0 ,SEEK_SET);

                limpaBanco(fpPokemonDAT, codigo, contCodigo);
                fpPokemonDAT = fopen("pokemons.dat", "r+");
                fseek(fpPokemonDAT, 0 ,SEEK_END);

                contCodigo = reconstroiIndice(fpPokemonDAT, nome, equipe, codigo);
                contNome = contCodigo;
                contEquipe = contCodigo;

                fclose(fpPokemonDAT);
            break;

            case 7:
                fpChavePrimaria = fopen("iprimary.idx", "w");
                rewind(fpChavePrimaria);
                gravaChavePrimaria(fpChavePrimaria, codigo, contCodigo);
                fclose(fpChavePrimaria);

                fpNome = fopen("ipokemon.idx", "w");
                fseek(fpNome, 0 ,SEEK_END);
                gravaIndice(fpNome, nome, contNome);
                fclose(fpNome);

                fpEquipe = fopen("iteam.idx", "w");
                fseek(fpEquipe, 0 ,SEEK_END);
                gravaIndice(fpEquipe, equipe, contEquipe);
                fclose(fpEquipe);           
            break;
        }

    } while (op != 7);

    return 0;
}
