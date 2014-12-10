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
#include<ctype.h>
#include "LISTA.h"
#include "TAB.h"
#include "PARTIDA.h"

#define TAMANHO_MAX_NOME 40
#define NUM_JOGADORES 2

/* Tipo jogador, guarda as informações relevantes dos jogadores */
typedef struct PAR_tagJogador {

	char nome[TAMANHO_MAX_NOME]; 
	/* Nome do jogador */

	char  corPecas;
	/* Cor das pecas do jogador */

	int linhaRei;
	/* Linha do tabuleiro na qual está o rei do jogador */

	char colunaRei;
	/* Coluna do tabuleiro na qual está o rei do jogador */

}tpJogador ;

/* Variável que armazena os dados dos jogadores em um vetor */
static tpJogador jogadores[NUM_JOGADORES];
static int jogadoresCadastrados = 0;


void VerificaCor(char cor);
void VerificaNomePeca(char nome);
void ImprimirAmeacas( int linhaDest, char colunaDest, TAB_tppTab pTab );
void ImprimirCasasAmeacadas( int linhaDest, char colunaDest, TAB_tppTab pTab );
void ImprimirTodasAmeacas( TAB_tppTab pTab );

/*****  Código das funções exportadas pelo módulo  *****/

PAR_tpCondRet PAR_CadastrarJogador( char nome[], char cor ){

	if( ! isalpha( nome[0] ) ){
		return PAR_CondRetNomeInvalido;
	}

	if( cor != 'B' && cor != 'P'){
		return PAR_CondRetCorInvalida;
	}

	if(jogadoresCadastrados == 0){
		strcpy(jogadores[0].nome, nome);
		jogadores[0].corPecas = cor;
	}
	else{
		if(jogadoresCadastrados == 1){

			if( strcmp(jogadores[0].nome, nome) == 0){
				return PAR_CondRetNomeInvalido;
			}

			if( jogadores[0].corPecas == cor ){
				return PAR_CondRetCorInvalida;
			}

			strcpy(jogadores[1].nome, nome);
			jogadores[1].corPecas = cor;
		}
		else{
			return PAR_CondRetNumInvalidoJogadores;
		}
	}

	jogadoresCadastrados++;
	return PAR_CondRetOK;
}

