/**************************************************************************************
*
*	$MCD M�dulo de defini��o: PAR  Controlador da partida
*
*	Arquivo gerado:              PAR.h
*	Letras identificadoras:      PAR
*
*	Projeto: INF 1301 Jogo de Xadrez
*	Autores: Guilherme Araujo e Jo�o Pedro Fontaine
*
*
*	$ED Descri��o do m�dulo
*		Implementa um modulo controlador da partida.
*       Onde s�o implementadas as funcionalidades que permitem a realizacao,
*       de uma partida de xadrez
**************************************************************************************/

typedef enum {

	PAR_CondRetOK = 0,
	/* Concluiu corretamente */

	PAR_CondRetNaoExiste = 1 ,
	/* O tabuleiro nao existe */

	PAR_CondRetCasaVazia = 2,
	/* A casa nao contem peca */

	PAR_CondRetMovInv = 3,
	/* Movimento de peca invalido */

	PAR_CondRetCaptPeca = 4,
	/* Capturou peca inimiga */

	PAR_CondRetCasaCheia = 5,
	/* A casa ja contem peca */

	PAR_CondRetCasaInvalida = 6,
	/* A casa nao pertence ao tabuleiro */

	PAR_CondRetPecaBloqueando = 7,
	/* A casa nao pertence ao tabuleiro */

	PAR_CondRetPecaInvalida = 8,
	/* A casa nao pertence ao tabuleiro */

	PAR_CondRetXeque = 9,
	/* O Rei est� em xeque */

	PAR_CondRetXequeMate = 10,
	/* O Rei est� em xeque mate */

	PAR_CondRetNomeInvalido = 11,
	/* O nome do jogador n�o � v�lido */

	PAR_CondRetCorInvalida = 12,
	/* A cor escolhida n�o � v�lida */

	PAR_CondRetNumInvalidoJogadores = 13,
	/* Numero de jogadores inferior ou superior ao correto para o jogo */

	PAR_CondRetDesistencia = 14
	/* Numero de jogadores inferior ou superior ao correto para o jogo */

} PAR_tpCondRet ;

/**************************************************************************************
*
*	$FC Fun��o: PAR  &Iniciar jogo
*
*	$ED Descri��o da fun��o
*		Inicia um jogo de xadrez
*
*	$FV Valor retornado
*		Se executou corretamente retorna o ponteiro para o tabuleiro.
*
*		Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados, a fun��o
*		retornar� NULL.
*		N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
**************************************************************************************/


PAR_tpCondRet PAR_IniciarPartida ( char modoDeInicializacao );



/**************************************************************************************
*
*	$FC Fun��o: PAR  &Imprimir tabuleiro
*
*	$ED Descri��o da fun��o
*		Imprime o tabuleiro na tela do usuario.
*
*  $EP Par�metros
*		pTab (ponteiro para o tabuleiro da partida)
*
*	$FV Valor retornado
*		CondRetOK
*       CondRetNaoExiste
*
**************************************************************************************/

PAR_tpCondRet  PAR_ImprimirTabuleiro ( TAB_tppTab pTab );



/**************************************************************************************
*
*	$FC Fun��o: PAR  &Realizar jogada
*
*	$ED Descri��o da fun��o
*		Realiza a movimentacao de pecas de acordo com as regras
*       do jogo de xadrez.
*
*  $EP Par�metros
*		linhaOrig (int contendo o numero da linha onde est� a pe�a a ser movida)  
*		colunaOrig (char contendo o caractere da coluna onde est� a pe�a a ser movida)  
*		linhaDest (int contendo o numero da linha para onde a pe�a deve ser movida)  
*		colunaDest (char contendo o caractere da coluna para onde a pe�a deve ser movida)
*		pTab (ponteiro para o tabuleiro em quest�o)
*
*	$FV Valor retornado
*		CondRetOK
*       CondRetNaoExiste
*       CondRetCasaInvalida
*		CondRetCondRetCasaVazia
*       CondRetCondRetCasaCheia
*		CondRetMovInv
*       CondRetPecaBloqueando
*       CondRetCaptPeca
*
**************************************************************************************/

PAR_tpCondRet RealizarJogada (int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab );



/**************************************************************************************
*
*	$FC Fun��o: PAR  &Cadastrar Jogador
*
*	$ED Descri��o da fun��o
*		Realiza o cadastro de jogadores na partida do jogo de xadrez.
*
*	$EP Par�metros
*		nome (char[] contendo o nome do jogador a ser cadastrado)  
*		cor (char contendo o caractere da cor que o jogador gostaria 'B' ou 'P')  
*		
*	$FV Valor retornado
*		CondRetOK
*       CondRetNomeInvalido
*		CondRetCorInvalida
*       CondRetNumInvalidoJogadores
*
**************************************************************************************/

PAR_tpCondRet PAR_CadastrarJogador( char nome[], char cor );
