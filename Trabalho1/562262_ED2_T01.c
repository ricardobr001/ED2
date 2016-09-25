/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Data de enrega: 05/10/2016        */
/*	Trabalho 1                        */
/*  Professor: Tiago                  */
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "562262_ED2_T01.h"

/*Cadastro de um novo pokemon*/
Pokemon cadastro()
{
    Pokemon info;

    do
    {
        //printf("Digite o nome do pokemon: ");
        scanf("\n%[^\n]s", info.nomePokemon);
    } while (!verificaNome(info.nomePokemon));

    do
    {
        //printf("Digite o tipo do pokemon: ");
        scanf("\n%[^\n]s", info.tipo);
    } while (!verificaTipoPokemon(info.tipo));
    
    do
    {
        //printf("Digite o cp do pokemon: ");
        scanf("\n%[^\n]s", info.cp);
    } while (!verificaCP(info.cp));
    
    do
    {
        //printf("Digite a data da captura: ");
        scanf("\n%[^\n]s", info.data);
    } while (!verificaData(info.data));
    
    do
    {
        //printf("Digite a hora da captura: ");
        scanf("\n%[^\n]s", info.hora);
    } while (!verificaHora(info.hora));
    
    do
    {
        //printf("Digite o nome do treinador: ");
        scanf("\n%[^\n]s", info.treinador);
    } while(!verificaTreinador(info.treinador));    

    do
    {
        //printf("Digite o nivel do treinador: ");
        scanf("\n%[^\n]s", info.nivelTreinador);
    } while (!verificaNivel(info.nivelTreinador));

    do
    {
        //printf("Digite o nome da equipe: ");
        scanf("\n%[^\n]s", info.nomeEquipe);
    } while (!verificaEquipe(info.nomeEquipe));

    geraChavePrimaria(&info);

    return info;  
}

/*Verifica se os caracteres do nome é válido*/
int verificaNome(char *nome)
{
    int i = 0;

    while (nome[i] != '\0')
    {
        if ((nome[i] < 'A' || nome[i] > 'Z') && (nome[i] < 'a' || nome[i] > 'z'))
        {
            return 0;
        }

        i++;
    }

    i = 0;

    while (nome[i] != '\0')
    {
        nome[i] = toupper(nome[i]);
        i++;
    }

    return 1;
}

/*Verifica se os caracteres do tipo são válidos*/
int verificaTipoPokemon(char *tipo)
{
    int i = 0;

    while (tipo[i] != '\0')
    {
        if (((tipo[i] < 'A' || tipo[i] > 'Z') && (tipo[i] < 'a' || tipo[i] > 'z')) && tipo[i] != '/')
        {
            return 0;
        }

        i++;
    }

    i = 0;

    while (tipo[i] != '\0')
    {
        tipo[i] = toupper(tipo[i]);
        i++;
    }

    return 1;
}

/*Verifica se os caracteres do CP é válido*/
int verificaCP(char *cp)
{
    if ((cp[0] < '0' || cp[0] > '9') && (cp[1] < '0' || cp[1] > '9') && (cp[2] < '0' || cp[2] > '9') && (cp[3] < '0' || cp[3] > '9'))
    {
        return 0;
    }
    else if (cp[4] != '.')
    {
        return 0;
    }
    else if ((cp[5] < '0' || cp[5] > '9') && (cp[6] < '0' || cp[6] > '9'))
    {
        return 0;
    }
    

    return 1;
}

/*Verifica se os caracteres da data são válidos*/
int verificaData(char *data)
{
    int dias;

    if (data[6] == '1')     //Se a dezena do ano for 1, entra no if
    {
        if (data[7] < '6')      //Se for um ano menor que 2016, não é um ano válido
        {
            return 0;
        }
        else if (data[7] < '6' || data[7] > '9')        //Verifica se os caracteres do ano são validos
        {
            return 0;
        }
    }

    if (data[2] != '/' || data[5] != '/')       //Se os delimitadores da data não for '/', não é uma data válida
    {
        return 0;
    }

    dias = verificaMes(data);       //Descobrindo quantos dias tem o mês

    if (dias == 0)     //Se não for um mês válido, retorna 0
    {
        return 0;
    }
    else if (dias == 30)        //Se for um mês com 30 dias entra no if
    {
        if (data[0] < '0' || data[0] > '3')     //Verifica se os caracteres da dezena são válidos
        {
            return 0;
        }
        else if (data[0] == '3' && data[1] != '0')      //Se a dezena for 3, verifica se a unidade é 0
        {
            return 0;
        }
        else if (data[1] < '0' || data[1] > '9')        //Verifica se os caracteres da unidade do dia são válidos
        {
            return 0;
        }
    }
    else if (dias == 31)        //Se for um mês com 31 dias entra no if
    {
        if (data[0] < '0' || data[0] > '3')     //Verifica se os caracteres da dezena são válidos
        {
            return 0;
        }
        else if (data[0] == '3' && data[1] != '0' && data[1] != '1')        //Se a dezena for 3, verifica se a unidade é 0 ou 1
        {
            return 0;
        }
        else if (data[1] < '0' || data[1] > '9')        //Verifica se os caracteres da unidade do dia são válidos
        {
            return 0;
        }
    }
    else if (dias == 29)        //Se for um mês com 29 dias entra no if
    {
        if (data[0] < '0' || data[0] > '2')     //Verifica se os caracteres da dezena são válidos
        {
            return 0;
        }
        else if (data[1] < '0' || data[1] > '9')        //Verifica se os caracteres da unidade do dia são válidos
        {
            return 0;
        }
    }
    else if (dias == 28)        //Se for um mês com 29 dias entra no if
    {
        if (data[0] < '0' || data[0] > '2')     //Verifica se os caracteres da dezena são válidos
        {
            return 0;
        }
        else if (data[0] == '2')        //Se a dezena for 2, entra no if
        {
            if (data[1] < '0' || data[1] > '8')         //Verifica se os caracteres da unidade do dia são válidos
            {
                return 0;
            }                
        }
        else if (data[1] < '0' || data[1] > '9')        //Verifica se os caracteres da unidade do dia são válidos
        {
            return 0;
        }
    }

    return 1;       //Retorna que é uma data válida
}

