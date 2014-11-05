/***************************************************************************
*  $MCI Módulo de implementação: PAR  Partida de xadrez
*
*  Arquivo gerado:              PAR.c
*  Letras identificadoras:      PAR
*
*  Projeto: INF 1301 Jogo de Xadrez
*  Autores: Guilherme Araujo e João Pedro Fontaine

***************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "TAB.h"
#include "LISTA.h"
#include "PARTIDA.h"


/*****  Código das funções exportadas pelo módulo  *****/


TAB_tppTab PAR_IniciarJogo ( void ){

	int i;

	TAB_tppTab pTab;
	pTab = TAB_CriarTab();

	if(pTab==NULL){
		printf("\nNao foi possivel criar tabuleiro");
		return NULL;
	}
	/*if*/

	TAB_InserirPeca ( 1 , 'A' , 'B' , 'T' , pTab) ; 
	TAB_InserirPeca ( 1 , 'B' , 'B' , 'C' , pTab) ; 
	TAB_InserirPeca ( 1 , 'C' , 'B' , 'B' , pTab) ; 
	TAB_InserirPeca ( 1 , 'D' , 'B' , 'D' , pTab) ; 
	TAB_InserirPeca ( 1 , 'E' , 'B' , 'R' , pTab) ; 
	TAB_InserirPeca ( 1 , 'F' , 'B' , 'B' , pTab) ; 
	TAB_InserirPeca ( 1 , 'G' , 'B' , 'C' , pTab) ; 
	TAB_InserirPeca ( 1 , 'H' , 'B' , 'T' , pTab) ; 
	TAB_InserirPeca ( 8 , 'A' , 'P' , 'T' , pTab) ; 
	TAB_InserirPeca ( 8 , 'B' , 'P' , 'C' , pTab) ; 
	TAB_InserirPeca ( 8 , 'C' , 'P' , 'B' , pTab) ; 
	TAB_InserirPeca ( 8 , 'D' , 'P' , 'D' , pTab) ; 
	TAB_InserirPeca ( 8 , 'E' , 'P' , 'R' , pTab) ; 
	TAB_InserirPeca ( 8 , 'F' , 'P' , 'B' , pTab) ; 
	TAB_InserirPeca ( 8 , 'G' , 'P' , 'C' , pTab) ; 
	TAB_InserirPeca ( 8 , 'H' , 'P' , 'T' , pTab) ; 

	for(i=0;i<8;i++){ /* Apenas para deixar o codigo mais enxuto ao inserir os peoes */

		TAB_InserirPeca ( 2 , ('A'+i) , 'B' , 'P' , pTab) ; 
	    TAB_InserirPeca ( 7 , ('A'+i) , 'P' , 'P' , pTab) ;
	}
	/* for */

	return pTab;
}



PAR_tpCondRet RealizarJogada (int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){

	PAR_tpCondRet CondRet;

	if(pTab==NULL) return PAR_CondRetNaoExiste;

	CondRet = (PAR_tpCondRet) TAB_MoverPeca( linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);

	return CondRet;
}



PAR_tpCondRet  PAR_ImprimirTabuleiro ( TAB_tppTab pTab ){

	int i;

	if(pTab==NULL) return PAR_CondRetNaoExiste;

	printf("\n			A		B		C		D		E		F		G		H");

	for(i=8;i>=1;i++){
		printf("\n%d			%c		%c		%c		%c		%c		%c		%c		%c", i,
	            TAB_ObterPeca( i, 'A', pTab)->nome, TAB_ObterPeca( i, 'B', pTab)->nome,
				TAB_ObterPeca( i, 'C', pTab)->nome, TAB_ObterPeca( i, 'D', pTab)->nome,
				TAB_ObterPeca( i, 'E', pTab)->nome, TAB_ObterPeca( i, 'F', pTab)->nome,
				TAB_ObterPeca( i, 'G', pTab)->nome, TAB_ObterPeca( i, 'H', pTab)->nome);
	}
	/* for*/

	return PAR_CondRetOK;
}

