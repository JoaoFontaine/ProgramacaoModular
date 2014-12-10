
/**************************************************************************************
*
*	$MCD M�dulo de defini��o: TAB  Tabuleiro de xadrez
*
*	Arquivo gerado:              TAB.h
*	Letras identificadoras:      TAB
*
*	Projeto: INF 1301 Jogo de Xadrez
*	Autores: Guilherme Araujo e Jo�o Pedro Fontaine
*
*
*	$ED Descri��o do m�dulo
*		Implementa um tabuleiro de xadrez com suas funcionalidades.
*		Podem existir n tabuleiros em opera��o simultaneamente.
*		
*		O tabuleiro tem 64 casas dispostas em 8 colunas e 8 linhas. Cada casa possui 
*			um ponteiro para uma pe�a, que assume o valor NULL quando a mesma est�
*			vazia, um ponteiro para a cabe�a de uma lista de pe�as que amea�am esta 
*			casa e outro ponteiro para a cabe�a de uma lista de casas que s�o
*			amea�adas pela pe�a que est� nesta casa.
*
**************************************************************************************/
typedef struct LIS_tagLista *TAB_tppLista;
/* Tipo exportado que referencia a estrutura tabuleiro */
typedef struct TAB_tagPeca {

	char nome;
	/* Nome da peca */
	char cor;
	/* Cor da peca */

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

	TAB_CondRetPecaInvalida = 8
	/* A casa nao pertence ao tabuleiro */

} TAB_tpCondRet ;



/**************************************************************************************
*
*	$FC Fun��o: TAB  &Criar Tab
*
*	$ED Descri��o da fun��o
*		Cria um tabuleiro de xadrez.
*
*	$FV Valor retornado
*		Se executou corretamente retorna o ponteiro para o tabuleiro.
*		Este ponteiro ser� utilizado pelas fun��es que manipulam o tabuleiro.
*
*		Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados, a fun��o
*		retornar� NULL.
*		N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
**************************************************************************************/

TAB_tppTab TAB_CriarTab ( void );



/**************************************************************************************
*
*	$FC Fun��o: TAB  &Obter peca
*
*	$ED Descri��o da fun��o
*		Reorna a peca que est� na casa especificada.
*
*  $EP Par�metros
*		linha (int contendo o numero da linha da casa de interesse)  
*		coluna (char contendo o caractere da coluna da casa de interesse) 
*		pTab (ponteiro para o tabuleiro em quest�o)
*
*	$FV Valor retornado
*		TAB_tppPeca (ponteiro para uma peca, NULL caso a casa esteja vazia)
*
**************************************************************************************/

TAB_tppPeca TAB_ObterPeca ( int linha , char coluna, TAB_tppTab pTab );



/**************************************************************************************
*
*	$FC Fun��o: TAB  &Retirar peca
*
*	$ED Descri��o da fun��o
*		Retira a peca da casa especificada.
*
*  $EP Par�metros
*		linha (int contendo o numero da linha da casa de interesse)  
*		coluna (char contendo o caractere da coluna da casa de interesse) 
*		pTab (ponteiro para o tabuleiro em quest�o)
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
*	$FC Fun��o: TAB  &Mover peca
*
*	$ED Descri��o da fun��o
*		Move a peca da casa origem para a casa destino.
*		Segue as regras de movimenta��o proprias de cada pe�a.
*		Em alguns casos essa movimenta��o implica na remo��o de outra peca
*
*  $EP Par�metros
*		linhaOrig (int contendo o numero da linha onde est� a pe�a a ser movida)  
*		colunaOrig (char contendo o caractere da coluna onde est� a pe�a a ser movida)  
*		linhaDest (int contendo o numero da linha para onde a pe�a deve ser movida)  
*		colunaDest (char contendo o caractere da coluna para onde a pe�a deve ser movida)
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
*	$FC Fun��o: TAB  &Inserir peca
*
*	$ED Descri��o da fun��o
*		Insere nova peca na casa especificada.
*
*  $EP Par�metros
*		linha (int contendo o numero da linha da casa de interesse)  
*		coluna (char contendo o caractere da coluna da casa de interesse) 
*		pTab (ponteiro para o tabuleiro em quest�o)
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
*	$FC Fun��o: TAB  &Obter Lista Ameacantes
*
*	$ED Descri��o da fun��o
*		Retorna uma lista de pecas que ameacam a casa especificada
*
*  $EP Par�metros
*		linha (int contendo o numero da linha da casa de interesse)  
*		coluna (char contendo o caractere da coluna da casa de interesse) 
*		pTab (ponteiro para o tabuleiro em quest�o)
*
*	$FV Valor retornado
*		LIS_tppLista (ponteiro para a cabe�a da lista de ameacantes)
*		
*		Em caso de algum problema � retornado NULL sem maiores esclarecimentos
*
**************************************************************************************/

TAB_tppLista TAB_ObterListaAmeacantes( int linha , char coluna, TAB_tppTab pTab );



/**************************************************************************************
*
*	$FC Fun��o: TAB  &Obter Lista Ameacados
*
*	$ED Descri��o da fun��o
*		Retorna uma lista de casas que est�o ameacadas pela peca localizada na casa 
*		especificada
*
*  $EP Par�metros
*		linha (int contendo o numero da linha da casa de interesse)  
*		coluna (char contendo o caractere da coluna da casa de interesse) 
*		pTab (ponteiro para o tabuleiro em quest�o)
*
*	$FV Valor retornado
*		LIS_tppLista (ponteiro para a cabe�a da lista de ameacados)
*		
*		Em caso de algum problema � retornado NULL sem maiores esclarecimentos
*
**************************************************************************************/

TAB_tppLista TAB_ObterListaAmeacados( int linha , char coluna, TAB_tppTab pTab );



/**************************************************************************************
*
*	$FC Fun��o: TAB  &Destruir Tab
*
*	$ED Descri��o da fun��o
*		Destroi um tabuleiro de xadrez passado como parametro.
*
*  $EP Par�metros
*		pTab (ponteiro para o tabuleiro em quest�o)
*
*	$FV Valor retornado
*		TAB_CondRetNaoExiste
*		TAB_CondRetOK
*
**************************************************************************************/

TAB_tpCondRet TAB_DestruirTab ( TAB_tppTab pTab );