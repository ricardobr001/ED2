/* ==========================================================================
 * Universidade Federal de S�o Carlos - Campus Sorocaba
 * Disciplina: Estruturas de Dados 2
 * Prof. Tiago A. de Almeida
 *
 * Trabalho 03A - Hashing com reespalhamento linear
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

/* Sa�das do usu�rio */
#define OPCAO_INVALIDA 			"Opcao invalida!\n\n"
#define REGISTRO_N_ENCONTRADO	"Registro nao encontrado!\n\n"
#define CAMPO_INVALIDO 			"Campo invalido! Informe novamente.\n\n"
#define ERRO_PK_REPETIDA 		"ERRO: Ja existe um registro com a chave primaria: %s.\n\n"
#define ERRO_TABELA_CHEIA 		"ERRO: Tabela Hash esta cheia!\n\n"
#define REGISTRO_INSERIDO 		"Registro %s inserido com sucesso. Numero de colisoes: %d.\n\n"

#define POS_OCUPADA 	"[%d] Ocupado: %s\n"
#define POS_LIVRE 		"[%d] Livre\n"
#define POS_REMOVIDA 	"[%d] Removido\n"

/* Estado das posi��es da tabela hash */
#define LIVRE       0
#define OCUPADO     1
#define REMOVIDO    2

/* Registro do Pok�mon */
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
 * Cont�m o estado da posi��o, a chave prim�ria e o RRN do respectivo registro */
typedef struct {
	int estado;
	char pk[TAM_PRIMARY_KEY];
	int rrn;
} Chave;

/* Estrutura da Tabela Hash */
typedef struct {
  int tam;
  Chave *v;
} Hashtable;

/* Vari�veis globais */
char ARQUIVO[TAM_ARQUIVO];
int n_registros;

/* ==========================================================================
 * ========================= PROT�TIPOS DAS FUN��ES =========================
 * ========================================================================== */

/* Descarta o que estiver no buffer de entrada */
void ignore();

/* Recebe do usu�rio uma string simulando o arquivo completo. */
void carregar_arquivo();

/* Exibe o jogador */
void exibir_registro(int rrn);

/* <<< DECLARE AQUI OS PROTOTIPOS >>> */

/* =======================================
 * <<< Protótios de funções principais >>> 
 * ======================================= */
 
/*Função que encontra que verifica se um número é primo, caso não for encontra o próximo*/
int prox_primo(int num);

/*Função que cria a tabela Hash*/
void criar_tabela(Hashtable *t, int tam);

/*Função que carrega os valores da string ARQUIVO na tabela*/
void carregar_tabela(Hashtable *t);

/*Função que cadastra um pokemon no sistema*/
void cadastrar(Hashtable *t);

/*Função que altera o CP de um pokemon*/
void alterar(Hashtable t);

/*Função que imprime a tabela*/
void imprimir_tabela(Hashtable t);

/*Função que busca uma chave na tabela*/
void buscar(Hashtable t);

/*Função que remove uma pk da tabela*/
void remover(Hashtable *t);

/*Função que libera a memória alocada*/
void liberar_tabela(Hashtable *t);

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

/*Função que ira inserir a nova chave na tabela e mostrará número de colisões*/
void insere_tabela_nao_listar(Hashtable *t, Chave a);

/*Função que ira inserir a nova chave na tabela e mostra o número de colisões*/
void insere_tabela_listando(Hashtable *t, Chave a);

/*Função que fará o cálculo para inserir a nova chave na tabela*/
int hash(char *pk, int tam);

/*Função que fara a inserção na tabela*/
int inserir(Hashtable *t, Chave a, int pos);

/*Função que gera a chave primária de um novo registro*/
void geraChavePrimaria(Pokemon *info, Chave *chave);

/*Função que grava os dados de um pokemon na string ARQUIVO*/
void insere_arquivo(Pokemon info);

/*Altera o CP de um pokemon na string ARQUIVO*/
void alterar_arquivo(Pokemon info, int rrn);

/* ==========================================================================
 * ============================ FUN��O PRINCIPAL ============================
 * =============================== N�O ALTERAR ============================== */
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



	/* Execu��o do programa */
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
			alterar(tabela);
			break;
		case 3:
			getchar();
			buscar(tabela);
			break;
		case 4:
		    getchar();
			remover(&tabela);
			break;
		case 5:
			imprimir_tabela(tabela);
			break;
		case 6:
			liberar_tabela(&tabela);
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
 * ================================= FUN��ES ================================
 * ========================================================================== */

/* Descarta o que estiver no buffer de entrada */
void ignore() {
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

/* Recebe do usu�rio uma string simulando o arquivo completo. */
void carregar_arquivo() {
	scanf("%[^\n]\n", ARQUIVO);
}

/* Exibe o Pok�mon */
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
	t->tam = tam;		//Colocando o tamanho da tabela na tabela
	t->v = calloc(tam, sizeof(Chave));		//Alocando o vetor de chaves e inicializando tudo com 0
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
		a.estado = OCUPADO;		//Colocando que está posição está ocupada
        // printf("Chave que está sendo colocada!\n");
        // printf("%s\n", a.pk);
        // printf("ESTADO: %d\n", a.estado);
        // printf("RRN: %d\n", a.rrn);
		p = p + 192;			//Andando o ponteiro p
		insere_tabela_nao_listar(t, a);
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
	insere_tabela_listando(t, a);		//Colocando a chave na tabela
	insere_arquivo(info);		//Inserindo na string ARQUIVO
	n_registros++;		//Atualizando o número de registros no sistema	
}

