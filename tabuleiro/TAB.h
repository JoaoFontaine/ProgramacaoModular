
/**************************************************************************************
*
*	$MCD Módulo de definição: TAB  Tabuleiro de xadrez
*
*	Arquivo gerado:              TAB.h
*	Letras identificadoras:      TAB
*
*	Projeto: INF 1301 Jogo de Xadrez
*	Autores: Guilherme Araujo e João Pedro Fontaine
*
*
*	$ED Descrição do módulo
*		Implementa um tabuleiro de xadrez com suas funcionalidades.
*		Podem existir n tabuleiros em operação simultaneamente.
*		
*		O tabuleiro tem 64 casas dispostas em 8 colunas e 8 linhas. Cada casa possui 
*			um ponteiro para uma peça, que assume o valor NULL quando a mesma está
*			vazia, um ponteiro para a cabeça de uma lista de peças que ameaçam esta 
*			casa e outro ponteiro para a cabeça de uma lista de casas que são
*			ameaçadas pela peça que está nesta casa.
*
**************************************************************************************/

/* Tipo exportado que referencia a estrutura tabuleiro */

typedef struct TAB_tagCasa * TAB_tppCasa;

typedef struct TAB_tagPeca {

	char nome;
	/* Nome da peca */
	char cor;
	/* Cor da peca */

	#ifdef _DEBUG

		TAB_tppCasa pCasa;
		/*ponteiro para a casa*/

	#endif

} tpPeca ;

typedef struct TAB_tagTab * TAB_tppTab ;

/* Tipo exportado que referencia a estrutura peca */
typedef struct TAB_tagPeca * TAB_tppPeca;

/* Condicoes de retorno do modulo tabuleiro */
typedef enum {

	TAB_CondRetOK = 0,
	/* Concluiu corretamente */

	TAB_CondRetNaoExiste = 1 ,
	/* O tabuleiro nao existe */

	TAB_CondRetCasaVazia = 2,
	/* A casa nao contem peca */

	TAB_CondRetMovInv = 3,
	/* Movimento de peca invalido */

	TAB_CondRetCaptPeca = 4,
	/* Capturou peca inimiga */

	TAB_CondRetCasaCheia = 5,
	/* A casa ja contem peca */

	TAB_CondRetCasaInvalida = 6,
	/* A casa nao pertence ao tabuleiro */

	TAB_CondRetPecaBloqueando = 7,
	/* A casa nao pertence ao tabuleiro */

	TAB_CondRetPecaInvalida = 8,
	/* A casa nao pertence ao tabuleiro */

	TAB_CondRetXeque = 9,
	/* O Rei está em xeque */

	TAB_CondRetXequeMate = 10,
	/* O Rei está em xeque mate */

	TAB_TipoEspacoTab = 11,
				/* Tipo de espaco de dados tabuleiro */

	TAB_TipoEspacoCasa = 12,
				/* Tipo de espaco de dados casa */

	TAB_TipoEspacoPeca = 13,
				/* Tipo de espaco de dados peca */

	TAB_CondRetErroEstrutura = 14,
				/* Erro estrutural */

	TAB_TipoEspacoCabeca = 15,
				/* Tipo de dado cabeca de tab */

	TAB_TipooDadoCasa = 16,
				/* Tipo de dado casa de tab */

	TAB_TipoDadoPeca = 17
				/* Tipo de dado peca de tab */

} TAB_tpCondRet ;



/**************************************************************************************
*
*	$FC Função: TAB  &Criar Tab
*
*	$ED Descrição da função
*		Cria um tabuleiro de xadrez.
*
*	$FV Valor retornado
*		Se executou corretamente retorna o ponteiro para o tabuleiro.
*		Este ponteiro será utilizado pelas funções que manipulam o tabuleiro.
*
*		Se ocorreu algum erro, por exemplo falta de memória ou dados errados, a função
*		retornará NULL.
*		Não será dada mais informação quanto ao problema ocorrido.
*
**************************************************************************************/

TAB_tppTab TAB_CriarTab ( void );



/**************************************************************************************
*
*	$FC Função: TAB  &Obter peca
*
*	$ED Descrição da função
*		Reorna a peca que está na casa especificada.
*
*  $EP Parâmetros
*		linha (int contendo o numero da linha da casa de interesse)  
*		coluna (char contendo o caractere da coluna da casa de interesse) 
*		pTab (ponteiro para o tabuleiro em questão)
*
*	$FV Valor retornado
*		TAB_tppPeca (ponteiro para uma peca, NULL caso a casa esteja vazia)
*
**************************************************************************************/

TAB_tppPeca TAB_ObterPeca ( int linha , char coluna, TAB_tppTab pTab );



