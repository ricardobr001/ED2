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
int ORDENADO_IPOKEMON;
int ORDENADO_ITEAM;

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

/*Função que grava os dados de um pokemon na string ARQUIVO*/
void insere_arquivo(Pokemon info, int rrn);

/*Função que coloca uma chave primaria a partir de uma equipe no vetor iteam*/
void guarda_equipe(Iteam *vet, char *primary_key, char *equipe, int i);

/*Função que inicializa a arvore B*/
void inicializa(Iprimary *arvore, int ordem);

/*Função que insere uma primary_key na arvore-B*/
int inserir(Iprimary *p, Chave a);

/*Função de inserir auxiliar*/
node_Btree* inserir_aux(node_Btree *p, Chave *aux, Chave a, int *flag_chave);

/*Função que divide o no da arvore B*/
node_Btree* divide_no(node_Btree *p, node_Btree *filho_direito, Chave *aux, Chave a, int *flag_chave);

/*Função que busca um código pokemon na árvore-B*/
node_Btree* busca_arvore(node_Btree *p, char *pk, int *pos);

/*Função que ira chamar as funções que ordenam o vetor ipokemon*/
void ordena_pokemon(Ipokemon *vet, int tam);

/*Quick sort aplicado para ordenar pelo nome do pokemon*/
void quick_sort_ipokemon_nome(Ipokemon *vet, int esq, int dir);

/*Quick sort aplicado para ordenar pela pk*/
void quick_sort_ipokemon_pk(Ipokemon *vet, int esq, int dir);

/*Função que ira chamar as funções que ordenam o vetor ipokemon*/
void ordena_time(Iteam *vet, int tam);

/*Quick sort aplicado para ordenar o time*/
void quick_sort_time(Iteam *vet, int esq, int dir);

/*Função que imprime a árvore-B no formato pre-order*/
void pre_order(node_Btree *p, int altura);

/*Função que exibe os pokemons na ordem do nome pokemon*/
void exibe_pokemon(node_Btree *p, Ipokemon *vet, int tam);

/*Função que exibe os pokemons na ordem do time*/
void exibe_time(node_Btree *p, Iteam *vet, int tam);

Pokemon recuperar_registro(int rrn);

/*Altera o CP de um pokemon na string ARQUIVO*/
void alterar_arquivo(Pokemon info, int rrn);

/*Função que procura um pokemon no vetor ipokemon*/
int busca_ipokemon(Ipokemon *vet, char *nome, int tam);

/*Função que exibe os pokemons do vetor Ipokemon da função busca*/
void exibe_pokemon_busca(Iprimary p, Ipokemon *vet, char *nome, int inicio, int tam);

/*Função que procura por uma equipe no vetor iteam*/
int busca_iteam(Iteam *vet, char *nome, int tam);

/*Função que exibe os pokemons do vetor Iteam da função busca*/
void exibe_time_busca(Iprimary p, Iteam *vet, char *nome, int inicio, int tam);

/*Função que busca um código pokemon na árvore-B e lista seus nós*/
node_Btree* busca_arvore_listando(node_Btree *p, char *pk, int *pos);

/*Função que deixa os caracteres maiusculos*/
void deixa_maiusculo(char *vet);

/*função que libera a arvore-B alocada*/
void apagar_no(node_Btree **p);

/* =======================================
 * <<< Protótios de funções principais >>> 
 * ======================================= */

 /*Função que cadastra um pokemon no sistema*/
 void cadastrar(Iprimary *iprimary, Ipokemon *ipokemon, Iteam *iteam, int *nregistros);

/*Função que cria uma arvore B para armazenar os dados primary_key e seu RRN*/
 void criar_iprimary(Iprimary *iprimary, int nregistros, int ordem);

/*Função que cria o indice secundário com os nomes dos pokemons*/
 void criar_ipokemon(Ipokemon *vet, int nregistros);

 /*Função que cria o indice secundário com as equipes*/
void criar_iteam(Iteam *vet, int nregistros);

/*Função que altera o CP de um pokemon*/
void alterar(Iprimary p);

/*Função que busca um pokemon por código, nome ou equipe*/
void buscar(Iprimary p, Ipokemon *vet_pokemon, Iteam *vet_team, int nregistros);

