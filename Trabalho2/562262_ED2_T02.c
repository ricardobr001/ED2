/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Estruturas de Dados 2
 * Prof. Tiago A. de Almeida
 *
 * Trabalho 02 - Árvore B
 *
 * RA: 562262
 * Aluno: Ricardo Mendes Leal Junior
 * ========================================================================== */


/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


/* Tamanho dos campos dos registros */
#define	TAM_PRIMARY_KEY	13
#define	TAM_NOME		38
#define	TAM_TIPO		38
#define TAM_CP			8
#define	TAM_DATA		9
#define	TAM_HORA		6
#define	TAM_NIVEL		4

#define TAM_REGISTRO    192
#define MAX_REGISTROS   10000
#define TAM_ARQUIVO     (MAX_REGISTROS * TAM_REGISTRO + 1)


/* Saídas do usuário */
#define OPCAO_INVALIDA          "Opcao invalida!\n"
#define MEMORIA_INSUFICIENTE    "Memoria insuficiente!"
#define REGISTRO_N_ENCONTRADO   "Registro nao encontrado!\n\n"
#define CAMPO_INVALIDO          "Campo invalido! Informe novamente.\n"
#define ERRO_PK_REPETIDA        "ERRO: Ja existe um registro com a chave primaria: %s.\n"
#define ARQUIVO_VAZIO           "Arquivo vazio!"
#define NOS_PERCORRIDOS         "Busca por %s. Nos percorridos:\n"


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


/* Registro da Árvore-B
 * Contém a chave primária e o RRN do respectivo registro */
typedef struct {
	char pk[TAM_PRIMARY_KEY];	// chave primária
	int rrn;					// rrn do registro
} Chave;


/* Estrutura da Árvore-B */
typedef struct node node_Btree;
struct node {
	int num_chaves;		// numero de chaves armazenadas
	Chave *chave;		// vetor das chaves e rrns [m-1]
	node_Btree **desc;	// ponteiros para os descendentes, *desc[m]
	int folha;			// flag folha da arvore
};

typedef struct {
	node_Btree *raiz;
} Iprimary;


/* Registro do índice secundário - ipokemon.idx
 * Contém o nome do Pokémon e a chave primária do registro */
typedef struct {
	char nome_pokemon[TAM_NOME];
	char primary_key[TAM_PRIMARY_KEY];
} Ipokemon;


/* Registro do índice secundário - iteam.idx
 * Contém o nome da equipe e a chave primária do registro */
typedef struct {
	char nome_equipe[TAM_NOME];
	char primary_key[TAM_PRIMARY_KEY];
} Iteam;


/* Variáveis globais */
char ARQUIVO[TAM_ARQUIVO];
int M;

/* ==========================================================================
 * ========================= PROTÓTIPOS DAS FUNÇÕES =========================
 * ========================================================================== */

/* Recebe do usuário uma string simulando o arquivo completo e retorna o número
 * de registros. */
int carregar_arquivo();

/* Exibe o Pokémon */
void exibir_registro(int rrn);

/* <<< DECLARE AQUI OS PROTOTIPOS >>> */
void ignore();

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

/*Função que gera a chave primária de um novo registro*/
void geraChavePrimaria(Pokemon *info, Chave *chave, int RRN);

/*Função que coloca uma chave primaria a partir de um nome pokemon no vetor ipokemon*/
void guarda_pokemon(Ipokemon *vet, char *primary_key, char *nome, int i);

/*Função que coloca uma chave primaria a partir de uma equipe no vetor iteam*/
void guarda_equipe(Iteam *vet, char *primary_key, char *equipe, int i);

/*Função que inicializa a arvore B*/
void inicializa(Iprimary *arvore, int ordem);

/*Função que insere uma primary_key na arvore-B*/
int inserir(Iprimary *p, Chave a);

/*Função de inserir auxiliar*/
void inserir_aux(node_Btree *p, node_Btree *filho_direito, Chave *aux, Chave a, int *flag_chave, int *flag_repetido);

/*Função que divide o no da arvore B*/
node_Btree* divide_no(node_Btree *p, node_Btree *filho_direito, Chave *aux, Chave a, int *flag_chave);