/*Função que altera o CP de um pokemon*/
void alterar(Hashtable t)
{
    int resultado;
    char aux_pk[100], aux_cp[50];
    Pokemon info;

    scanf("\n%[^\n]s", aux_pk);                 //Lendo a primary_key
    aux_pk[TAM_PRIMARY_KEY-1] = '\0';           //Truncando a string, caso tenha tamanho maior que 12 bytes
    deixa_maiusculo(aux_pk);                    //Deixando a string maiuscula
    resultado = busca_tabela(&t, aux_pk);       //Efetuando a busca da primary_key na tabela

    if (resultado == -1)      //Se o resultado da busca for -1
    {
        printf(REGISTRO_N_ENCONTRADO);      //Significa que não encontrou a primary_key na árvore e printa na tela que não encontrou o registro
        return;
    }
    else        //Caso contrário
    {
        do
        {
            scanf("\n%[^\n]s", aux_cp);     //Lendo o cp numa string auxiliar
            aux_cp[TAM_CP-1] = '\0';        //Truncando a string, caso tenha tamanho maior que 7 bytes

            if (!verificaCP(aux_cp))        //Verificando se o CP é válido
            {
                printf(CAMPO_INVALIDO);     //Caso for inválido, imprime na tela que o cp está incorreto e solicitar o dado novamente
            }

        } while (!verificaCP(aux_cp));      //Enquanto não digitar um CP válido, mantém o laço

        strcpy(info.combat_points, aux_cp);     //Copia a string auxiliar para a estrutura pokemons

        alterar_arquivo(info, t.v[resultado].rrn);         //Altera o CP na string ARQUIVO
    }
}

/*Função que imprime a tabela*/
void imprimir_tabela(Hashtable t)
{
	int i;

	for (i = 0 ; i < t.tam ; i++)		//Laço que percorre a tabela por inteiro listando ela
	{
		if (t.v[i].estado == LIVRE)		//Se a posição estiver livre
		{
			printf(POS_LIVRE, i);		//Imprime que a posição está livre
		}
		else if (t.v[i].estado == OCUPADO)		//Se a posição estiver ocupada
		{
			printf(POS_OCUPADA, i, t.v[i].pk);		//Imprime que a posição está ocupada e sua pk
		}
		else		//Se não a posição foi removida
		{
			printf(POS_REMOVIDA, i);		//Imprime que a posição foi removida
		}
	}
    printf("\n");
}

/*Função que busca uma chave na tabela*/
void buscar(Hashtable t)
{
    int resultado;
    char aux_pk[100];
    Pokemon info;

    scanf("\n%[^\n]s", aux_pk);                 //Lendo a primary_key
    aux_pk[TAM_PRIMARY_KEY-1] = '\0';           //Truncando a string, caso tenha tamanho maior que 12 bytes
    deixa_maiusculo(aux_pk);                    //Deixando a string maiuscula
    printf("buscando pela chave %s\n", aux_pk);
    resultado = busca_tabela(&t, aux_pk);       //Efetuando a busca da primary_key na tabela
    printf("posição que a busca retornou: %d\n", resultado);

    if (resultado == -1)      //Se o resultado da busca for -1
    {
        printf(REGISTRO_N_ENCONTRADO);      //Significa que não encontrou a primary_key na árvore e printa na tela que não encontrou o registro
        return;
    }
    else        //Caso contrário
    {
        info = recuperar_registro(t.v[resultado].rrn);      //Recuperando um pokemon da string ARQUIVO
        exibir_registro(t.v[resultado].rrn);        //Exibindo seu conteúdo na tela
    }
}

/*Função que remove uma pk da tabela*/
void remover(Hashtable *t)
{
    int resultado;
    char aux_pk[100];

    scanf("\n%[^\n]s", aux_pk);                 //Lendo a primary_key
    aux_pk[TAM_PRIMARY_KEY-1] = '\0';           //Truncando a string, caso tenha tamanho maior que 12 bytes
    deixa_maiusculo(aux_pk);                    //Deixando a string maiuscula
    resultado = busca_tabela(t, aux_pk);       //Efetuando a busca da primary_key na tabela
    printf("retornou a posição: %d\n", resultado);

    if (resultado == -1)      //Se o resultado da busca for -1
    {
        printf(REGISTRO_N_ENCONTRADO);      //Significa que não encontrou a primary_key na árvore e printa na tela que não encontrou o registro
        return;
    }
    else        //Caso contrário
    {
        t->v[resultado].pk[0] = '*';        //Marcando que esse pokemon foi removido na sua pk
        t->v[resultado].pk[1] = '|';        
        t->v[resultado].estado = REMOVIDO;      //Marcando também no seu estado
        printf("chave: %s\nEstado: %d\n", t->v[resultado].pk, t->v[resultado].estado);
    }
}

