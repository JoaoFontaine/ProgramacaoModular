/**************************************************************************************
*
*	$MCD Módulo de definição: PAR  Controlador da partida
*
*	Arquivo gerado:              PAR.h
*	Letras identificadoras:      PAR
*
*	Projeto: INF 1301 Jogo de Xadrez
*	Autores: Guilherme Araujo e João Pedro Fontaine
*
*
*	$ED Descrição do módulo
*		Implementa um modulo controlador da partida.
*       Onde são implementadas as funcionalidades que permitem a realizacao,
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
*	$FC Função: PAR  &Iniciar jogo
*
*	$ED Descrição da função
*		Inicia um jogo de xadrez
*
*	$FV Valor retornado
*		Se executou corretamente retorna o ponteiro para o tabuleiro.
*
*		Se ocorreu algum erro, por exemplo falta de memória ou dados errados, a função
*		retornará NULL.
*		Não será dada mais informação quanto ao problema ocorrido.
*
**************************************************************************************/


TAB_tppTab PAR_IniciarJogo ( void );



/**************************************************************************************
*
*	$FC Função: PAR  &Imprimir tabuleiro
*
*	$ED Descrição da função
*		Imprime o tabuleiro na tela do usuario.
*
*  $EP Parâmetros
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
*	$FC Função: PAR  &Realizar jogada
*
*	$ED Descrição da função
*		Realiza a movimentacao de pecas de acordo com as regras
*       do jogo de xadrez.
*
*  $EP Parâmetros
*		linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
*		colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
*		linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
*		colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
*		pTab (ponteiro para o tabuleiro em questão)
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