void inorder(node_Btree *p);

Pokemon recuperar_registro(int rrn);

/* =======================================
 * <<< Protótios de funções principais >>> 
 * ======================================= */

 /*Função que cadastra um pokemon no sistema*/
 void cadastrar(Iprimary *iprimary, Ipokemon *ipokemon, Iteam *iteam, int *nregistros);

/*Função que cria uma arvore B para armazenar os dados primary_key e seu RRN*/
 void criar_iprimary(Iprimary *iprimary, int nregistros, int ordem);

/* ==========================================================================
 * ============================ FUNÇÃO PRINCIPAL ============================
 * =============================== NÃO ALTERAR ============================== */
int main() {

	/* Arquivo */
	int carregarArquivo = 0, nregistros = 0;
	scanf("%d\n", &carregarArquivo); // 1 (sim) | 0 (nao)
	if (carregarArquivo) {
		nregistros = carregar_arquivo();
	}

	/* Índice primário */
	int ordem;
	scanf("%d", &ordem);
	Iprimary iprimary;
	criar_iprimary(&iprimary, nregistros, ordem);

	/* Índice secundário de nomes de Pokémon */
	Ipokemon *ipokemon = (Ipokemon *) malloc (MAX_REGISTROS * sizeof(Ipokemon));
	if (!ipokemon) {
		perror(MEMORIA_INSUFICIENTE);
		exit(1);
	}
	//criar_ipokemon(ipokemon, nregistros);

	/* Índice secundário de equipes */
	Iteam *iteam = (Iteam *) malloc (MAX_REGISTROS * sizeof(Iteam));
	if (!iteam) {
		perror(MEMORIA_INSUFICIENTE);
		exit(1);
	}
	//criar_iteam(iteam, nregistros);

	/* Execução do programa */
	int opcao = 0;
	while(opcao != 5) {
		scanf("%d", &opcao);
		switch(opcao) {
		// Cadastrar um novo Pokémon
		case 1:
			getchar();
			cadastrar(&iprimary, ipokemon, iteam, &nregistros);
			break;
		// Alterar os combat points de um Pokémon
		case 2:
			getchar();
			//alterar(iprimary);
			break;
		// Buscar um Pokémon
		case 3:
			//buscar(iprimary, ipokemon, iteam, nregistros);
			break;
		// Listar todos os Pokémons
		case 4:
			//listar(iprimary, ipokemon, iteam, nregistros);
			break;
		// Liberar a memória alocada
		case 5:
			//apagar_no(&iprimary.raiz);
            inorder(iprimary.raiz);
			free(ipokemon);
			free(iteam);
			break;
        // Imprimir o arquivo de dados
		case 10:
			printf("%s\n", ARQUIVO);
			break;
        // Ignora a entrada e exibe mensagem de erro
		default:
			ignore();
			printf(OPCAO_INVALIDA);
			break;
		}
	}
	return 0;
}

/* ==========================================================================
 * =============================== AUXILIARES ===============================
 * ========================================================================== */

/* Descarta o que estiver no buffer de entrada */
void ignore() {
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

/* <<< IMPLEMENTE AQUI AS FUNCOES AUXILIARES >>> */

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
void geraChavePrimaria(Pokemon *info, Chave *chave, int RRN)
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
    chave->rrn = RRN;
}

/*Função que coloca uma chave primaria a partir de um nome pokemon no vetor ipokemon*/
void guarda_pokemon(Ipokemon *vet, char *primary_key, char *nome, int i)
{
    strcpy(vet[i].primary_key, primary_key);
    strcpy(vet[i].nome_pokemon, nome);
}

/*Função que coloca uma chave primaria a partir de uma equipe no vetor iteam*/
void guarda_equipe(Iteam *vet, char *primary_key, char *equipe, int i)
{
    strcpy(vet[i].primary_key, primary_key);
    strcpy(vet[i].nome_equipe, equipe);
}

/*Função que inicializa a arvore B*/
void inicializa(Iprimary *arvore, int ordem)
{
    arvore->raiz = NULL;
    M = ordem;
}

