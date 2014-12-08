#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "LISTA.h"
#include "TAB.h"
#include "PARTIDA.h"

#define LINHAS 8
#define COLUNAS 8


void VerificaCor(char cor1){
	if(cor1!='B' || cor1!='P'){
		printf("\nCor invalida, digite B para branca ou P para preta)");
		scanf("%c",cor1);
		VerificaCor(cor1);
	}
	/*if*/
}


void ReceberDigitacao (char cor,  TAB_tppTab pTab){

	int linhaOrig;
	char colunaOrig;
	int linhaDest;
	char colunaDest;


	LIS_tppLista ListaAmeacados;
	LIS_tppLista ListaAmeacantes;

	TAB_tpCondRet CondRet;
	TAB_tppPeca pPeca;

	printf("\n Digite a linha (inteiro) da casa da peca a ser movimentada");
	scanf("%d",&linhaOrig);
	printf("\n Digite e coluna (caracter maiusculo) da casa da peca a ser movimentada");
	scanf("%c",&colunaOrig);
	printf("\n Digite a linha (inteiro) da casa destino");
	scanf("%d",&linhaOrig);
	printf("\n Digite e coluna (caracter maiusculo) da casa destino");
	scanf("%c",&colunaOrig);

	pPeca = (TAB_tppPeca) TAB_ObterPeca(linhaOrig, colunaOrig, pTab);

	if(pPeca->cor!=cor){
		printf("\n Peca nao pertencente ao jogador, por favor retentar");
		ReceberDigitacao(cor, pTab);
		return;
	}
	/*if*/

	CondRet = (TAB_tpCondRet) TAB_MoverPeca(linhaOrig, colunaOrig, linhaDest , colunaDest, pTab);

	if(CondRet!=TAB_CondRetOK){
		printf("\n Movimento invalido, por favor retentar");
		ReceberDigitacao(cor, pTab);
		return;
	}
	/*if*/

	ListaAmeacados = TAB_ObterListaAmeacados(linhaDest, colunaDest, pTab);
	ListaAmeacantes = TAB_ObterListaAmeacantes(linhaDest, colunaDest, pTab);
	LIS_IrInicioLista(ListaAmeacados);
	LIS_IrInicioLista(ListaAmeacantes);

	/*
	while(LIS_IrProx(ListaAmeacados)!=LIS_CondRetFimLista){
		pPeca = LIS_ObterNo(ListaAmeacados)
		printf("\n A peca movimentada ameaca essa casa: ");

    */
	return;
}



int FimDeJogo (TAB_tppTab pTab) {
	
	if (TAB_VerificaXeque(pTab)==TAB_CondRetXequeMate) return 1;

	return 0;
}
	


int main(void){

	char nomeJogador1[30];
	char nomeJogador2[30];
	char cor1;
	char cor2;

	TAB_tppPeca pPeca;
	TAB_tppTab pTab;
	pTab=PAR_IniciarJogo();

	printf("\n Digite o nome do Jogador 1 (max 30 caracteres)");
	scanf("%s",nomeJogador1);
	printf("\n Escolha sua cor de peca ('B'ou'P')");
	scanf("%c",cor1);

	VerificaCor(cor1);

	printf("\n Digite o nome do Jogador 2 (max 30 caracteres) ");
	scanf("%s",nomeJogador2);

	if(cor1='B'){
		printf("\n Jogador 1 comecara a partida com as pecas brancas ");
		cor2='P';
	}
	else{
		cor2='B';
		printf("\n Jogador 2 comecara a partida com as pecas brancas ");
	}
	/*if*/
	
	while(!FimDeJogo(pTab)){
		PAR_ImprimirTabuleiro(pTab);

		if(cor1=='B'){
			ReceberDigitacao(cor1, pTab);
			ReceberDigitacao(cor2, pTab);
		}
		else{
			ReceberDigitacao(cor2, pTab);
			ReceberDigitacao(cor1, pTab);
		}
		/*if*/
	}

	return 0;
}