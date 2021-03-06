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
#include <ctype.h>
#include "562262_ED2_T01.h"

/*Cadastro de um novo pokemon*/
Pokemon cadastro()
{
    Pokemon info;

    do
    {
        scanf("\n%[^\n]s", info.nomePokemon);

        if (!verificaNome(info.nomePokemon))
        {
            printf("Campo inválido! Informe novamente: ");
        }

    } while (!verificaNome(info.nomePokemon));

    do
    {
        scanf("\n%[^\n]s", info.tipo);

        if (!verificaTipoPokemon(info.tipo))
        {
            printf("Campo inválido! Informe novamente: ");
        }

    } while (!verificaTipoPokemon(info.tipo));
    
    do
    {
        scanf("\n%[^\n]s", info.cp);

        if (!verificaCP(info.cp))
        {
            printf("Campo inválido! Informe novamente: ");
        }

    } while (!verificaCP(info.cp));
    
    do
    {
        scanf("\n%[^\n]s", info.data);

        if (!verificaData(info.data))
        {
            printf("Campo inválido! Informe novamente: ");
        }

    } while (!verificaData(info.data));
    
    do
    {
        scanf("\n%[^\n]s", info.hora);

        if (!verificaHora(info.hora))
        {
            printf("Campo inválido! Informe novamente: ");
        }

    } while (!verificaHora(info.hora));
    
    do
    {
        scanf("\n%[^\n]s", info.treinador);

        if (!verificaTreinador(info.treinador))
        {
            printf("Campo inválido! Informe novamente: ");
        }

    } while(!verificaTreinador(info.treinador));    

    do
    {
        scanf("\n%[^\n]s", info.nivelTreinador);

        if (!verificaNivel(info.nivelTreinador))
        {
            printf("Campo inválido! Informe novamente: ");
        }

    } while (!verificaNivel(info.nivelTreinador));

    do
    {
        scanf("\n%[^\n]s", info.nomeEquipe);

        if (!verificaEquipe(info.nomeEquipe))
        {
            printf("Campo inválido! Informe novamente: ");
        }

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
    int i = 0, flag = 0;

    while (tipo[i] != '\0')
    {
        if (((tipo[i] < 'A' || tipo[i] > 'Z') && (tipo[i] < 'a' || tipo[i] > 'z')) && tipo[i] != '/')
        {
            return 0;
        }

        if (tipo[i] == '/')
        {
            if (i == 0)
            {
                return 0;
            }
            else if (tipo[i+1] == '\0')
            {
                return 0;
            }
            
            flag++;
        }
        
        if (flag == 2)
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

            if (verificaBissexto(data))        //Se for um ano bissexto, fevereiro terá 29 dias
            {                
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

    ano[0] = data[6];       //Copia os caracteres que delimitam o ano para a string ano
    ano[1] = data[7];
    ano[2] = '\0';
    i = atoi(ano);       //Transforma a string ano em número

    if (i % 4 == 0)           //Um ano divísivel por 4 é bissexto
    {
        return 1;
    }

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
    if (nivel[0] == '0' && nivel[1] == '0' && nivel[2] == '0')
    {
        return 0;
    }
    else if (nivel[0] == '0')      //Verifica se o nível é válido
    {
        if ((nivel[1] < '0' || nivel[1] > '9') && (nivel[2] < '0' && nivel[2] > '9'))
        {
            return 0;
        }

        return 1;
    }
    else if (nivel[0] == '1' && nivel[1] == '0' && nivel[2] == '0')
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

/*Função que verifica se a chave primaria gerada já existe*/
int verificaChave(Pokemon info, Indice *vet, int tam)
{
    int pos;

    pos = buscaChavePrimaria(info.codigo, vet, 0, tam);     //Busca a chave primaria no vetor

    if (pos == -1)
    {
        return 1;
    }

    return 0;
}

/*Função que coloca os dados no vetor de chaves primárias*/
void colocaChavePrimaria(Indice *vet, char *codigo, int *i)
{
    strcpy(vet[(*i)].codigo, codigo);
    vet[(*i)].RRN = (*i);
    (*i)++;
}

/*Função que coloca os dados no vetor de nome pokemon e nome da equipe*/
void colocaNome(Nome *vet, char *codigo, char *str, int *i)
{
    strcpy(vet[(*i)].codigo, codigo);
    strcpy(vet[(*i)].str, str);
    (*i)++;
}

/*Função que encontra um registro a partir de uma determinada chave primária*/
int buscaChavePrimaria(char *codigo, Indice *vet, int limEsq, int limDir)
{
    int i, j;

    i = (limDir + limEsq) / 2;

    if (!strcmp(vet[i].codigo, codigo))     //Se as strings forem iguais, retorna a posição em que se encontra a chave primária encontrada
    {
        if (vet[i].RRN == -1)       //Se o RRN for -1, retorna -1
        {
            return -1;
        }

        return i;       //Se não retorna a posição
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

/*Função que encontra um registro a partir de uma determinado nome ou time*/
int buscaIndice(char *nome, Nome *vet, int tam)
{
    int i, flag;

    for (i = 0 ; i < tam ; i++)
    {
        flag = strcmp(vet[i].str, nome);

        if (flag == 0)     //Se as strings forem iguais, retorna a posição em que se encontra a chave primária encontrada
        {
            return i;
        }
        else if (flag > 0)
        {
            return -1;
        }
    }

    return -1;
}

/*Função que imprime os pokemons que tem um determinado nome ou pertencem a um determinado time*/
void imprimePokemonEquipe(FILE *fp, char *chave, Nome *vetorNomeEquipe, Indice *vetorIndice, int inicio, int tam)
{
    int i;
    Pokemon aux;

    for (i = inicio ; i < tam && !strcmp(vetorNomeEquipe[i].str, chave) ; i++)
    {
        aux = recuperaPokemon(fp, vetorIndice, buscaChavePrimaria(vetorNomeEquipe[i].codigo, vetorIndice, 0, tam));
        printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n", aux.codigo, aux.nomePokemon, aux.tipo, aux.cp, aux.data, aux.hora, aux.treinador, aux.nivelTreinador, aux.nomeEquipe);
    }
}

/*Função que ordena o vetor a partir da chave primária*/
void ordenaChavePrimaria(Indice *vet, int tam)
{
    qsort(vet, tam, sizeof(Indice), compare);
}

/*Função de comparação dos códigos para o qsort*/
int compare(const void *x, const void *y)
{
    Indice *m = (Indice*)x;
    Indice *n = (Indice*)y;

    return strcmp(m->codigo, n->codigo);
}

/*Função de comparação das strings, que podem ser tanto nome de equipe como nome do pokemon para o qsort*/
int compareNome(const void *x, const void *y)
{
    Nome *m = (Nome*)x;
    Nome *n = (Nome*)y;

    return strcmp(m->str, n->str);
}

/*Função que ordena o vetor a partir do nome do pokemon ou da equipe*/
void ordenaNome(Nome *vet, int tam)
{
    qsort(vet, tam, sizeof(Nome), compare);
    qsort(vet, tam, sizeof(Nome), compareNome);
}

/*Função que grava um pokemon no arquivo pokemons.dat*/
void gravaPokemonNoArquivo(FILE *fp, Pokemon info)
{
    int tam = 0;
    char str[194];
    strcpy(str, info.codigo);       //Formando a string que terá todos os dados do pokemon
    strcat(str, "@");
    strcat(str, info.nomePokemon);
    strcat(str, "@");
    strcat(str, info.tipo);
    strcat(str, "@");
    strcat(str, info.cp);
    strcat(str, "@");
    strcat(str, info.data);
    strcat(str, "@");
    strcat(str, info.hora);
    strcat(str, "@");
    strcat(str, info.treinador);
    strcat(str, "@");
    strcat(str, info.nivelTreinador);
    strcat(str, "@");
    strcat(str, info.nomeEquipe);
    strcat(str, "@");
    
    tam = strlen(str);

    for ( ; tam < 192 ; tam++)      //Completando a string com # até ter 192 bytes
    {
        strcat(str, "#");
    }

    str[tam] = '\0';

    fprintf(fp, "%s", str);     //Printando a string no arquivo
}

/*Função que grava o vetor de indice no arquivo*/
void gravaChavePrimaria(FILE *fp, Indice *vet, int tam)
{
    int i;

    fprintf(fp, "1\n");         //Gravando que o indice está atualizado

    for (i = 0 ; i < tam ; i++)     //Gravando o vetor que contem o código e o RRN no arquivo iprimary.idx
    {
        fprintf(fp, "%s %d\n", vet[i].codigo, vet[i].RRN); 
    }
}

/*Função que grava vetores com chave primaria a partir do nome do pokemon e nome da equipe*/
void gravaIndice(FILE *fp, Nome *vet, int tam)
{
    int i;      

    fprintf(fp, "1\n");     //Gravando que o indice está atualizado
    
    for (i = 0 ; i < tam ; i++)     //Gravando o vetor que contém o código e o nome ou equipe nos arquivos ipokemon.idx e iteam.idx
    {
        fprintf(fp, "%s %s\n", vet[i].codigo, vet[i].str); 
    }
}

/*Função que faz a leitura das chaves primarias e o RRN do arquivo*/
int leituraChaveRRN(FILE *fp, Indice *vet, int *i)
{
    int ok;

    fscanf(fp, "%d", &ok);      //Lendo se o arquivo está atualizado

    if (ok == 1)        //Se estiver atualizado le os dados do arquivo
    {
        while (fscanf(fp, "%s %d", vet[(*i)].codigo, &vet[(*i)].RRN) != EOF)
        {            
            (*i)++;
        }

        return 1;
    }
    else
    {
        return 0;
    }
}

/*Função que faz a leitura das chaves primarias, nome do pokemon e nome da equipe*/
int leituraNomeEquipe(FILE *fp, Nome *vet, int *i)
{
    int ok;

    fscanf(fp, "%d", &ok);      //Lendo se o arquivo está atualizado

    if (ok)     //Se estiver atualizado le os dados do arquivo
    {
        while (fscanf(fp, "%s %s", vet[(*i)].codigo, vet[(*i)].str) != EOF)
        {
            (*i)++;
        }

        return 1;
    }
    else
    {
        return 0;
    }
}

/*Função que recupera um pokemon do arquivo pokemons.dat a partir da chave primária*/
Pokemon recuperaPokemon(FILE *fp, Indice *vet, int posicaoVet)
{
    Pokemon aux;
    fseek(fp, (vet[posicaoVet].RRN-1)*192, SEEK_SET);       //Indo até a posição em que se encontra o pokemon

    fscanf(fp, "%[^@]s", aux.codigo);               //Recuperando o pokemon do arquivo
    fscanf(fp, "@%[^@]s", aux.nomePokemon);
    fscanf(fp, "@%[^@]s", aux.tipo);
    fscanf(fp, "@%[^@]s", aux.cp);
    fscanf(fp, "@%[^@]s", aux.data);
    fscanf(fp, "@%[^@]s", aux.hora);
    fscanf(fp, "@%[^@]s", aux.treinador);
    fscanf(fp, "@%[^@]s", aux.nivelTreinador);
    fscanf(fp, "@%[^@]s", aux.nomeEquipe);

    return aux;
}

/*Função que lista o pokemon a partir de um determinado código*/
void listaPokemonCodigo(FILE *fp, Indice *vet, int tam)
{
    int i;
    Pokemon aux;

    for (i = 0 ; i < tam ; i++)     //Andando o vetor que contém o código
    {
        if (vet[i].RRN != -1)       //Se o código for diferente de -1, está no pokemons.dat
        {   
            aux = recuperaPokemon(fp, vet, i);
            printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n", aux.codigo, aux.nomePokemon, aux.tipo, aux.cp, aux.data, aux.hora, aux.treinador, aux.nivelTreinador, aux.nomeEquipe);
        }        
    }
}

/*Função que lista os pokemons por equipe ou nome*/
void listaPokemonNomeEquipe(FILE *fp, Nome *vetorNomeEquipe, Indice *vetorIndice, int tam)
{
    int i, pos;
    Pokemon aux;

    for (i = 0 ; i < tam ; i++)     //Andando o vetor que contém o nome ou equipe e os códigos
    {
        pos = buscaChavePrimaria(vetorNomeEquipe[i].codigo, vetorIndice, 0, tam);       //Busca no vetor Indice a posição para recuperar o RRN

        if (pos != -1)      //Se a posição for diferente de -1, o pokemon pode ser listado
        {
            aux = recuperaPokemon(fp, vetorIndice, pos);
            printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n", aux.codigo, aux.nomePokemon, aux.tipo, aux.cp, aux.data, aux.hora, aux.treinador, aux.nivelTreinador, aux.nomeEquipe);
        }        
    }
}

/*Função que modifica o CP de um pokemon*/
void modificaCP(FILE *fp, Indice *vet, int tam)
{
    Pokemon aux;
    char cp[8], codigo[13];
    int pos;

    scanf("\n%[^\n]s", codigo);     //lendo o codigo do pokemon que tera o CP modificado

    pos = buscaChavePrimaria(codigo, vet, 0, tam);      //Recuperando a posição que esse pokemon se encontra no vetor indice

    if (pos == -1)      //Se a posição for -1, o pokemon não está no banco
    {
        printf("Registro não encontrado!\n");
        return;
    }

    do      //Lendo o cp para modificar
    {
        scanf("\n%[^\n]s", cp);

        if (!verificaCP(cp))
        {
            printf("Campo inválido!\n");
        }

    } while (!verificaCP(cp));

    fseek(fp, (vet[pos].RRN-1)*192, SEEK_SET);      //Indo até a posição para fazer a modificação

    fscanf(fp, "%[^@]s", aux.codigo);
    fscanf(fp, "@%[^@]s", aux.nomePokemon);
    fscanf(fp, "@%[^@]s@", aux.tipo);
    fprintf(fp, "@%s", cp);
    fseek(fp, 0 ,SEEK_END);
}

/*Função que marca um registro como removido*/
void marcaRegistro(FILE *fp, Indice *vet, char *chave, int tam)
{
    int pos;        
    char marca[3];
    marca[0] = '*';
    marca[1] = '|';
    marca[2] = '\0';

    deixaMaiusculo(chave);

    pos = buscaChavePrimaria(chave, vet, 0, tam);       //Recuperando a posição que esse pokemon se encontra no vetor indice

    if (pos == -1)      //Se a posição for -1, esse pokemon não está no banco
    {
        printf("Registro não encontrado!\n");
    }
    else        //Caso contrário esse pokemon está no banco
    {
        vet[pos].RRN = -1;
        fseek(fp, (vet[pos].RRN-1)*192, SEEK_SET);      //Marcando no banco que o pokemon foi "removido"
        fprintf(fp, "%s", marca);
        fseek(fp, 0, SEEK_END);
    }
}

/*Função que limpa o banco de dados*/
void limpaBanco(FILE *fp, Indice *vet, int tam)
{
    FILE *novo;
    Pokemon aux;
    int i;

    novo = fopen("pokemons2.dat", "w");     //Abrindo um novo arquivo para efetuar a cópia

    reeordenaRRN(vet, tam);     //reordenando o vetor de indices a partir do RRN

    for (i = 0 ; i < tam ; i++)     //Andando o vetor de RRN
    {
        if (vet[i].RRN != -1)       //Se o RRN for diferente de -1, pode recuperar do pokemons.dat e efetuar a cópia do pokemon
        {
            aux = recuperaPokemon(fp, vet, i);
            gravaPokemonNoArquivo(novo, aux);
        }
    }

    fclose(novo);       //Fechando o fluxo do novo arquivo
    remove("pokemons.dat");     //Removendo o banco antigo
    rename("pokemons2.dat", "pokemons.dat");        //Renomando o novo banco
}

/*Função que reeordena o vetor pelo RRN*/
void reeordenaRRN(Indice *vet, int tam)
{
    qsort(vet, tam, sizeof(Indice), compareRRN);
}

/*Função de comparação dos códigos para o qsort*/
int compareRRN(const void *x, const void *y)
{
    Indice *m = (Indice*)x;
    Indice *n = (Indice*)y;

    if (m->RRN < n->RRN)
    {
        return -1;
    }
    else if (m->RRN > n->RRN)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*Função que reconstroi os indices a partir do arquivo de dados*/
int reconstroiIndice(FILE *fp, Nome *nome, Nome *equipe, Indice *codigo)
{
    int i = 0;
    Pokemon aux;

    for (i = 0 ; !feof(fp) ; i++)       //Enquanto não for o fim do pokemons.dat, continua executando o laço
    {
        fseek(fp, i*192, SEEK_SET);     //Indo para a posição do próximo registro

        fscanf(fp, "%[^@]s", aux.codigo);       //Lendo o pokemon do arquivo
        fscanf(fp, "@%[^@]s", aux.nomePokemon);
        if (!verificaNome(aux.nomePokemon))
        {
            return 0;
        }
        fscanf(fp, "@%[^@]s", aux.tipo);
        fscanf(fp, "@%[^@]s", aux.cp);
        fscanf(fp, "@%[^@]s", aux.data);
        fscanf(fp, "@%[^@]s", aux.hora);
        fscanf(fp, "@%[^@]s", aux.treinador);
        fscanf(fp, "@%[^@]s", aux.nivelTreinador);
        fscanf(fp, "@%[^@]s", aux.nomeEquipe);

        strcpy(codigo[i].codigo, aux.codigo);       //Formando os vetor novamente
        codigo[i].RRN = i+1;

        strcpy(nome[i].codigo, aux.codigo);
        strcpy(nome[i].str, aux.nomePokemon);

        strcpy(equipe[i].codigo, aux.codigo);
        strcpy(equipe[i].str, aux.nomeEquipe);
    }

    ordenaChavePrimaria(codigo, i);     //Ordenando os vetores
    ordenaNome(nome, i);
    ordenaNome(equipe, i);

    return i;        
}

/*Função que deixa os caracteres maiusculos*/
void deixaMaiusculo(char *vet)
{
    int i = 0;

    while (vet[i] != '\0')        //Enquanto não chegar no final da string, deixa todas as letras maiusculas
    {
        vet[i] = toupper(vet[i]);
        i++;
    }
}