/*Função que insere uma primary_key na arvore-B*/
int inserir(Iprimary *p, Chave a)
{   
    int flag = 0, flag_repetido = 0;
    node_Btree *novo, *filho_direito = NULL;
    Chave aux;
    

    if (p->raiz == NULL)        //Se a raiz for nula, apenas insere a chave na primeira posição do vetor na folha
    {
        novo = malloc(sizeof(node_Btree));
        novo->chave = malloc((M - 1)*sizeof(Chave));
        novo->chave[0] = a;
        novo->desc = malloc(M*sizeof(node_Btree*));
        novo->desc[0] = NULL;
        novo->desc[1] = NULL;
        novo->folha = 1;
        novo->num_chaves = 1;
        p->raiz = novo;
        return 1;
    }
    else        //Se não chama a função inserir_aux
    {
        inserir_aux(p->raiz, filho_direito, &aux, a, &flag, &flag_repetido);

        if (flag) //Se a chave promovida não for nula
        {
            novo = malloc(sizeof(node_Btree));
            novo->chave = malloc((M - 1)*sizeof(Chave));
            novo->desc = malloc(M*sizeof(node_Btree*));
            novo->folha = 0;
            novo->num_chaves = 1;
            novo->chave[0] = aux;
            novo->desc[0] = p->raiz;
            novo->desc[1] = filho_direito;

            p->raiz = novo;
            return 1;
        }

        if (!flag_repetido)     //Se a flag de chave repetida for falsa, retorna que inseriu a chave nova com sucesso
        {
            return 1;
        }

        return 0;       //Se não retorna que não conseguiu inserir a chave nova
    }
}

/*Função de inserir auxiliar*/
void inserir_aux(node_Btree *p, node_Btree *filho_direito, Chave *aux, Chave a, int *flag_chave, int *flag_repetido)
{
    int i;

    if (p == NULL)      //Se o nó for nulo, retorna sem fazer nenhuma operação
    {
        return;
    }

    if (p->folha == 1)        //Se for uma folha, entra no if
    {
        if(p->num_chaves < M-1)       //Se o numero de chaves nesta folha for menor que a ordem-1 da arvore, entra no if
        {
            i = p->num_chaves-1;      //Pegando o tamanho do vetor da folha, -1 para não acessar posição não alocada

            while (i >= 0 && strcmp(a.pk, p->chave[i].pk) == -1)       //Enquanto for maior que 0 e a pk a ser inserida for menor que a pk que já está na arvore, executa o while
            {       
                p->chave[i+1] = p->chave[i];                    //Copia a pk da posição atual do vetor para a proxima posição livre do vetor
                p->desc[i+1] = p->desc[i];                      //Copia o ponteiro para a proxima subArvore, junto com a sua pk
                i--;
            }

            if (!strcmp(a.pk, p->chave[i].pk))      //Se a chave a ser inserida for igual a chave que o while parou
            {                                       //A chave é repetida
                *flag_repetido = 1;
                return;
            }

            p->chave[i+1] = a;            //Copia a pk da posição atual do vetor para a proxima posição livre do vetor

            p->num_chaves++;        //Atualizando o numero de chaves que este nó possui

            filho_direito = NULL;
            return;
        }
        else
        {
            filho_direito = divide_no(p, NULL, aux, a, flag_chave);     //Implementar
        }
    }
    else
    {
        i = p->num_chaves-1;      //Pegando o tamanho do vetor da folha, -1 para não acessar posição não alocada

        while (i >= 0  && strcmp(a.pk, p->chave[i].pk) == -1)
        {
            i--;
        }

        i++;
        inserir_aux(p->desc[i], filho_direito, aux, a, flag_chave, flag_repetido);

        if (flag_chave)        //Se a chave promovida for diferente de NULL, entra no if
        {
            printf("ocorreu overflow!\n");
            strcpy(a.pk, aux->pk);       //Copia a chave promovida para a chave a ser inserida

            if(p->num_chaves < M-1)
            {
                i = p->num_chaves-1;      //Pegando o tamanho do vetor da folha, -1 para não acessar posição não alocada
                
                while (i >= 0 && strcmp(a.pk, p->chave[i].pk) == -1)
                {
                    p->chave[i+1] = p->chave[i];                    //Copia a pk da posição atual do vetor para a proxima posição livre do vetor
                    p->desc[i+2] = p->desc[i+1];                      //Copia o ponteiro para a proxima subArvore, junto com a sua pk
                    i--;
                }

                if (!strcmp(a.pk, p->chave[i].pk))      //Se a chave a ser inserida for igual a chave que o while parou
                {                                       //A chave é repetida
                    *flag_repetido = 1;
                    return;
                }

                p->chave[i+1] = p->chave[i];                    //Copia a pk da posição atual do vetor para a proxima posição livre do vetor
                p->desc[i+2] = filho_direito;
                
                p->num_chaves = p->num_chaves + 1;       //Atualizando o numero de chaves que este nó possui
            
                return;
            }
            else
            {
                filho_direito = divide_no(p, filho_direito, aux, a, flag_chave);
            }
        }
        else
        {
            return;
        }
    }
}