TAB_tppTab PAR_PrepararTabuleiro ( char modoDeInicializacao ){

	int i, j;
	char peca, cor;
	char coluna;
	char opcao;
	int linha;

	TAB_tpCondRet condRet;
	TAB_tppTab pTab;
	TAB_tppPeca pPeca;
	TAB_tppPeca rei_0;
	TAB_tppPeca rei_1;
	pTab = TAB_CriarTab();

	if(pTab==NULL){
		printf("\nNao foi possivel criar tabuleiro");
		return NULL;
	}
	/*if*/

	if ( modoDeInicializacao == 'M' || modoDeInicializacao == 'm' ){

		do{
			printf("Torre -> T|Cavalo -> C|Bispo -> B|Rainha -> D|Rei -> R|Peao -> P\n");
			printf("Para não inserir mais nenhuma -> N\n");
			printf("Qual peca deseja inserir?\n-> ");
			scanf(" %c", &peca);
			printf("\n");
			VerificaNomePeca(peca);
			if(peca == 'N'){
				return pTab;
			}

			printf("Preta -> P|Branca -> B\n");
			printf("Para não inserir mais nenhuma -> N\n");
			printf("Qual a cor da peca que deseja inserir?\n-> ");
			scanf(" %c", &cor);
			printf("\n");
			VerificaCor(cor);
			if(cor == 'N'){
				return pTab;
			}

			printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |\n");
			printf("Para não inserir mais nenhuma -> Numero < 1 ou Numero > 8\n");
			printf("Em qual linha deseja inserir a peca?\n-> ");
			scanf(" %d", &linha);
			printf("\n");
			if( linha < 1 || linha > 8 ){
				return pTab;
			}

			printf("| A | B | C | D | E | F | G | H |\n");
			printf("Para não inserir mais nenhuma -> N\n");
			printf("Em qual coluna deseja inserir a peca?\n-> ");
			scanf(" %c", &coluna);
			printf("\n");
			if(coluna == 'N'){
				return pTab;
			}

			condRet = TAB_InserirPeca ( linha , coluna , cor , peca , pTab) ; 
			if( condRet != TAB_CondRetOK ){
				printf("Peca nao pode ser inserida!\n");
			}

			printf("Sim -> S|Nao -> N\n");
			printf("Deseja inserir mais uma peca?\n-> ");
			scanf(" %c", &opcao);
			printf("\n");

		}while(opcao == 'S');

	}
	else{

		TAB_InserirPeca ( 1 , 'A' , 'B' , 'T' , pTab) ;
		ImprimirCasasAmeacadas( 1 , 'A', pTab );
		TAB_InserirPeca ( 1 , 'B' , 'B' , 'C' , pTab) ; 
		ImprimirCasasAmeacadas( 1 , 'B', pTab );
		TAB_InserirPeca ( 1 , 'C' , 'B' , 'B' , pTab) ; 
		ImprimirCasasAmeacadas( 1 , 'C', pTab );
		TAB_InserirPeca ( 1 , 'D' , 'B' , 'D' , pTab) ; 
		ImprimirCasasAmeacadas( 1 , 'D', pTab );
		TAB_InserirPeca ( 1 , 'E' , 'B' , 'R' , pTab) ; 
		ImprimirCasasAmeacadas( 1 , 'E', pTab );
		TAB_InserirPeca ( 1 , 'F' , 'B' , 'B' , pTab) ; 
		ImprimirCasasAmeacadas( 1 , 'F', pTab );
		TAB_InserirPeca ( 1 , 'G' , 'B' , 'C' , pTab) ; 
		ImprimirCasasAmeacadas( 1 , 'G', pTab );
		TAB_InserirPeca ( 1 , 'H' , 'B' , 'T' , pTab) ;
		ImprimirCasasAmeacadas( 1 , 'H', pTab );

		for(i=0;i<8;i++){ /* Apenas para deixar o codigo mais enxuto ao inserir os peoes */

			TAB_InserirPeca ( 2 , ('A'+i) , 'B' , 'P' , pTab) ; 
			TAB_InserirPeca ( 7 , ('A'+i) , 'P' , 'P' , pTab) ;
		}

		ImprimirCasasAmeacadas( 1 , 'A', pTab );
		ImprimirCasasAmeacadas( 1 , 'B', pTab );
		ImprimirCasasAmeacadas( 1 , 'C', pTab );
		ImprimirCasasAmeacadas( 1 , 'D', pTab );
		ImprimirCasasAmeacadas( 1 , 'E', pTab );
		ImprimirCasasAmeacadas( 1 , 'F', pTab );
		ImprimirCasasAmeacadas( 1 , 'G', pTab );
		ImprimirCasasAmeacadas( 1 , 'H', pTab );

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
	}


	for(i=1;i<9;i++){
		for(j=0;j<8;j++){
			pPeca = TAB_ObterPeca ( i , (char) ('A'+j) , pTab) ;
			if(pPeca != NULL && pPeca->nome == 'R'){
				if(pPeca->cor == 'B'){
					if(jogadores[0].corPecas == 'B'){
						jogadores[0].linhaRei = i;
						jogadores[0].colunaRei = (char) ('A'+j);
					}
					else{
						jogadores[1].linhaRei = i;
						jogadores[1].colunaRei = (char) ('A'+j);
					}
				}
				else{
					if(jogadores[0].corPecas == 'P'){
						jogadores[0].linhaRei = i;
						jogadores[0].colunaRei = (char) ('A'+j);
					}
					else{
						jogadores[1].linhaRei = i;
						jogadores[1].colunaRei = (char) ('A'+j);
					}

				}
			}
		}
	}
	rei_0 = TAB_ObterPeca( jogadores[0].linhaRei, jogadores[0].colunaRei, pTab );
	rei_1 = TAB_ObterPeca( jogadores[1].linhaRei, jogadores[1].colunaRei, pTab );
	if( rei_0 == NULL || rei_0->nome != 'R' || rei_0->cor != jogadores[0].corPecas ){
		printf("**\tErro ao tentar localizar o Rei o jogador %s\n", jogadores[0].nome);
	}
	if( rei_1 == NULL || rei_1->nome != 'R' || rei_1->cor != jogadores[1].corPecas ){
		printf("**\tErro ao tentar localizar o Rei o jogador %s\n", jogadores[1].nome);
	}

	return pTab;
}


