/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Estruturas de Dados 2
 * Prof. Tiago A. de Almeida
 *
 * Trabalho 03B - Hashing com encadeamento
 *
 * RA: 562262
 * Aluno: Ricardo Mendes Leal Junior
 * ========================================================================== */

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Tamanho dos campos dos registros */
#define	TAM_PRIMARY_KEY	13
#define	TAM_NOME		38
#define	TAM_TIPO		38
#define TAM_CP			8
#define	TAM_DATA		9
#define	TAM_HORA		6
#define	TAM_NIVEL		4

#define TAM_REGISTRO    192
#define MAX_REGISTROS   5000
#define TAM_ARQUIVO     (MAX_REGISTROS * TAM_REGISTRO + 1)

/* Saídas do usuário */
#define OPCAO_INVALIDA 			"Opcao invalida!\n\n"
#define REGISTRO_N_ENCONTRADO 	"Registro nao encontrado!\n\n"
#define CAMPO_INVALIDO 			"Campo invalido! Informe novamente.\n\n"
#define ERRO_PK_REPETIDA 		"ERRO: Ja existe um registro com a chave primaria: %s.\n\n"
#define REGISTRO_INSERIDO 		"Registro %s inserido com sucesso.\n\n"

/* Registro do Pokémon */
typedef struct {
	char primary_key[TAM_PRIMARY_KEY];
	char nome_pokemon[TAM_NOME];
	char tipo_pokemon[TAM_TIPO];
	char combat_points[TAM_CP];
	char data_captura[TAM_DATA]; 	// DD/MM/AA
	char hora_captura[TAM_HORA];	// HH:MM
	char nome_treinador[TAM_NOME];
	char nivel_treinador[TAM_NIVEL];
	char nome_equipe[TAM_NOME];
} Pokemon;

/* Registro da Tabela Hash
 * Contém a chave primária, o RRN do registro atual e o ponteiro para o próximo
 * registro. */
typedef struct chave Chave;
struct chave {
	char pk[TAM_PRIMARY_KEY];
	int rrn;
	Chave *prox;
};

/* Estrutura da Tabela Hash */
typedef struct {
  int tam;
  Chave **v;
} Hashtable;

/* Variáveis globais */
char ARQUIVO[TAM_ARQUIVO];
int n_registros;

/* ==========================================================================
 * ========================= PROTÓTIPOS DAS FUNÇÕES =========================
 * ========================================================================== */

/* Descarta o que estiver no buffer de entrada */
void ignore();

/* Recebe do usuário uma string simulando o arquivo completo. */
void carregar_arquivo();

/* Exibe o jogador */
void exibir_registro(int rrn);

/* <<< DECLARE AQUI OS PROTOTIPOS >>> */

/* =======================================
 * <<< Protótios de funções principais >>> 
 * ======================================= *

/*Função que encontra que verifica se um número é primo, caso não for encontra o próximo*/
int prox_primo(int num);

/*Função que cria a tabela Hash*/
void criar_tabela(Hashtable *t, int tam);

/*Função que carrega os valores da string ARQUIVO na tabela*/
void carregar_tabela(Hashtable *t);

/*Função que cadastra um pokemon no sistema*/
void cadastrar(Hashtable *t);

/*Função que imprime a tabela*/
void imprimir_tabela(Hashtable t);
 
/* =======================================
 * <<< Protótios de funções auxiliraes >>> 
 * ======================================= */

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

/*Função que deixa os caracteres maiusculos*/
void deixa_maiusculo(char *vet);

/*Função que recupera um pokemon da string ARQUIVO*/
Pokemon recuperar_registro(int rrn);

/*Função que ira inserir a nova chave na tabela, retornando 1 se inseriu normalmente ou 0 caso contrário*/
void insere_tabela(Hashtable *t, Chave a);

/*Função que ira inserir a nova chave na tabela, retornando 1 se inseriu normalmente ou 0 caso contrário*/
void insere_tabela_sem_comentario(Hashtable *t, Chave a);

/*Função que gera a chave primária de um novo registro*/
void geraChavePrimaria(Pokemon *info, Chave *chave);

/*Função que fara a inserção na tabela*/
int inserir(Hashtable *t, Chave a, int pos);

/*Função que grava os dados de um pokemon na string ARQUIVO*/
void insere_arquivo(Pokemon info);

/* ==========================================================================
 * ============================ FUNÇÃO PRINCIPAL ============================
 * =============================== NÃO ALTERAR ============================== */