/*Função que divide o no da arvore B*/
node_Btree* divide_no(node_Btree *p, node_Btree *filho_direito, Chave *aux, Chave a, int *flag_chave)
{
    int i, j, flag = 0, pos;
    node_Btree *novo;

    pos = floor(M/2);

    if (p == NULL)
    {
        return;
    }

    i = p->num_chaves - 1;         //Pegando o tamanho do vetor da folha, -1 para não acessar posição não alocada

    novo = malloc(sizeof(node_Btree));                  //Alocando o novo nó Y e atribuindo os valores
    novo->chave = malloc((M - 1)*sizeof(Chave));
    novo->desc = malloc(M*sizeof(node_Btree*));
    novo->desc[0] = NULL;
    novo->desc[1] = NULL;
    novo->folha = p->folha;
    novo->num_chaves = pos;

    for (j = novo->num_chaves-1 ; j >= 0 ; j--)         //Efetuando a copia dos dados da folha X para a folha Y até que a chave primaria seja colocada
    {
        if (!flag && strcmp(a.pk, p->chave[i].pk) == 1)       //Se não tiver colocado a chave primaria ainda e a chave for maior do que a da folha X
        {                                                           //Coloca a chave na folha y seu ponteiro do filho direito e assinala que ja colocou a chave primaria
            p->chave[j] = a;
            p->desc[j+1] = filho_direito;
            flag = 1;
        }
        else        //Se não copia a chave da folha X para a Y
        {
            novo->chave[j] = p->chave[i];
            novo->desc[j+1] = p->desc[i+1];
            i--;
        }
    }

    if (!flag)      //Se a chave primaria não tiver sido colocada
    {
        while(i >= 0 && strcmp(a.pk, p->chave[i].pk) == -1)       //Enquanto não for o fim do vetor da folha e a chave primaria for maior
        {                                                               //Do que a chave que se encontra na posição i
            p->chave[i+1] = p->chave[i];            //Empurra os dados para a frente
            p->desc[i+2] = p->desc[i+1];
            i--;
        }

        p->chave[i+1] = a;
        p->desc[i+2] = filho_direito;
    }

    *aux = p->chave[pos+1];
    novo->desc[0] = p->desc[pos+2];
    p->num_chaves = pos;
    *flag_chave = 1;
    return novo;
}

Pokemon recuperar_registro(int rrn)
{
    Pokemon aux;
    char *p = ARQUIVO;
    p = p + (192 * rrn);

    sscanf(p, "%[^@]s", aux.primary_key);       //Lendo o pokemon do p
    sscanf(p, "@%[^@]s", aux.nome_pokemon);
    sscanf(p, "@%[^@]s", aux.tipo_pokemon);
    sscanf(p, "@%[^@]s", aux.combat_points);
    sscanf(p, "@%[^@]s", aux.data_captura);
    sscanf(p, "@%[^@]s", aux.hora_captura);
    sscanf(p, "@%[^@]s", aux.nome_treinador);
    sscanf(p, "@%[^@]s", aux.nivel_treinador);
    sscanf(p, "@%[^@]s", aux.nome_equipe);

    return aux;
}

/* ==========================================================================
 * ================================= FUNÇÕES ================================
 * ========================================================================== */