PAR_tpCondRet RealizarJogada (int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){

	PAR_tpCondRet CondRet;

	if(pTab==NULL) return PAR_CondRetNaoExiste;

	CondRet = (PAR_tpCondRet) TAB_MoverPeca( linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);

	return CondRet;
}

PAR_tpCondRet  PAR_ImprimirTabuleiro ( TAB_tppTab pTab ){

	int i, j;
	TAB_tppPeca pPeca;
	char nome, cor;

	if(pTab==NULL) return PAR_CondRetNaoExiste;

	printf("\n\t|   A\t|   B\t|   C\t|   D\t|   E\t|   F\t|   G\t|   H\t|\n");
	printf("   -----|-------|-------|-------|-------|-------|-------|-------|-------|\n");

	for(i=8;i>=1;i--){
		printf("\t|\t|\t|\t|\t|\t|\t|\t|\t|\n");
		printf("    %d\t|", i);

		for( j = 0; j < 8; j++ ){
			pPeca = TAB_ObterPeca( i, (char)('A' + j), pTab);
			if( pPeca == NULL ){
				nome = 'V';
				cor = 'V';
			}
			else{
				nome = pPeca->nome;
				cor = pPeca->cor;
			}

			printf("  %c%c   |",  nome, cor);
		}
		printf("\n\t|\t|\t|\t|\t|\t|\t|\t|\t|\n");
		printf("   -----|-------|-------|-------|-------|-------|-------|-------|-------|\n");

	}
	/* for*/

	return PAR_CondRetOK;
}

