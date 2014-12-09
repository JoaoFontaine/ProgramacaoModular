#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "LISTA.h"
#include "TAB.h"
#include "PARTIDA.h"

#define LINHAS 8
#define COLUNAS 8
#define TAMANHO_MAX_NOME 40

int main(void){

	char nomeJogador1[TAMANHO_MAX_NOME];
	char nomeJogador2[TAMANHO_MAX_NOME];
	char cor1;
	char cor2;

	PAR_tpCondRet condRet;

	printf("\tOla! Cadastre dois jogadores para iniciar uma partida de xadrez.\n");

	do{

		printf("\nDigite o nome do Jogador 1 (max 40 caracteres)\n");
		scanf(" %[^\n]", nomeJogador1);
		printf("\nEscolha sua cor de peca ('B'ou'P')");
		scanf(" %c", &cor1);

	}while( PAR_CadastrarJogador( nomeJogador1, cor1 ) != PAR_CondRetOK );

	do{
	printf("\nDigite o nome do Jogador 2 (max 40 caracteres)\n");
	scanf(" %[^\n]", nomeJogador2);

	if( cor1 == 'B' ){
		cor2 = 'P';
	}
	else{
		cor2 = 'B';
	}

	condRet = PAR_CadastrarJogador( nomeJogador2, cor2 );
	if( condRet != PAR_CondRetOK ){
		printf("Dados invalidos, tente novamente.\n");
	}
	}while( condRet != PAR_CondRetOK );
	/*if*/

	printf("O jogador com as pecas brancas comecara a partida.\n");

	condRet = PAR_IniciarPartida( 'A' );

	return 0;
}