

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

         TAB_CondRetCasaCheia = 5
		       /* A casa ja contem peca */

   } TAB_tpCondRet ;

TAB_tppTab CriarTab ( void );

TAB_tppPeca ObterPeca ( int linha , char coluna, TAB_tppTab pTab );

TAB_tpCondRet RetirarPeca ( int linha , char coluna, TAB_tppPeca pPeca );

TAB_tpCondRet MoverPeca ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest );

TAB_tpCondRet InserirPeca ( int linha , char coluna, TAB_tppPeca pPeca );

LIS_tppLista ObterListaAmeacantes( int linha , char coluna, TAB_tppTab pTab );

LIS_tppLista ObterListaAmeacados( int linha , char coluna, TAB_tppTab pTab );

TAB_tpCondRet DestruirTab ( TAB_tppTab pTab );