PAR_tpCondRet PAR_IniciarPartida ( char modoDeInicializacao ){

	PAR_tpCondRet condRetPar;
	char cor ;
	char nome[TAMANHO_MAX_NOME];
	int linhaOrig;
	char colunaOrig;
	int linhaDest;
	char colunaDest;
	int turno;
	int jogadorDaVez;
	TAB_tppPeca pPeca;
	TAB_tppTab pTab;
	char novoTurno = 'S';
	char buffer[5];

	while(jogadoresCadastrados < 2){
		printf("\n Digite o nome do Jogador.\n -> ");
		scanf(" %s", &nome);
		printf("\nPreta -> P|Branca -> B\n");
		printf("Digite a cor das pecas do Jogador.\n -> ");
		scanf(" %c", &cor);
		printf("\n");
		condRetPar = PAR_CadastrarJogador( nome, cor );
		if( condRetPar == PAR_CondRetNomeInvalido ){
			printf("Por favor digite um nome de Jogador valido. O nome deve comecar com um caractere alfabetico\n");
		}
		if( condRetPar == PAR_CondRetCorInvalida ){
			printf("Por favor digite uma cor de peca valida.\n");
		}
	}

	if( jogadores[0].corPecas == 'B' ){
		turno = 0;
	}
	else{
		turno = 1;
	}

	pTab = PAR_PrepararTabuleiro ( modoDeInicializacao );
	jogadorDaVez = turno % NUM_JOGADORES;

	do{
		char FimDeJogo[5];
		PAR_ImprimirTabuleiro(pTab);
		printf("\n\n   %s, esse e o seu turno.\n", jogadores[jogadorDaVez].nome);
		printf("Para encerrar o jogo e aceitar a derrota a qualquer momento, durante seu turno, digite -> FIM\n");

		if( condRetPar == PAR_CondRetXeque ){
			printf("\n****** Atencao ******\n");
			printf("Jogador %s, voce esta em Xeque!\n", jogadores[jogadorDaVez].nome);
			printf("Neste turno você deve obrigatoriamente neutralizar a ameaca sobre seu rei!\n\n");
		}

		printf("Digite a linha (inteiro) da casa da peca a ser movimentada.\n ->");
		scanf(" %s", buffer);
		if( strcmp(buffer, "FIM") == 0 ){
			condRetPar = PAR_CondRetDesistencia;
			break;
		}
		linhaOrig = (int) buffer[0] - '0';

		printf("\n Digite e coluna (caracter maiusculo) da casa da peca a ser movimentada.\n ->");
		scanf(" %s", buffer);
		if( strcmp(buffer, "FIM") == 0 ){
			condRetPar = PAR_CondRetDesistencia;
			break;
		}
		colunaOrig = buffer[0];

		printf("\n Digite a linha (inteiro) da casa destino.\n ->");
		scanf(" %s", buffer);
		if( strcmp(buffer, "FIM") == 0 ){
			condRetPar = PAR_CondRetDesistencia;
			break;
		}
		linhaDest = (int) buffer[0] - '0';

		printf("\n Digite e coluna (caracter maiusculo) da casa destino.\n ->");
		scanf(" %s", buffer);
		if( strcmp(buffer, "FIM") == 0 ){
			condRetPar = PAR_CondRetDesistencia;
			break;
		}
		colunaDest = buffer[0];

		printf("\n");

		pPeca = (TAB_tppPeca) TAB_ObterPeca(linhaOrig, colunaOrig, pTab);

		if( pPeca == NULL || pPeca->cor != jogadores[jogadorDaVez].corPecas ){
			printf("Peca nao pertencente ao jogador, por favor retentar.\n");
			continue;
		}

		condRetPar = RealizarJogada(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);

		if( condRetPar != PAR_CondRetOK && condRetPar != PAR_CondRetCaptPeca){
			printf("Movimento inválido, tente novamente.\n");
			continue;
		}

		ImprimirAmeacas( linhaDest, colunaDest, pTab );

		turno++;
		jogadorDaVez = turno % NUM_JOGADORES;

		ImprimirAmeacas( jogadores[jogadorDaVez].linhaRei, jogadores[jogadorDaVez].colunaRei, pTab );
		condRetPar = (PAR_tpCondRet) TAB_VerificaXeque( jogadores[jogadorDaVez].linhaRei, jogadores[jogadorDaVez].colunaRei, pTab );

		if( condRetPar == PAR_CondRetXequeMate ){
			jogadorDaVez = (turno+1) % NUM_JOGADORES;
			printf("\n****** Atencao ******\n");
			printf("Xeque Mate!\nParabens %s, voce ganhou!!\n\n\n", jogadores[(jogadorDaVez)].nome);
			printf("Pressione qualquer tecla para encerrar.");
			scanf("%c", &novoTurno);
			break;
		}

	}while( novoTurno != 'N' );

	ImprimirTodasAmeacas(pTab);

	return condRetPar;
}

void VerificaCor(char cor){

	if(cor!='B' && cor!='P' && cor!='N'){
		printf("Cor invalida, digite B para branca ou P para preta\n)");
		printf("Para não inserir mais nenhuma -> N\n-> ");
		scanf(" %c", &cor);
		printf("\n");
		VerificaCor(cor);
	}
	/*if*/
}

void VerificaNomePeca(char nome){
	if(nome!='T' && nome!='C' && nome!='B' && nome!='D' && nome!='R' && nome!='P' && nome!='N'){
		printf("Peca invalida, as possibilidades sao:\n)");
		printf("Torre -> T|Cavalo -> C|Bispo -> B|Rainha -> D|Rei -> R|Peao -> P\n");
		printf("Para não inserir mais nenhuma -> N\n-> ");
		scanf(" %c", &nome);
		printf("\n");
		VerificaNomePeca(nome);
	}
	/*if*/
}