/*Função que irá listar as estruturas utilizadas no programa*/
void listar(Iprimary p, Ipokemon *vet_pokemon, Iteam *vet_time, int tam);

/* ==========================================================================
 * ============================ FUNÇÃO PRINCIPAL ============================
 * =============================== NÃO ALTERAR ============================== */
int main() {

    int i;
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
	criar_ipokemon(ipokemon, nregistros);

	/* Índice secundário de equipes */
	Iteam *iteam = (Iteam *) malloc (MAX_REGISTROS * sizeof(Iteam));
	if (!iteam) {
		perror(MEMORIA_INSUFICIENTE);
		exit(1);
	}
	criar_iteam(iteam, nregistros);

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
			alterar(iprimary);
			break;
		// Buscar um Pokémon
		case 3:
			buscar(iprimary, ipokemon, iteam, nregistros);
			break;
		// Listar todos os Pokémons
		case 4:
			listar(iprimary, ipokemon, iteam, nregistros);
			break;
		// Liberar a memória alocada
		case 5:
			apagar_no(&iprimary.raiz);
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

/*Função que grava os dados de um pokemon na string ARQUIVO*/
void insere_arquivo(Pokemon info, int rrn)
{
    int i = 0, tam = 0;
    char *p = ARQUIVO;
    char str[194];
    p = p + (192 * rrn);   
    
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
    int flag = 0;
    node_Btree *novo, *filho_direito = NULL;
    Chave aux;
    
    //printf("chave a ser inserida: %s\n", a.pk);

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
        filho_direito = inserir_aux(p->raiz, &aux, a, &flag);

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

        return 0;       //Se não retorna que não conseguiu inserir a chave nova
    }
}

/*Função de inserir auxiliar*/
node_Btree* inserir_aux(node_Btree *p, Chave *aux, Chave a, int *flag_chave)
{
    node_Btree *filho_direito = NULL;
    int i;

    if (p == NULL)      //Se o nó for nulo, retorna sem fazer nenhuma operação
    {
        *flag_chave = 0;
        return NULL;
    }

    if (p->folha == 1)        //Se for uma folha, entra no if
    {
        if(p->num_chaves < M-1)       //Se o numero de chaves nesta folha for menor que a ordem-1 da arvore, entra no if
        {
            i = p->num_chaves-1;      //Pegando o tamanho do vetor da folha, -1 para não acessar posição não alocada

            while (i >= 0 && strcmp(a.pk, p->chave[i].pk) < 0)       //Enquanto for maior que 0 e a pk a ser inserida for menor que a pk que já está na arvore, executa o while
            {       
                p->chave[i+1] = p->chave[i];                    //Copia a pk da posição atual do vetor para a proxima posição livre do vetor
                i--;
            }

            p->chave[i+1] = a;            //Copia a pk da posição atual do vetor para a proxima posição livre do vetor
            p->num_chaves++;        //Atualizando o numero de chaves que este nó possui
            *flag_chave = 0;
            return NULL;
        }
        else        //Caso contrário, houve um overflow na folha
        {
            return divide_no(p, NULL, aux, a, flag_chave);     //Implementar
        }
    }
    else
    {
        i = p->num_chaves-1;      //Pegando o tamanho do vetor da folha, -1 para não acessar posição não alocada

        while (i >= 0  && strcmp(a.pk, p->chave[i].pk) < 0)
        {
            i--;
        }

        i++;
        filho_direito = inserir_aux(p->desc[i], aux, a, flag_chave);

        if ((*flag_chave))       //Se a chave promovida for diferente de NULL, entra no if
        {

            strcpy(a.pk, aux->pk);       //Copia a chave promovida para a chave a ser inserida
            a.rrn = aux->rrn;

            if(p->num_chaves < M-1)
            {
                i = p->num_chaves-1;      //Pegando o tamanho do vetor da folha, -1 para não acessar posição não alocada
                
                while (i >= 0 && strcmp(a.pk, p->chave[i].pk) < 0)
                {
                    p->chave[i+1] = p->chave[i];                    //Copia a pk da posição atual do vetor para a proxima posição livre do vetor
                    p->desc[i+2] = p->desc[i+1];                      //Copia o ponteiro para a proxima subArvore, junto com a sua pk
                    i--;
                }

                p->chave[i+1] = a;                    //Copia a pk da posição atual do vetor para a proxima posição livre do vetor
                p->desc[i+2] = filho_direito;                
                p->num_chaves = p->num_chaves + 1;       //Atualizando o numero de chaves que este nó possui
                *flag_chave = 0;
                return NULL;
            }
            else        //Caso contrário, propagou o overflow
            {
                return divide_no(p, filho_direito, aux, a, flag_chave);
            }
        }
        else        //Caso contrário, não houve overflow
        {
            *flag_chave = 0;
            return NULL;
        }
    }
}

