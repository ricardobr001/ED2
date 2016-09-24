/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Data de enrega: 05/10/2016        */
/*	Trabalho 1                        */
/*  Professor: Tiago                  */
/**************************************/

#ifndef TRAB_H
#define TRAB_H

typedef struct pokemon
{
    char codigo[13];
    char nomePokemon[50];
    char tipo[50];
    char cp[8];
    char data[9];
    char hora[6];
    char treinador[50];
    char nivelTreinador[4];
    char nomeEquipe[9];
} Pokemon;

/*Cadastro de um novo pokemon*/
Pokemon cadastro(int *i);

/*Verifica se os caracteres do nome é válido*/
int verificaNome(char *nome);

/*Verifica se os caracteres do tipo são válidos*/
int verificaTipoPokemon(char *tipo);

/*Verifica se os caracteres do CP é válido*/
int verificaCP(char *cp);

/*Verifica se os caracteres da data são válidos*/
int verificaData(char *data);

/*Verifica o mês*/
int verificaMes(char *data);

/*Verifica se o ano é bissexto*/
int verificaBissexto(char *data);

/*Verifica se os caracteres da hora são válidos*/
int verificaHora(char *hora);

/*Verifica se o nome do treinador é válido*/
int verificaTreinador(char *treinador);

/*Verifica se o nivel do treinador é válido*/
int verificaNivel(char *nivel);

/*Verifica se o nome da equipe é válido*/
int verificaEquipe(char *equipe);

/*Função que gera a chave primária de um novo registro*/
void geraChavePrimaria(Pokemon *info);

/*Função que encontra um registro a partir de uma determinada chave primária*/
int buscaChavePrimaria(char *codigo, Pokemon *vet, int limEsq, int limDir);

/*Função que ordena o vetor a partir da chave primária*/
void ordenaChavePrimaria(Pokemon *vet, int tam);

#endif