/**************************************************************************************
*
*	$FC Função: TAB  &Retirar peca
*
*	$ED Descrição da função
*		Retira a peca da casa especificada.
*
*  $EP Parâmetros
*		linha (int contendo o numero da linha da casa de interesse)  
*		coluna (char contendo o caractere da coluna da casa de interesse) 
*		pTab (ponteiro para o tabuleiro em questão)
*
*	$FV Valor retornado
*		CondRetOK
*		CondRetNaoExiste
*		CondRetCasaInvalida
*		CondRetCondRetCasaVazia
*
**************************************************************************************/

TAB_tpCondRet TAB_RetirarPeca ( int linha , char coluna, TAB_tppTab pTab );



/**************************************************************************************
*
*	$FC Função: TAB  &Mover peca
*
*	$ED Descrição da função
*		Move a peca da casa origem para a casa destino.
*		Segue as regras de movimentação proprias de cada peça.
*		Em alguns casos essa movimentação implica na remoção de outra peca
*
*  $EP Parâmetros
*		linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
*		colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
*		linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
*		colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
*
*	$FV Valor retornado
*		CondRetOK
*		CondRetNaoExiste
*		CondRetCasaInvalida
*		CondRetCondRetCasaVazia
*
**************************************************************************************/

TAB_tpCondRet TAB_MoverPeca ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab );



/**************************************************************************************
*
*	$FC Função: TAB  &Inserir peca
*
*	$ED Descrição da função
*		Insere nova peca na casa especificada.
*
*  $EP Parâmetros
*		linha (int contendo o numero da linha da casa de interesse)  
*		coluna (char contendo o caractere da coluna da casa de interesse) 
*		pTab (ponteiro para o tabuleiro em questão)
*
*	$FV Valor retornado
*		CondRetOK
*		CondRetNaoExiste
*		CondRetCasaInvalida
*		CondRetCondRetCasaCheia
*
**************************************************************************************/

TAB_tpCondRet TAB_InserirPeca ( int linha , char coluna, char cor, char tipo, TAB_tppTab pTab );



/**************************************************************************************
*
*	$FC Função: TAB  &Obter Lista Ameacantes
*
*	$ED Descrição da função
*		Retorna uma lista de pecas que ameacam a casa especificada
*
*  $EP Parâmetros
*		linha (int contendo o numero da linha da casa de interesse)  
*		coluna (char contendo o caractere da coluna da casa de interesse) 
*		pTab (ponteiro para o tabuleiro em questão)
*
*	$FV Valor retornado
*		LIS_tppLista (ponteiro para a cabeça da lista de ameacantes)
*		
*		Em caso de algum problema é retornado NULL sem maiores esclarecimentos
*
**************************************************************************************/

LIS_tppLista TAB_ObterListaAmeacantes( int linha, char coluna, TAB_tppTab pTab );


/**************************************************************************************
*
*	$FC Função: TAB  &Obter Lista Ameacados
*
*	$ED Descrição da função
*		Retorna uma lista de casas que estão ameacadas pela peca localizada na casa 
*		especificada
*
*  $EP Parâmetros
*		linha (int contendo o numero da linha da casa de interesse)  
*		coluna (char contendo o caractere da coluna da casa de interesse) 
*		pTab (ponteiro para o tabuleiro em questão)
*
*	$FV Valor retornado
*		LIS_tppLista (ponteiro para a cabeça da lista de ameacados)
*		
*		Em caso de algum problema é retornado NULL sem maiores esclarecimentos
*
**************************************************************************************/

LIS_tppLista TAB_ObterListaAmeacados( int linha , char coluna, TAB_tppTab pTab );



/**************************************************************************************
*
*	$FC Função: TAB  &Destruir Tab
*
*	$ED Descrição da função
*		Destroi um tabuleiro de xadrez passado como parametro.
*
*  $EP Parâmetros
*		pTab (ponteiro para o tabuleiro em questão)
*
*	$FV Valor retornado
*		TAB_CondRetNaoExiste
*		TAB_CondRetOK
*
**************************************************************************************/

TAB_tpCondRet TAB_DestruirTab ( TAB_tppTab pTab );

/**************************************************************************************
*
*	$FC Função: TAB  &Verificar Xeque
*
*	$ED Descrição da função
*		Verifica se o rei está em xeque ou xeque mate, retorna TAB_CondRetOK
*		caso o rei nao esteja em nehuma dessas condicoes
*
*  $EP Parâmetros
*		pTab (ponteiro para o tabuleiro em questão)
*
*	$FV Valor retornado
*		TAB_CondRetXeque
*		TAB_CondRetXequeMate
*		TAB_CondRetOK
*
**************************************************************************************/

TAB_tpCondRet TAB_VerificaXeque ( TAB_tppTab pTab );


/***********************************************************************
*
*  $FC Função: TAB  &Verificar um tabuleiro
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica completamente um tabuleiro.
*     Também marca todos os espaços por ele ocupados.
*
***********************************************************************/

#ifdef _DEBUG

   TAB_tpCondRet TAB_VerificarTab( TAB_tppTab pTab) ;

#endif