int main() {

	/* Arquivo */
	int carregarArquivo = 0;
	scanf("%d\n", &carregarArquivo); // 1 (sim) | 0 (nao)
	if (carregarArquivo) carregar_arquivo();



	/* Tabela Hash */
	int tam;
	scanf("%d", &tam);
	tam = prox_primo(tam);

	Hashtable tabela;
	criar_tabela(&tabela, tam);
	if (carregarArquivo) carregar_tabela(&tabela);



	/* Execução do programa */
	int opcao = 0;
	while(opcao != 6) {
		scanf("%d", &opcao);
		switch(opcao) {

		case 1:
			getchar();
			cadastrar(&tabela);
			break;
		case 2:
			getchar();
			//alterar(tabela);
			break;
		case 3:
			getchar();
			//buscar(tabela);
			break;
		case 4:
		    getchar();
			//remover(&tabela);
			break;
		case 5:
			imprimir_tabela(tabela);
			break;
		case 6:
			//liberar_tabela(&tabela);
			break;

		case 10:
			printf("%s\n", ARQUIVO);
			break;

		default:
			ignore();
			printf(OPCAO_INVALIDA);
			break;
		}
	}
	return 0;
}



/* ==========================================================================
 * ================================= FUNÇÕES ================================
 * ========================================================================== */

