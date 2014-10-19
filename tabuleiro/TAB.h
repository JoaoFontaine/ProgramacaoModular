

typedef struct TAB_tagTab * TAB_tppTab ;

typedef struct TAB_tagPeca * TAB_tppPeca;

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

TAB_tppTab TAB_CriarTab ( void );

TAB_tppPeca TAB_ObterPeca ( int linha , char coluna, TAB_tppTab pTab );

TAB_tpCondRet TAB_RetirarPeca ( int linha , char coluna, TAB_tppTab pTab );

TAB_tpCondRet TAB_MoverPeca ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab );

TAB_tpCondRet TAB_InserirPeca ( int linha , char coluna, char cor, char tipo, TAB_tppTab pTab );

LIS_tppLista TAB_ObterListaAmeacantes( int linha , char coluna, TAB_tppTab pTab );

LIS_tppLista TAB_ObterListaAmeacados( int linha , char coluna, TAB_tppTab pTab );

TAB_tpCondRet TAB_DestruirTab ( TAB_tppTab pTab );