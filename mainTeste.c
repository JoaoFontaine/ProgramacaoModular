#include<stdio.h>
#include<stdlib.h>
#include "geracod.h"

int main (void){

	funcp pFun;
	int resposta;
	int i;
	unsigned char *tst;
	char* nFonte= "/home/joaofontaine/Dropbox/sb/trabalho2/arquivosTeste/tst01.txt";
	FILE *arqEntrada;
	
	arqEntrada = fopen( nFonte, "r");
	if( arqEntrada == NULL ){
		printf("Nao foi possivel abrir o arquivo\n");
		exit(0);
	}
	
	pFun = geracod ( arqEntrada );
	/*
	tst = (unsigned char*) pFun;
	for(i=0; i<35; i++){
		printf("%0x\n", tst[i]);
	}*/

	resposta = (*pFun)(10,20,5);
	
	printf("resposta = %d\n", resposta);
	
  	return 0;
}