/* Recebe do usuário uma string simulando o arquivo completo e retorna o número
 * de registros. */
int carregar_arquivo() {
	scanf("%[^\n]\n", ARQUIVO);
	return strlen(ARQUIVO) / TAM_REGISTRO;
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

/* <<< IMPLEMENTE AQUI AS FUNCOES PRINCIPAIS >>> */

/*Função que cria uma arvore B para armazenar os dados primary_key e seu RRN*/
 void criar_iprimary(Iprimary *iprimary, int nregistros, int ordem)
 {
     int i;
     char *p = ARQUIVO;
     Pokemon aux;
     Chave a;

     inicializa(iprimary, ordem);

     for (i = 0 ; nregistros > 0 ; i++, nregistros--)
     {
         sscanf(p, "%[^@]s", aux.primary_key);       //Lendo o pokemon do p
         sscanf(p, "@%[^@]s", aux.nome_pokemon);
         sscanf(p, "@%[^@]s", aux.tipo_pokemon);
         sscanf(p, "@%[^@]s", aux.combat_points);
         sscanf(p, "@%[^@]s", aux.data_captura);
         sscanf(p, "@%[^@]s", aux.hora_captura);
         sscanf(p, "@%[^@]s", aux.nome_treinador);
         sscanf(p, "@%[^@]s", aux.nivel_treinador);
         sscanf(p, "@%[^@]s", aux.nome_equipe);
         p = p + 192;
         geraChavePrimaria(&aux, &a, i);
         inserir(iprimary, a);
     }
 }

/*Função que cadastra um pokemon no sistema*/
void cadastrar(Iprimary *iprimary, Ipokemon *ipokemon, Iteam *iteam, int *nregistros)
{
	Pokemon info;
    Chave chave;

    do      //Lendo os dados para formar um registro de um pokemon
    {
        scanf("\n%[^\n]s", info.nome_pokemon);

        if (!verificaNome(info.nome_pokemon))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaNome(info.nome_pokemon));

    do
    {
        scanf("\n%[^\n]s", info.tipo_pokemon);

        if (!verificaTipoPokemon(info.tipo_pokemon))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaTipoPokemon(info.tipo_pokemon));
    
    do
    {
        scanf("\n%[^\n]s", info.combat_points);

        if (!verificaCP(info.combat_points))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaCP(info.combat_points));
    
    do
    {
        scanf("\n%[^\n]s", info.data_captura);

        if (!verificaData(info.data_captura))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaData(info.data_captura));
    
    do
    {
        scanf("\n%[^\n]s", info.hora_captura);

        if (!verificaHora(info.hora_captura))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaHora(info.hora_captura));
    
    do
    {
        scanf("\n%[^\n]s", info.nome_treinador);

        if (!verificaTreinador(info.nome_treinador))
        {
            printf(CAMPO_INVALIDO);
        }

    } while(!verificaTreinador(info.nome_treinador));    

    do
    {
        scanf("\n%[^\n]s", info.nivel_treinador);

        if (!verificaNivel(info.nivel_treinador))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaNivel(info.nivel_treinador));

    do
    {
        scanf("\n%[^\n]s", info.nome_equipe);

        if (!verificaEquipe(info.nome_equipe))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaEquipe(info.nome_equipe));

    geraChavePrimaria(&info, &chave, *nregistros);      //Gerando a chave primária do pokemon lido

	if (!inserir(iprimary, chave))       //Caso a inserção na árvore-B não ocorra
	{
		printf(ERRO_PK_REPETIDA, info.primary_key);     //Printa que a chave é repetida
	}
	else        //Se não completa os dois vetores, time e nome pokemon
	{		
		//guarda_pokemon(ipokemon, info.primary_key, info.nome_pokemon, *nregistros);
		//guarda_time(iteam, info.primary_key, info.nome_equipe, *nregistros);
		(*nregistros)++;
	}	
}

void inorder(node_Btree *p) {
    int i;
	if (p != NULL) {
        for (i = 0 ; i < M-1 ; i++)
        {
            inorder(p->desc[i]);
            printf("%s\n", p->chave[i].pk); 
        }   
	}
}