/* Descarta o que estiver no buffer de entrada */
void ignore() {
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

/* Recebe do usuário uma string simulando o arquivo completo. */
void carregar_arquivo() {
	scanf("%[^\n]\n", ARQUIVO);
}

/* Exibe o Pokémon */
void exibir_registro(int rrn) {

	Pokemon p = recuperar_registro(rrn);

	printf("%s\n", p.primary_key);
	printf("%s\n", p.nome_pokemon);
	printf("%s\n", p.tipo_pokemon);
	printf("%s\n", p.combat_points);
	printf("%s\n", p.data_captura);
	printf("%s\n", p.hora_captura);
	printf("%s\n", p.nome_treinador);
	printf("%s\n", p.nivel_treinador);
	printf("%s\n", p.nome_equipe);
	printf("\n");
	
}


/* <<< IMPLEMENTE AQUI AS FUNCOES >>> */

/* ======================================================================= *
 * ========================= Funções principais ========================== *
 * ======================================================================= */

/*Função que encontra que verifica se um número é primo, caso não for encontra o próximo*/
int prox_primo(int num)
{
	int i, j, flag = 1;
	
	for (i = 2 ; i < num && flag; i++)		//Laço que percorre todos os número de 2 até o ultimo número antes
	{
		if (num % i == 0)		//Se o número for divisivel por qualquer outro número
		{
			flag = 0;		//Ele não é primo
		}
	}

	if (flag)		//Se o número for primo depois do laço
	{
		return num;		//Retorna esse número, pois ele é primo
	}
	else		//Caso contrário
	{
		for (i = num ; ; i++)		//Laço que procura o próximo primo
		{
			flag = 1;		//Assumimos que todos os números são primos		

			for (j = 2 ; j < i && flag; j++)		//Laço que percorre os números de 2 até j
			{
				if (i % j == 0)		//Se i for divisível por j, i não é primo
				{
					flag = 0;		//Marcamos que esse número i não é primo
				}
			}

			if (flag)		//Se o número continuar sendo primo
			{
				return i;		//Retorna o novo número primo
			}
		}
	}	
}

/*Função que cria a tabela Hash*/
void criar_tabela(Hashtable *t, int tam)
{
	int i;

	t->tam = tam;		//Colocando o tamanho da tabela na tabela
	t->v = malloc(tam*sizeof(Chave*));		//Alocando o vetor de ponteiros de chaves

    for (i = 0 ; i < tam ; i++)     //Laço para alocar as n primeiras chaves de cada posição do vetor de ponteiros
    {
        t->v[i] = malloc(sizeof(Chave));     //Alocando a chave e inicializando tudo com o valor 0 / NULL
		t->v[i]->prox = NULL;
	}
}

/*Função que carrega os valores da string ARQUIVO na tabela*/
void carregar_tabela(Hashtable *t)
{
	int i, pos;
	char *p = ARQUIVO;
	char pk[13];
	Chave a;

	n_registros = strlen(ARQUIVO) / TAM_REGISTRO;		//Descobrindo quantos registros estão na string ARQUIVO

	for (i = 0 ; n_registros > i ; i++)
	{
		sscanf(p, "%[^@]s", pk);       //Lendo o pokemon do pk
		strcpy(a.pk, pk);			//Copiando a chave lida para o campo pk da estrutura chave
		a.rrn = i;				//Passando o valor do RRN desta chave
		a.prox = NULL;		//Colocando que está posição está ocupada
		p = p + 192;			//Andando o ponteiro p
		insere_tabela_sem_comentario(t, a);
	}
}

/*Função que cadastra um pokemon no sistema*/
void cadastrar(Hashtable *t)
{
	Pokemon info;
	char aux[100];
	int retorno;
	Chave a;

	do      //Lendo os dados para formar um registro de um pokemon
    {
        scanf("\n%[^\n]s", aux);		//Lendo numa string auxiliar
        aux[TAM_NOME-1] = '\0';		//Truncando a string

        if (!verificaNome(aux))		//Se a string não for válida
        {
            printf(CAMPO_INVALIDO);		//Imprime que é um campo inválido na tela
        }

    } while (!verificaNome(aux));		//Executa a leitura até a string ser válida

    strcpy(info.nome_pokemon, aux);		//Após a entrada ser válida, copia para o campo da estrutura pokemon

    do
    {
        scanf("\n%[^\n]s", aux);
        aux[TAM_NOME-1] = '\0';

        if (!verificaTipoPokemon(aux))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaTipoPokemon(aux));

    strcpy(info.tipo_pokemon, aux);
    
    do
    {
        scanf("\n%[^\n]s", aux);
        aux[TAM_CP-1] = '\0';

        if (!verificaCP(aux))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaCP(aux));

    strcpy(info.combat_points, aux);
    
    do
    {
        scanf("\n%[^\n]s", aux);
        aux[TAM_DATA-1] = '\0';

        if (!verificaData(aux))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaData(aux));

    strcpy(info.data_captura, aux);
    
    do
    {
        scanf("\n%[^\n]s", aux);
        aux[TAM_HORA-1] = '\0';

        if (!verificaHora(aux))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaHora(aux));

    strcpy(info.hora_captura, aux);
    
    do
    {
        scanf("\n%[^\n]s", aux);
        aux[TAM_NOME-1] = '\0';

        if (!verificaTreinador(aux))
        {
            printf(CAMPO_INVALIDO);
        }

    } while(!verificaTreinador(aux));

    strcpy(info.nome_treinador, aux);  

    do
    {
        scanf("\n%[^\n]s", aux);
        aux[TAM_NIVEL-1] = '\0';

        if (!verificaNivel(aux))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaNivel(aux));

    strcpy(info.nivel_treinador, aux);

    do
    {
        scanf("\n%[^\n]s", aux);
        aux[TAM_NOME-1] = '\0';

        if (!verificaEquipe(aux))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaEquipe(aux));

	strcpy(info.nome_equipe, aux);

	geraChavePrimaria(&info, &a); //Gerando a chave primária do pokemon lido
	insere_tabela(t, a);		//Colocando a chave na tabela
	insere_arquivo(info);		//Inserindo na string ARQUIVO
	n_registros++;		//Atualizando o número de registros no sistema
}

/*Função que imprime a tabela*/
void imprimir_tabela(Hashtable t)
{
	int i;
	Chave *aux;

	for (i = 0 ; i < t.tam ; i++)		//Laço que percorre a tabela por inteiro listando ela
	{
		if (t.v[i]->prox == NULL)		//Se a posição estiver livre
		{
			printf("[%d]\n", i);		//Imprime que a posição está livre
		}
		else
		{
			printf("[%d]", i);
			aux = t.v[i]->prox;

			while (aux != NULL)
			{
				printf(" %s", aux->pk);
				aux = aux->prox;
			}
			printf("\n");
		}
	}
    //printf("\n");
}

/* ======================================================================= *
 * ========================= Funções auxiliares ========================== *
 * ======================================================================= */


/*Verifica se os caracteres do nome é válido*/
int verificaNome(char *nome)
{
    int i = 0;

    while (nome[i] != '\0')		//Andando o string até encontrar o \0
    {
        if ((nome[i] < 'A' || nome[i] > 'Z') && (nome[i] < 'a' || nome[i] > 'z'))		//Se algum caractere não for uma letra, o nome é inválido
        {
            return 0;
        }

        i++;
    }

    i = 0;

    while (nome[i] != '\0')		//Deixando todos os caracteres maiusculos
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

    while (tipo[i] != '\0')		//Andando a string até encontrar o \0
    {
        if (((tipo[i] < 'A' || tipo[i] > 'Z') && (tipo[i] < 'a' || tipo[i] > 'z')) && tipo[i] != '/')		//Se algum caractere não for letra e for diferente da barra, o tipo é inválido
        {
            return 0;
        }

        if (tipo[i] == '/')		//Se o caractere for /, entra no if
        {
            if (i == 0)		//Se a barra estiver na primeira posição, o tipo é inválido
            {
                return 0;
            }
            else if (tipo[i+1] == '\0')		//Se a barra estiver na ultima posição, o tipo é inválido
            {
                return 0;
            }
            
            flag++;		//Somando no contador que encontrou uma barra
        }
        
        if (flag == 2)		//Se tiver duas barras, o tipo é inválido
        {
            return 0;
        }

        i++;
    }

    i = 0;

    while (tipo[i] != '\0')		//Deixando todos os caracteres maiusculos
    {
        tipo[i] = toupper(tipo[i]);
        i++;
    }

    return 1;
}

/*Verifica se os caracteres do CP é válido*/
int verificaCP(char *cp)
{
    if (strlen(cp) != TAM_CP-1)
    {
        return 0;
    }
    if (cp[0] < '0' || cp[0] > '9')
    {
        return 0;
    }
    else if (cp[1] < '0' || cp[1] > '9')
    {
        return 0;
    }
    else if (cp[2] < '0' || cp[2] > '9')
    {
        return 0;
    }
    else if (cp[3] < '0' || cp[3] > '9')
    {
        return 0;
    }
    else if (cp[4] != '.')
    {
        return 0;
    }
    else if (cp[5] < '0' || cp[5] > '9')
    {
        return 0;
    }
    else if (cp[6] < '0' || cp[6] > '9')
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

/*Função que deixa os caracteres maiusculos*/
void deixa_maiusculo(char *vet)
{
    int i = 0;

    while (vet[i] != '\0')        //Enquanto não chegar no final da string, deixa todas as letras maiusculas
    {
        vet[i] = toupper(vet[i]);
        i++;
    }
}

/*Função que recupera um pokemon da string ARQUIVO*/
Pokemon recuperar_registro(int rrn)
{
	Pokemon aux;
    char *p;
    p = ARQUIVO + (192 * rrn);		//Fazendo com que o novo ponteiro vá para a posição correta para efetuar a leitura

    sscanf(p, "%[^@]s", aux.primary_key);       //Lendo os dados na variavel aux e andando o ponteiro p
    p = p + TAM_PRIMARY_KEY;

    sscanf(p, "%[^@]s", aux.nome_pokemon);
    p = p + strlen(aux.nome_pokemon)+1;

    sscanf(p, "%[^@]s", aux.tipo_pokemon);
    p = p + strlen(aux.tipo_pokemon)+1;

    sscanf(p, "%[^@]s", aux.combat_points);
    p = p + TAM_CP;

    sscanf(p, "%[^@]s", aux.data_captura);
    p = p + TAM_DATA;

    sscanf(p, "%[^@]s", aux.hora_captura);
    p = p + TAM_HORA;

    sscanf(p, "%[^@]s", aux.nome_treinador);
    p = p + strlen(aux.nome_treinador)+1;

    sscanf(p, "%[^@]s", aux.nivel_treinador);
    p = p + TAM_NIVEL;

    sscanf(p, "%[^@]s", aux.nome_equipe);

	return aux;
}

/*Função que gera a chave primária de um novo registro*/
void geraChavePrimaria(Pokemon *info, Chave *chave)
{
    info->primary_key[0] = info->nome_equipe[0];
    info->primary_key[1] = info->nome_treinador[0];
    info->primary_key[2] = info->nome_pokemon[0];
    info->primary_key[3] = info->nome_pokemon[1];
    info->primary_key[4] = info->data_captura[0];
    info->primary_key[5] = info->data_captura[1];
    info->primary_key[6] = info->data_captura[3];
    info->primary_key[7] = info->data_captura[4];
    info->primary_key[8] = info->hora_captura[0];
    info->primary_key[9] = info->hora_captura[1];
    info->primary_key[10] = info->hora_captura[3];
    info->primary_key[11] = info->hora_captura[4];
    info->primary_key[12] = '\0';

	strcpy(chave->pk, info->primary_key);
    chave->rrn = n_registros;
	chave->prox = NULL;
}

/*Função que ira inserir a nova chave na tabela e mostra o número de colisões*/
void insere_tabela_sem_comentario(Hashtable *t, Chave a)
{
	int pos = 0;

	pos = hash(a.pk, t->tam);		//Encontrando a posição para a inserção

	inserir(t, a, pos);		//Insere a chave na tabela
	//printf("Chave inserida: %s na posição %d\n", t->v[pos]->prox->pk, pos);
}

/*Função que ira inserir a nova chave na tabela e mostra o número de colisões*/
void insere_tabela(Hashtable *t, Chave a)
{
	int pos = 0;
	//printf("Inserindo a chave %s!\n", a.pk);

	pos = hash(a.pk, t->tam);		//Encontrando a posição para a inserção
	//printf("Posição da inserção: %d\n", pos);

	if (inserir(t, a, pos))		//Se a função tiver retornado um 1
	{
		printf(REGISTRO_INSERIDO, a.pk);		//Printa na tela que inseriu normalmente e quantas colisões houveram
	}
	else		//Caso contrário
	{
		printf(ERRO_PK_REPETIDA, a.pk);		//Printa na tela que a chave é repetida
	}
}

/*Função que fará o cálculo para inserir a nova chave na tabela*/
int hash(char *pk, int tam)
{
	int i, pos = 0;

	for (i = 0 ; i < TAM_PRIMARY_KEY-1 ; i++)		//Enquanto i for menor que 12, executa o laço
	{
		pos = pos + ((i+1) * pk[i]);		//Cálculo da função hash
	}

	return pos % tam;		//Depois do cálculo fazemos o valor mod T
}

/*Função que fara a inserção na tabela*/
int inserir(Hashtable *t, Chave a, int pos)
{
	Chave *novo, *aux;
	aux = t->v[pos];

	//printf("Endereço de aux: %p\n", aux);
	//printf("entrou na função inserir!\n");
	//printf("inserindo a chave %s\n\n", a.pk);

	if (aux->prox == NULL)		//Se a posição estiver livre
	{
		novo = malloc(sizeof(Chave));
		novo->prox = NULL;
		novo = &a;
		printf("chave da caixa: %s\n", novo->pk);
		printf("posicao: %d\n\n", pos);
		//printf("t->[%d] é null\n", pos);
		t->v[pos]->prox = novo;
		//printf("t->[%d].pk: %s\n\n", pos, t->v[pos]->pk);
		return 1;		//Retorna que a chave foi inserida normalmente
	}
	else
	{

		while (aux->prox != NULL && strcmp(aux->pk, a.pk) < 0)		//Enquanto não chegar no fim da lista e a chave da caixa 
		{															//Atual for menor que a chave nova, executa o laço
			aux = aux->prox;		//Andando pela lista		
		}

		// if (strcmp(aux->pk, a.pk) == 0)		//Se as chaves forem iguais
		// {
		// 	printf("chaves iguais!\n");
		// 	return 0;		//Retorna que não foi possível inserir a nova chave
		// }
		novo = malloc(sizeof(Chave));
		novo->prox = NULL;
		novo = &a;
		printf("colidiu na posicao %d\n", pos);
		printf("chave da caixa: %s\n\n", novo->pk);
		novo->prox = aux->prox;		//Organizando os ponteiros
		aux->prox = novo;
		return 1;		//Retorna que a chave foi inserida normalmente
				
	}
}

/*Função que grava os dados de um pokemon na string ARQUIVO*/
void insere_arquivo(Pokemon info)
{
    int i = 0, tam = 0;
    char *p = ARQUIVO;
    char str[194];
    p = p + (192 * n_registros);   
    
    strcpy(str, info.primary_key);       //Formando a string que terá todos os dados do pokemon
    strcat(str, "@");
    strcat(str, info.nome_pokemon);
    strcat(str, "@");
    strcat(str, info.tipo_pokemon);
    strcat(str, "@");
    strcat(str, info.combat_points);
    strcat(str, "@");
    strcat(str, info.data_captura);
    strcat(str, "@");
    strcat(str, info.hora_captura);
    strcat(str, "@");
    strcat(str, info.nome_treinador);
    strcat(str, "@");
    strcat(str, info.nivel_treinador);
    strcat(str, "@");
    strcat(str, info.nome_equipe);
    strcat(str, "@");

    tam = strlen(str);

    for ( ; tam < 192 ; tam++)      //Completando a string com # até ter 192 bytes
    {
        strcat(str, "#");
    }

    str[tam] = '\0';

    sprintf(p, "%s", str);     //Printando a string no arquivo
}