/*Verifica o mês*/
int verificaMes(char *data)
{
    if (data[3] < '0' || data[3] > '1')     //Verifica se os caracteres da dezena do mês são válidos
    {
        return 0;
    }
    else if (data[4] < '0' || data[4] > '9')        //Verifica se os caracteres da unidade do mês são válidos
    {
        return 0;
    }

    if (data[3] == '0')     //Se for um mês entre Janeiro e Setembro, entra no if
    {
        if (data[4] == '1' || data[4] == '3' || data[4] == '5' || data[4] == '7' || data[4] == '8')     //Verifica se é um mês com 31 dias
        {
            return 31;
        }
        else if (data[4] == '2')        //Se for Fevereiro, entra no if
        {
            printf("Saida da função %d\n", verificaBissexto(data));

            if (verificaBissexto(data));        //Se for um ano bissexto, fevereiro terá 29 dias
            {                
                printf("Tem 29 dias!\n");
                return 29;
            }
            
            return 28;      //Caso contrário terá 28 dias
        }
        
        return 30;      //Para qualquer outro mês entre 1 e 9 será um mês com 30 dias 
    }

    if (data[3] == '1' && data[4] == '1')       //Se for um mês mês de Novembro, terá 30 dias
    {
        return 30;
    }
    else if (data[3] == '1' && (data[4] == '0' || data[4] == '2'))      //Se for Outubro ou dezembro terá 31 dias
    {
        return 31;
    }

    return 0;       //Caso contrário é um mês inválido
}

/*Verifica se o ano é bissexto*/
int verificaBissexto(char *data)
{
    int i;
    char ano[3];

    //printf("\n\nData: %c%c\n\n", data[6], data[7]);

    ano[0] = data[6];       //Copia os caracteres que delimitam o ano para a string ano
    ano[1] = data[7];
    i = atoi(ano) + 2000;       //Transforma a string ano em número e soma 2000 ao seu valor

    /*printf("i = %d\n", i);
    printf("i mod 400 = %d\n", i%400);
    printf("i mod 4 = %d\n", i%4);
    printf("i mod 100 = %d\n", i%100);*/

    if (i % 400 == 0)           //Um ano divísivel por 400 é bissexto
    {
        //printf("É bissexto!!\n\n");
        return 1;
    }
    else if (i % 4 == 0 && i % 100 != 0)        //Um ano divísivel por 4 é bissexto, porém um ano divisível por 100 não é bissexto
    {
        //printf("É bissexto!!\n\n");
        return 1;
    }

    //printf("NÃO é bissexto!\n\n");
    return 0;
}

/*Verifica se os caracteres da hora são válidos*/
int verificaHora(char *hora)
{
    if (hora[0] < '0' || hora[0] > '2')     //Verifica se o caractere da dezena das horas é válido
    {
        return 0;
    }
    else if (hora[0] == '2' && (hora[1] < '0' || hora[1] > '3'))        //Verifica se o caractere da unidade das horas é válido
    {
        return 0;
    }
    else if(hora[2] != ':')     //Verifica se o caractere separador de horas e minutos é válido
    {
        return 0;
    }
    else if (hora[3] < '0' || hora[3] > '5')        //Verifica se o caractere da dezena dos minutos é válido
    {
        return 0;
    }
    else if (hora[4] < '0' || hora[4] > '9')        //Verifica se o caractere da unidade dos minutos é válido
    {
        return 0;
    }
    return 1;
}

/*Verifica se o nome do treinador é válido*/
int verificaTreinador(char *treinador)
{
    int i = 0;

    while (treinador[i] != '\0')    //Verifica se o nome do treinador é válido, ou seja se possui apenas números ou letras
    {
        if ((treinador[i] < 'A' || treinador[i] > 'Z') && (treinador[i] < 'a' || treinador[i] > 'z') && (treinador[i] < '0' || treinador[i] > '9'))
        {
            return 0;
        }

        i++;
    }

    i = 0;

    while (treinador[i] != '\0')        //Enquanto não chegar no final da string, deixa todas as letras maiusculas
    {
        treinador[i] = toupper(treinador[i]);
        i++;
    }

    return 1;
}

