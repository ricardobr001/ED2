/**************************************/
/*	Nome: Ricardo Mendes Leal Junior  */
/*	RA: 562262                        */
/*	Data de enrega: 05/10/2016        */
/*	Trabalho 1                        */
/*  Professor: Tiago                 */
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "562262_ED2_T01.h"

/*Cadastro de um novo pokemon*/
Pokemon cadastro(int *i)
{
    Pokemon info;

    do
    {
        printf("Digite o nome do pokemon: ");
        scanf("\n%[^\n]s", info.nomePokemon);
        __fpurge(stdin);
    } while (!verificaNome(info.nomePokemon));

    do
    {
        printf("Digite o tipo do pokemon: ");
        scanf("\n%[^\n]s", info.tipo);
        __fpurge(stdin);
    } while (!verificaTipoPokemon(info.tipo));
    
    do
    {
        printf("Digite o cp do pokemon: ");
        scanf("\n%[^\n]s", info.cp);
        __fpurge(stdin);
    } while (!verificaCP(info.cp));
    
    do
    {
        printf("Digite a data da captura: ");
        scanf("\n%[^\n]s", info.data);
        __fpurge(stdin);
    } while (!verificaData(info.data));
    
    do
    {
        printf("Digite a hora da captura: ");
        scanf("\n%[^\n]s", info.hora);
        __fpurge(stdin);
    } while (!verificaHora(info.hora));
    
    do
    {
        printf("Digite o nivel do treinador: ");
        scanf("\n%[^\n]s", info.nivelTreinador);
        __fpurge(stdin);
    } while (!verificaNivel(info.nivelTreinador));

    do
    {
        printf("Digite o nome da equipe: ");
        scanf("\n%[^\n]s", info.nomeEquipe);
        __fpurge(stdin);
    } while (!verificaEquipe(info.nomeEquipe));

    (*i)++;

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
    if (data[6] == '1')     //Verificando se o ano é válido
    {
        if (data[7] < '6')
        {
            return 0;
        }
        else if (data[7] < '6' || data[7] > '9')
        {
            return 0;
        }
    }

    if (verificaMes(data) == 0)     //Verificando se o mês é válido
    {
        return 0;
    }
    else if (verificaMes(data) == 30)
    {
        if (data[0] < '0' || data[0] > '3')
        {
            return 0;
        }
        else if (data[0] == '3' && data[1] != '0')
        {
            return 0;
        }
        else if (data[1] < '0' || data[1] > '9')
        {
            return 0;
        }
    }
    else if (verificaMes(data) == 31)
    {
        if (data[0] < '0' || data[0] > '3')
        {
            return 0;
        }
        else if (data[0] == '3' && (data[1] != '0' || data[1] != '1'))
        {
            return 0;
        }
        else if (data[1] < '0' || data[1] > '9')
        {
            return 0;
        }
    }
    else if (verificaMes(data) == 29)
    {
        if (data[0] < '0' || data[0] > '2')
        {
            return 0;
        }
        else if (data[1] < '0' || data[1] > '9')
        {
            return 0;
        }
    }
    else 
    {
        if (data[0] < '0' || data[0] > '2')
        {
            return 0;
        }
        else if (data[0] == '2')
        {
            if (data[1] < '0' || data[1] > '8')
            {
                return 0;
            }                
        }
        else if (data[1] < '0' || data[1] > '9')
        {
            return 0;
        }
    }

    return 1;
}

/*Verifica o mês*/
int verificaMes(char *data)
{
    if (data[3] < '0' || data[3] > '1')
    {
        return 0;
    }
    else if (data[4] < '0' || data[4] > '9')
    {
        return 0;
    }

    if (data[3] == '0')
    {
        if (data[4] == '1' || data[4] == '3' || data[4] == '5' || data[4] == '7' || data[4] == '8')
        {
            return 31;
        }
        else if (data[4] == '2')
        {
            if (verificaBissexto(data));
            {
                return 29;
            }
            
            return 28;
        }
        
        return 30;
    }

    if (data[3] == '1' && data[4] == '1')
    {
        return 30;
    }
    else if (data[3] == '1' && (data[4] == '0' || data[4] == '2'))
    {
        return 31;
    }

    return 0;
}

/*Verifica se o ano é bissexto*/
int verificaBissexto(char *data)
{
    int i;
    char ano[3];

    ano[0] = data[6];
    ano[1] = data[7];
    i = atoi(ano);

    if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
    {
        return 1;
    }

    return 0;
}

/*Verifica se os caracteres da hora são válidos*/
int verificaHora(char *hora)
{
    if ((hora[0] < '0' || hora[0] > '9') && (hora[1] < '0' || hora[1] > '9'))
    {
        return 0;
    }
    else if((hora[2]) != ':')
    {
        return 0;
    }
    else if ((hora[3] < '0' || hora[3] > '9') && (hora[4] < '0' || hora[4] > '9'))
    {
        return 0;
    }

    return 1;
}

/*Verifica se o nivel do treinador é válido*/
int verificaNivel(char *nivel)
{
    int i;
    char n[4];

    strcpy(n, nivel);
    i = atoi(n);

    if (i <= 100 && i > 0)
    {
        return 1;
    }

    return 0;
}

/*Verifica se o nome da equipe é válido*/
int verificaEquipe(char *equipe)
{
    int i = 0;

    if (!verificaNome(equipe))
    {
        return 0;
    }

    while (equipe[i] != '\0')
    {
        toupper(equipe[i]);
        i++;
    }

    if (!strcmp("VALOR", equipe))
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