void ImprimirAmeacas( int linhaDest, char colunaDest, TAB_tppTab pTab ){

	TAB_tppCasa pCasa;
	LIS_tppLista ameacadas = TAB_ObterListaAmeacados( linhaDest, colunaDest, pTab );
	LIS_tppLista ameacantes = TAB_ObterListaAmeacantes( linhaDest, colunaDest, pTab );
	TAB_tppPeca pPeca = TAB_ObterPeca( linhaDest, colunaDest, pTab );

	LIS_IrInicioLista (ameacadas);
	printf("Lista de Pecas ameacadas:\n");
	printf("Peca\tLinha\tColuna\n");
	do{
		pCasa = (TAB_tppCasa)LIS_ObterNo( ameacadas );
		if(pCasa != NULL && pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
			printf("%c\t%d\t%c\n", pCasa->Peca->nome, pCasa->linha, pCasa->coluna);
		}
	} while( LIS_IrProx(ameacadas) == LIS_CondRetOK );

	LIS_IrInicioLista (ameacantes);
	printf("Lista de Pecas ameacantes:\n");
	printf("Peca\tLinha\tColuna\n");
	do{
		pCasa = (TAB_tppCasa)LIS_ObterNo( ameacantes );
		if(pCasa != NULL && pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor ){
			printf("%c\t%d\t%c\n", pCasa->Peca->nome, pCasa->linha, pCasa->coluna);
		}
	} while( LIS_IrProx(ameacantes) == LIS_CondRetOK );

	printf("\n");

}

void ImprimirCasasAmeacadas( int linhaDest, char colunaDest, TAB_tppTab pTab ){

	TAB_tppCasa pCasa;
	LIS_tppLista ameacadas = TAB_ObterListaAmeacados( linhaDest, colunaDest, pTab );
	TAB_tppPeca pPeca = TAB_ObterPeca( linhaDest, colunaDest, pTab );

	LIS_IrInicioLista (ameacadas);
	printf("Lista de Casas ameacadas:\n");
	printf("Peca\tLinha\tColuna\n");
	do{
		pCasa = (TAB_tppCasa)LIS_ObterNo( ameacadas );
		if(pCasa != NULL){
			printf("%c\t%d\t%c\n", pCasa->Peca->nome, pCasa->linha, pCasa->coluna);
		}
	} while( LIS_IrProx(ameacadas) == LIS_CondRetOK );

	printf("\n");

}

void ImprimirTodasAmeacas( TAB_tppTab pTab ){

	int linha, coluna;
	TAB_tppCasa pCasa;
	LIS_tppLista ameacadas;
	LIS_tppLista ameacantes;
	TAB_tppPeca pPeca;

	for( linha = 1; linha < 9; linha++){
		for( coluna = 0; coluna < 8; coluna++ ){

			ameacadas = TAB_ObterListaAmeacados( linha, (char) ( coluna + 'A' ), pTab );
			ameacantes = TAB_ObterListaAmeacantes( linha, (char) ( coluna + 'A' ), pTab );
			pPeca = TAB_ObterPeca( linha, (char) ( coluna + 'A' ), pTab );

			if( pPeca != NULL ){
				if( ameacadas != NULL){
					LIS_IrInicioLista (ameacadas);
					printf("Lista de Pecas ameacadas:\n");
					printf("Peca\tLinha\tColuna\n");
					do{
						pCasa = (TAB_tppCasa)LIS_ObterNo( ameacadas );
						if(pCasa != NULL && pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
							printf("%c\t%d\t%c\n", pCasa->Peca->nome, pCasa->linha, pCasa->coluna);
						}
					} while( LIS_IrProx(ameacadas) == LIS_CondRetOK );
				}

				if( ameacantes != NULL){
					LIS_IrInicioLista (ameacantes);
					printf("Lista de Pecas ameacantes:\n");
					printf("Peca\tLinha\tColuna\n");
					do{
						pCasa = (TAB_tppCasa)LIS_ObterNo( ameacantes );
						if(pCasa != NULL && pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor ){
							printf("%c\t%d\t%c\n", pCasa->Peca->nome, pCasa->linha, pCasa->coluna);
						}
					} while( LIS_IrProx(ameacantes) == LIS_CondRetOK );
				}
				printf("\n");
			}
		}
	}
}