/*Verifica se o nivel do treinador é válido*/
int verificaNivel(char *nivel)
{
    int i;
    char n[4];

    strcpy(n, nivel);       //Copia os caracteres da string nível para uma outra string
    i = atoi(n);            //Transforma a string em número

    if (i <= 100 && i > 0)      //Verifica se o nível é válido
    {
        return 1;
    }

    return 0;
}

/*Verifica se o nome da equipe é válido*/
int verificaEquipe(char *equipe)
{
    int i = 0;

    if (!verificaNome(equipe))      //Verifica se o nome da equipe possui algum caracteve inválido
    {
        return 0;
    }

    while (equipe[i] != '\0')       //Enquanto não chegar no final da string, deixa todas as letras maiusculas
    {
        equipe[i] = toupper(equipe[i]);
        i++;
    }

    if (!strcmp("VALOR", equipe))       //Verifica se o nome da equipe é válido
    {
        return 1;
    }
    else if (!strcmp("INSTINCT", equipe))
    {
        return 1;
    }
    else if (!strcmp("MYSTIC", equipe))
    {
        return 1;
    }

    return 0;
}

/*Função que gera a chave primária de um novo registro*/
void geraChavePrimaria(Pokemon *info)
{
    info->codigo[0] = info->nomeEquipe[0];
    info->codigo[1] = info->treinador[0];
    info->codigo[2] = info->nomePokemon[0];
    info->codigo[3] = info->nomePokemon[1];
    info->codigo[4] = info->data[0];
    info->codigo[5] = info->data[1];
    info->codigo[6] = info->data[3];
    info->codigo[7] = info->data[4];
    info->codigo[8] = info->hora[0];
    info->codigo[9] = info->hora[1];
    info->codigo[10] = info->hora[3];
    info->codigo[11] = info->hora[4];
    info->codigo[12] = '\0';
}

/*Função que coloca os dados no vetor de chaves primárias*/
void colocaChavePrimaria(Indice *vet, char *codigo, int *i)
{
    strcpy(vet[(*i)].codigo, codigo);
    vet[(*i)].RRN = (*i);
    (*i)++;
}

/*Função que encontra um registro a partir de uma determinada chave primária*/
int buscaChavePrimaria(char *codigo, Indice *vet, int limEsq, int limDir)
{
    int i, j;

    i = (limDir + limEsq) / 2;

    if (!strcmp(vet[i].codigo, codigo))     //Se as strings forem iguais, retorna a posição em que se encontra a chave primária encontrada
    {
        return i;
    }

    if (limEsq >= limDir)       //Não encontrou a chave
    {
        return -1;
    }
    else
    {
        for(j = 0 ; vet[i].codigo[j] == codigo[j] ; j++);       //Enquanto os caracteres forem iguais, continua o laço

        if (vet[i].codigo[j] < codigo[j])           //Verificando se precisa procurar a chave a direita ou a esquerda no vetor
        {
            return buscaChavePrimaria(codigo, vet, i+1, limDir);
        }
        else
        {
            return buscaChavePrimaria(codigo, vet, limEsq, i-1);
        }
    }
}

/*Função que ordena o vetor a partir da chave primária*/
void ordenaChavePrimaria(Indice *vet, int tam)
{
    Indice aux;
    int i, pai, filho, j;

    i = tam / 2;

    for (;;)
    {
        if (i > 0)
        {
            i--;
            aux = vet[i];
        }
        else
        {
            tam--;

            if (tam == 0)
            {
                return;
            }

            aux = vet[tam];
            vet[tam] = vet[0];
        }

        pai = i;
        filho = i * 2 + 1;

        while (filho < tam)
        {
            for(j = 0 ; vet[filho+1].codigo[j] == vet[filho].codigo[j] ; j++);

            if ((filho + 1 < tam) && (vet[filho+1].codigo[j] > vet[filho].codigo[j]))
            {
                filho++;
            }

            for(j = 0 ; vet[filho].codigo[j] == aux.codigo[j] ; j++);

            if (vet[filho].codigo[j] > aux.codigo[j])
            {
                vet[pai] = vet[filho];
                pai = filho;
                filho = pai * 2 + 1;
            }
            else
            {
                break;
            }
        }
        vet[pai] = aux;
    }
}

/*Função que grava um pokemon no arquivo pokemons.dat*/
void gravaPokemonNoArquivo(FILE *fp, Pokemon info)
{
    fprintf(fp, "%s@%s@%s@%s@%s@%s@%s@%s@%s\n", info.codigo, info.nomePokemon, info.tipo, info.cp, info.data, info.hora, info.treinador, info.nivelTreinador, info.nomeEquipe);
}

/*Função que grava o vetor de indice no arquivo*/
void gravaIndice(FILE *fp, Indice *vet, int tam)
{
    int i;

    fprintf(fp, "1\n");
    
    for (i = 0 ; i < tam ; i++)
    {
        fprintf(fp, "%s %d\n", vet[i].codigo, vet[i].RRN); 
    }
}