/*Função que libera a memória alocada*/
void liberar_tabela(Hashtable *t)
{
    free(t->v);     //Liberando o vetor de chaves
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

/*Função que ira inserir a nova chave na tabela e sem mostrar o número de colisões*/
void insere_tabela_nao_listar(Hashtable *t, Chave a)
{
	int i, pos = 0;

	pos = hash(a.pk, t->tam);		//Encontrando a posição para a inserção
	i = inserir(t, a, pos);	//Inserindo o valor na tabela
}

/*Função que ira inserir a nova chave na tabela e mostra o número de colisões*/
void insere_tabela_listando(Hashtable *t, Chave a)
{
	int i, pos = 0;

	pos = hash(a.pk, t->tam);		//Encontrando a posição para a inserção
	i = inserir(t, a, pos);	//Inserindo o valor na tabela

	if (i >= 0)		//Se a função tiver retornado um número maior ou igual a 0, inseriu normalmente
	{
		printf(REGISTRO_INSERIDO, a.pk, i);		//Printa na tela que inseriu normalmente e quantas colisões houveram
	}
	else if (i == -1)		//Se a função tiver retornado -1, a chave é repetida
	{
		printf(ERRO_PK_REPETIDA, a.pk);		//Printa na tela que a chave é repetida
	}
	else		//Caso contrário a tabela está cheia
	{
		printf(ERRO_TABELA_CHEIA);		//Printa na tela que a tabela está cheia
	}
}

/*Função que fara a inserção na tabela*/
int inserir(Hashtable *t, Chave a, int pos)
{
	int i = 0, aux;
	aux = pos;

	if (t->v[pos].estado == LIVRE || t->v[pos].estado == REMOVIDO)		//Se a posição estiver livre
	{
		t->v[pos] = a;		//Insere a chave na tabela e retorna que não houve colisões
        //printf("Não houve colisão, colocado na posição %d\n", pos);
		return 0;
	}
	else
	{
		pos++;		//Como a posição está ocupada, pegamos a próxima
		i++;		//Já houve uma colisão

		while (t->v[pos].estado == OCUPADO && pos != aux)		//Enquanto a posição estiver ocupada, executa o laço
		{
			if (pos == t->tam-1)		//Se a posição for a última
			{
				pos = 0;		//Vamos para a primeira posição da tabela, pois a tabela é circular
			}
			else
			{
				i++;		//Contando quantas colisões houveram
				pos++;		//Pegando a próxima posição
			}			
		}

        //printf("Houve colisão, colocado na posição %d\n", i);

		if (pos == aux)		//Se paramos o laço e voltamos para a primeira posição
		{
			return -2;		//A tabela está cheia
		}
		else		//Se não inserimos o valor na tabela
		{
            t->v[pos] = a;
			return i;		//Retornamos quantas colisões aconteceram
		}
	}
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
	chave->estado = OCUPADO;
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

/*Função que busca uma pk na tabela*/
int busca_tabela(Hashtable *t, char *pk)
{
	int pos, aux;

    printf("chave: %s\n", pk);
	pos = hash(pk, t->tam);
    printf("posiçao: %d\n", pos);
	aux = pos;
    
    if (strcmp(t->v[pos].pk, pk) == 0)		//Se a pk na posição for a pk procurada, retorna essa posição
    {
        return pos;
    }
    else       //Se a chave não estiver na posição correta, procuramos pela tabela 
    {
        pos++;      //Verificamos a próxima posição

        while (t->v[pos].estado == OCUPADO && pos != aux)		//Enquanto a posição estiver ocupada, executa o laço
        {
            if (strcmp(t->v[pos].pk, pk) == 0)		//Se a pk na posição for a pk procurada, retorna essa posição
            {
                return pos;
            }

            if (pos == t->tam-1)		//Se a posição for a última
            {
                pos = -1;		//Vamos para a primeira posição da tabela, pois a tabela é circular
            }			
            else
            {
                pos++;		//Pegando a próxima posição
            }			
        }
    }

	if (pos == aux)		//Se paramos o laço e voltamos para a primeira posição
	{
		return -1;		//A chave procurada não está na tabela
	}
	else		//Se não encontramos a pk
	{
		return pos;		//Retornamos a posição na qual a pk se encontra
	}
}

/*Altera o CP de um pokemon na string ARQUIVO*/
void alterar_arquivo(Pokemon info, int rrn)
{
    char *p;
    p = ARQUIVO + (192 * rrn);

    sscanf(p, "%[^@]s", info.primary_key);       //Lendo os dados na variavel info e andando o ponteiro p
    p = p + TAM_PRIMARY_KEY;

    sscanf(p, "%[^@]s", info.nome_pokemon);
    p = p + strlen(info.nome_pokemon)+1;

    sscanf(p, "%[^@]s", info.tipo_pokemon);
    p = p + strlen(info.tipo_pokemon)+1;

    sprintf(p, "%s", info.combat_points);
    p = p + TAM_CP-1;

    *p = '@';
}