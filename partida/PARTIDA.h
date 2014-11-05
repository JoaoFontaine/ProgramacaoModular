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


#include "TAB.h"
#include "LISTA.h"

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


TAB_tppTab PAR_IniciarJogo ( void );



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