/*Função que divide o no da arvore B*/
node_Btree* divide_no(node_Btree *p, node_Btree *filho_direito, Chave *aux, Chave a, int *flag_chave)
{
    int i, j, flag = 0, pos;
    node_Btree *novo;

    pos = floor((M-1)/2);

    if (p == NULL)
    {
        *flag_chave = 0;
        return NULL;
    }

    i = p->num_chaves - 1;         //Pegando o tamanho do vetor da folha, -1 para não acessar posição não alocada

    novo = malloc(sizeof(node_Btree));                  //Alocando o novo nó Y e atribuindo os valores
    novo->chave = malloc((M - 1)*sizeof(Chave));
    novo->desc = malloc(M*sizeof(node_Btree*));
    novo->folha = p->folha;
    novo->num_chaves = pos;

    for (j = novo->num_chaves-1 ; j >= 0 ; j--)         //Efetuando a copia dos dados da folha X para a folha Y até que a chave primaria seja colocada
    {
        if (!flag && strcmp(a.pk, p->chave[i].pk) > 0)       //Se não tiver colocado a chave primaria ainda e a chave for maior do que a da folha X
        {                                                           //Coloca a chave na folha y seu ponteiro do filho direito e assinala que ja colocou a chave primaria
            novo->chave[j] = a;
            novo->desc[j+1] = filho_direito;
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
        while(i >= 0 && strcmp(a.pk, p->chave[i].pk) < 0)       //Enquanto não for o fim do vetor da folha e a chave primaria for maior
        {                                                               //Do que a chave que se encontra na posição i
            p->chave[i+1] = p->chave[i];            //Empurra os dados para a frente
            p->desc[i+2] = p->desc[i+1];
            i--;
        }

        p->chave[i+1] = a;
        p->desc[i+2] = filho_direito;
    }

    pos = floor((M)/2);
    *aux = p->chave[pos];
    novo->desc[0] = p->desc[pos+1];
    p->num_chaves = pos;
    *flag_chave = 1;
    return novo;
}

/*Função que recupera um pokemon da string ARQUIVO*/
Pokemon recuperar_registro(int rrn)
{
    Pokemon aux;
    char *p;
    p = ARQUIVO + (192 * rrn);

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

/*Função que busca um código pokemon na árvore-B*/
node_Btree* busca_arvore(node_Btree *p, char *pk, int *pos)
{
    int i = 0;

    if (p == NULL)
    {
        return NULL;
    }

    while (i < p->num_chaves && strcmp(pk, p->chave[i].pk) > 0)     //Andando o vetor do nó até encontrar uma chave igual
    {
        i++;
    }

    if (i < p->num_chaves && strcmp(pk, p->chave[i].pk) == 0)       //Se a chave for a que procuramos, retorna o nó
    {
        *pos = i;
        return p;
    }

    if (p->folha)
    {
        return NULL;
    }
    else
    {
        return busca_arvore(p->desc[i], pk, pos);
    }
}

/*Função que ira chamar as funções que ordenam o vetor ipokemon*/
void ordena_pokemon(Ipokemon *vet, int tam)
{
    quick_sort_ipokemon_pk(vet, 0, tam-1);
    quick_sort_ipokemon_nome(vet, 0, tam-1);
}

/*Quick sort aplicado para ordenar pela pk*/
void quick_sort_ipokemon_pk(Ipokemon *vet, int esq, int dir)
{
    int pivo, i, j;
    Ipokemon chave;
    pivo = esq;

    for (i = esq+1 ; i <= dir ; i++)        //Percorrendo o subvetor da esquerda até a direita
    {
        j = i;

        if (strcmp(vet[j].primary_key, vet[pivo].primary_key) < 0)      //Se o vetor na posição j for menor que o vetor no pivo
        {
            chave = vet[j];     //Copiando os valores para uma variável auxiliar
        
            while (j > pivo)        //Enquanto j for maior que o pivo
            {
                vet[j] = vet[j-1];      //Copia todos os pokemons para frente
                j--;
            }

            vet[j] = chave;      //Coloca os dados na ultima posição [pivo]
            pivo++;
        }
    }

    if (pivo-1 >= esq)
    {
        quick_sort_ipokemon_pk(vet, esq, pivo-1);
    }
    if(pivo+1 <= dir)
    {
        quick_sort_ipokemon_pk(vet, pivo+1, dir);
    }
}

/*Quick sort aplicado para ordenar pelo nome do pokemon*/
void quick_sort_ipokemon_nome(Ipokemon *vet, int esq, int dir)
{
    int pivo, i, j;
    Ipokemon chave;
    pivo = esq;

    for (i = esq+1 ; i <= dir ; i++)        //Percorrendo o subvetor da esquerda até a direita
    {
        j = i;

        if (strcmp(vet[j].nome_pokemon, vet[pivo].nome_pokemon) < 0)      //Se o vetor na posição j for menor que o vetor no pivo
        {
            chave = vet[j];    //Copiando os valores para uma variável auxiliar
        
            while (j > pivo)        //Enquanto j for maior que o pivo
            {
                vet[j] = vet[j-1];      //Copia todos os pokemons para frente
                j--;
            }
        
            vet[j] = chave;      //Coloca os dados na ultima posição [pivo]
            pivo++;
        }
    }

    if (pivo-1 >= esq)
    {
        quick_sort_ipokemon_nome(vet, esq, pivo-1);
    }
    if(pivo+1 <= dir)
    {
        quick_sort_ipokemon_nome(vet, pivo+1, dir);
    }
}

/*Função que ira chamar as funções que ordenam o vetor ipokemon*/
void ordena_time(Iteam *vet, int tam)
{
    quick_sort_time(vet, 0, tam-1);       //Ordenaremos pela pk
}

/*Quick sort aplicado para ordenar o time*/
void quick_sort_time(Iteam *vet, int esq, int dir)
{
    int pivo, i, j;
    Iteam chave;
    pivo = esq;

    for (i = esq+1 ; i <= dir ; i++)        //Percorrendo o subvetor da esquerda até a direita
    {
        j = i;

        if (strcmp(vet[j].primary_key, vet[pivo].primary_key) < 0)      //Se o vetor na posição j for menor que o vetor no pivo
        {
            chave = vet[j];     //Copiando os valores para uma variável auxiliar
        
            while (j > pivo)        //Enquanto j for maior que o pivo
            {
                vet[j] = vet[j-1];      //Copia todos os pokemons para frente
                j--;
            }

            vet[j] = chave;      //Coloca os dados na ultima posição [pivo]
            pivo++;
        }
    }

    if (pivo-1 >= esq)
    {
        quick_sort_time(vet, esq, pivo-1);
    }
    if(pivo+1 <= dir)
    {
        quick_sort_time(vet, pivo+1, dir);
    }
}

/*Função que exibe os pokemons na ordem do nome pokemon*/
void exibe_pokemon(node_Btree *p, Ipokemon *vet, int tam)
{
    int i, pos;
    node_Btree *res;
    
    for (i = 0 ; i < tam ; i++)     //Andando o vetor
    {
        res = busca_arvore(p, vet[i].primary_key, &pos);        //Efetua a busca na arvore-B de um pokemon a partir de sua pk
        exibir_registro(res->chave[pos].rrn);                     //Exibe o pokemon que foi encontrado
    }
}

/*Função que exibe os pokemons na ordem do time*/
void exibe_time(node_Btree *p, Iteam *vet, int tam)
{
    int i, pos;
    node_Btree *res;
    
    for (i = 0 ; i < tam ; i++)     //Andando o vetor
    {
        res = busca_arvore(p, vet[i].primary_key, &pos);        //Efetua a busca na arvore-B de um pokemon a partir de sua pk
        exibir_registro(res->chave[pos].rrn);                     //Exibe o pokemon que foi encontrado
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

/*Função que procura um pokemon no vetor ipokemon*/
int busca_ipokemon(Ipokemon *vet, char *nome, int tam)
{
    int i, flag;

    for (i = 0 ; i < tam ; i++)
    {
        flag = strcmp(vet[i].nome_pokemon, nome);

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

/*Função que procura por uma equipe no vetor iteam*/
int busca_iteam(Iteam *vet, char *nome, int tam)
{
    int i, flag;

    for (i = 0 ; i < tam ; i++)
    {
        flag = strcmp(vet[i].nome_equipe, nome);

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

/*Função que exibe os pokemons do vetor Ipokemon da função busca*/
void exibe_pokemon_busca(Iprimary p, Ipokemon *vet, char *nome, int inicio, int tam)
{
    int i, pos;
    node_Btree *res;

    for (i = inicio ; i < tam && !strcmp(vet[i].nome_pokemon, nome) ; i++)
    {
        res = busca_arvore(p.raiz, vet[i].primary_key, &pos);
        exibir_registro(res->chave[pos].rrn);
    }
}

/*Função que exibe os pokemons do vetor Iteam da função busca*/
void exibe_time_busca(Iprimary p, Iteam *vet, char *nome, int inicio, int tam)
{
    int i, pos;
    node_Btree *res;

    for (i = inicio ; i < tam && !strcmp(vet[i].nome_equipe, nome) ; i++)
    {
        res = busca_arvore(p.raiz, vet[i].primary_key, &pos);
        exibir_registro(res->chave[pos].rrn);
    }
}

/*Função que busca um código pokemon na árvore-B e lista seus nós*/
node_Btree* busca_arvore_listando(node_Btree *p, char *pk, int *pos)
{
    int i = 0;

    if (p == NULL) {
        return NULL;
    }
    else {
        for (i = 0 ; i < p->num_chaves ; i++)
        {
            if (p->num_chaves == 1 && i == 0)
            {
                printf("%s\n", p->chave[i].pk);
            }
            else if (i+1 == p->num_chaves)
            {
                printf("%s\n", p->chave[i].pk);
            }
            else if (i < p->num_chaves)
            {
                printf("%s, ", p->chave[i].pk);
            }
        }

        i = 0;

        while (i < p->num_chaves && strcmp(pk, p->chave[i].pk) > 0)     //Andando o vetor do nó até encontrar uma chave igual
        {
            i++;
        }

        if (i < p->num_chaves && strcmp(pk, p->chave[i].pk) == 0)       //Se a chave for a que procuramos, retorna o nó
        {
            *pos = i;
            return p;
        }

        if (p->folha)
        {
            return NULL;
        }
        else
        {
            return busca_arvore_listando(p->desc[i], pk, pos);
        }
    }
}

/*Função que imprime a árvore-B no formato pre-order*/
void pre_order(node_Btree *p, int altura) {
    int i;

	if (p != NULL)
    {
        printf("%d - ", altura);
        for (i = 0 ; i < M ; i++)
        {
            if (p->num_chaves == 1 && i == 0)
            {
                printf("%s\n", p->chave[i].pk);
            }
            else if (i+1 == p->num_chaves)
            {
                printf("%s\n", p->chave[i].pk);
            }
            else if (i < p->num_chaves)
            {
                printf("%s, ", p->chave[i].pk);
            }
        }
        for (i = 0 ; i <= p->num_chaves ; i++)
        {
            pre_order(p->desc[i], altura+1);
        }         
    }
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
     char pk[13];
     Chave a;

     inicializa(iprimary, ordem);

     for (i = 0 ; nregistros > 0 ; i++, nregistros--)
     {
         sscanf(p, "%[^@]s", pk);       //Lendo o pokemon do pk
         strcpy(a.pk, pk);
         a.rrn = i;
         p = p + 192;
         inserir(iprimary, a);
     }
 }

/*Função que cria o indice secundário com os nomes dos pokemons*/
void criar_ipokemon(Ipokemon *vet, int nregistros)
{
    int i;
    char *p = ARQUIVO;
    char pk[13], nome_pokemon[38];

    for (i = 0 ; i < nregistros ; i++)
    {
        sscanf(p, "%[^@]s", pk);
        p = p + TAM_PRIMARY_KEY;
        sscanf(p, "%[^@]s", nome_pokemon);
        p = p - TAM_PRIMARY_KEY + 192;
        guarda_pokemon(vet, pk, nome_pokemon, i);
    }

    ORDENADO_IPOKEMON = 0;
}

/*Função que cria o indice secundário com as equipes*/
void criar_iteam(Iteam *vet, int nregistros)
{
    int i;
    char *p = ARQUIVO;
    Pokemon aux;

    for (i = 0 ; i < nregistros ; i++)
    {
        aux = recuperar_registro(i);
        guarda_equipe(vet, aux.primary_key, aux.nome_equipe, i);
    }

    ORDENADO_ITEAM = 0;
}

/*Função que cadastra um pokemon no sistema*/
void cadastrar(Iprimary *iprimary, Ipokemon *ipokemon, Iteam *iteam, int *nregistros)
{
    int lixo=0;
	Pokemon info;
    Chave chave;
    char aux[100];
    node_Btree *busca;

    do      //Lendo os dados para formar um registro de um pokemon
    {
        scanf("\n%[^\n]s", aux);
        aux[TAM_NOME-1] = '\0';

        if (!verificaNome(aux))
        {
            printf(CAMPO_INVALIDO);
        }

    } while (!verificaNome(aux));

    strcpy(info.nome_pokemon, aux);

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

    geraChavePrimaria(&info, &chave, *nregistros);      //Gerando a chave primária do pokemon lido

    busca = busca_arvore(iprimary->raiz, info.primary_key, &lixo);      //Efetuando a busca na árvore-B
    
	if (busca != NULL)       //Caso essa chave já exista na árvore-B
	{
		printf(ERRO_PK_REPETIDA, info.primary_key);     //Printa que a chave é repetida
	}
	else        //aso contrário
	{		
        inserir(iprimary, chave);                                                       //Insere os dados na árvore-B e nos vetores iteam e ipokemon
		guarda_pokemon(ipokemon, info.primary_key, info.nome_pokemon, *nregistros);
		guarda_equipe(iteam, info.primary_key, info.nome_equipe, *nregistros);
        insere_arquivo(info, *nregistros);                                              //Também insere os dados na string ARQUIVO
        ORDENADO_IPOKEMON = 0;                      //Marca nas variaveis globais que os vetores iteam e ipokemon não estão ordenados
        ORDENADO_ITEAM = 0;
		(*nregistros)++;            //Somando o contador do número de registros
	}	
}

/*Função que altera o CP de um pokemon*/
void alterar(Iprimary p)
{
    int i;
    char aux_pk[100], aux_cp[50];
    Pokemon info;
    node_Btree *resultado;

    scanf("\n%[^\n]s", aux_pk);                 //Lendo a primary_key
    aux_pk[TAM_PRIMARY_KEY-1] = '\0';           //Truncando a string, caso tenha tamanho maior que 12 bytes
    deixa_maiusculo(aux_pk);                    //Deixando a string maiuscula
    resultado = busca_arvore(p.raiz, aux_pk, &i);       //Efetuando a busca da primary_key na árvore-B

    if (resultado == NULL)      //Se o resultado da busca for NULL
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

        alterar_arquivo(info, resultado->chave[i].rrn);         //Altera o CP na string ARQUIVO
    }
}

/*Função que busca um pokemon por código, nome ou equipe*/
void buscar(Iprimary p, Ipokemon *vet_pokemon, Iteam *vet_team, int nregistros)
{
    int op, i;
    char busca[100];
    node_Btree *resultado;

    scanf("%d", &op);

    switch (op)
    {
        case 1:
            scanf("\n%[^\n]s", busca);              //Lendo a primary_key
            busca[TAM_PRIMARY_KEY-1] = '\0';        //Truncando a string, caso tenha tamanho maior que 12 bytes
            deixa_maiusculo(busca);                 //Deixando a string maiuscula
            printf(NOS_PERCORRIDOS, busca);
            resultado = busca_arvore_listando(p.raiz, busca, &i);       //Efetuando a busca pela árvore-B
            printf("\n");

            if (resultado == NULL)          //Se não tiver encontrado a chave
            {
                printf(REGISTRO_N_ENCONTRADO);      //Imprime na tela que o registro não foi encontrado
            }
            else            //Caso contrário
            {
                exibir_registro(resultado->chave[i].rrn);       //Exibe o registro
            }
        break;

        case 2:
            scanf("\n%[^\n]s", busca);              //Lendo o nome do pokemon
            busca[TAM_NOME-1] = '\0';               //Truncando a string, caso tenha tamanho maior que 38 bytes
            deixa_maiusculo(busca);                 //Deixando a string maiuscula

            if (ORDENADO_IPOKEMON == 0)         //Se o vetor não estiver ordenado
            {
                ordena_pokemon(vet_pokemon, nregistros);        //Ordena ele e marca na variavel global que o vetor está ordenado
                ORDENADO_IPOKEMON = 1;
            }

            i = busca_ipokemon(vet_pokemon, busca, nregistros);     //Efetua a busca no vetor ipokemon

            if (i == -1)        //Se o retorno da busca for -1
            {
                printf(REGISTRO_N_ENCONTRADO);      //Significa que não encontrou o pokemon procurado, portanto printa na tela que não encontrou o seu registro
            }
            else        //Caso contrário
            {
                exibe_pokemon_busca(p, vet_pokemon, busca, i, nregistros);      //Exibe o registro
            }
        break;

        case 3:
            scanf("\n%[^\n]s", busca);          //Lendo a equipe
            busca[TAM_NOME-1] = '\0';           //Truncando a string, caso tenha tamanho maior que 38 bytes
            deixa_maiusculo(busca);             //Deixando a string maiuscula

            if (ORDENADO_ITEAM == 0)        //Se o vetor não estiver ordenado
            {
                ordena_time(vet_team, nregistros);      //Ordena ele e marca na variavel global que o vetor está ordenado
                ORDENADO_ITEAM = 1;
            }
            
            i = busca_iteam(vet_team, busca, nregistros);       //Efetua a busca no vetor iteam

            if(i == -1)         //Se o retorno da busca for -1
            {
                printf(REGISTRO_N_ENCONTRADO);      //Significa que não encontrou nenhum pokemon daquela equipe
            }
            else        //Caso contrário
            {
                exibe_time_busca(p, vet_team, busca, i, nregistros);        //Exibe o registro
            }
        break;
    }
}

/*Função que irá listar as estruturas utilizadas no programa*/
void listar(Iprimary p, Ipokemon *vet_pokemon, Iteam *vet_time, int tam)
{
    int op, i;

    scanf("%d", &op);       //Lendo a opção de listagem

    switch (op)
    {
        case 1:
            pre_order(p.raiz, 1);       //Caso for 1, lista a árvore-B na forma pre-order
            printf("\n");
        break;

        case 2:
            if (ORDENADO_IPOKEMON == 0)     //Se o vetor não estiver ordenado
            {
                ordena_pokemon(vet_pokemon, tam);       //Ordena ele e marca na variavel global que o vetor está ordenado
                ORDENADO_IPOKEMON = 1;
            }
            
            exibe_pokemon(p.raiz, vet_pokemon, tam);        //Exibe os registros do vetor ipokemon
        break;

        case 3:
            if (ORDENADO_ITEAM == 0)        //Se o vetor não estiver ordenado
            {
                ordena_time(vet_time, tam);         //Ordena ele e marca na variavel global que o vetor está ordenado
            }
            
            exibe_time(p.raiz, vet_time, tam);      //Exibe os registros do vetor iteam
        break;
    }
}

/*função que libera a arvore-B alocada*/
void apagar_no(node_Btree **p)
{
    int i;

    if ((*p) != NULL)       //Se o conteúdo do ponteiro não for nulo
    {
        for (i = 0 ; i <= (**p).num_chaves ; i++)       //Chama recursivamente a função para descer na árvore-B 
        {
            apagar_no(&(**p).desc[i]);
        }

        free((**p).desc);       //Liberando a memória alocada
        free((**p).chave);
        free((*p));
    }
}