#include<stdio.h>
#include<stdlib.h>
#include "geracod.h"

void ImprimeCodigo(funcp pFun);

int main (int argc, char *argv[]){

	funcp pFun;
	int resposta;
	int i;
	int parametros[5] = {0,0,0,0,0};
	char* nFonte= "/home/joaofontaine/Dropbox/sb/trabalho2/arquivosTeste/tst.txt";
	FILE *arqEntrada;
	
	arqEntrada = fopen( nFonte, "r");
	if( arqEntrada == NULL ){
		printf("Nao foi possivel abrir o arquivo\n");
		exit(0);
	}
	
	pFun = geracod ( arqEntrada );
	if(argc>1)
	{
		if(argv[1][0] == '1'){
			ImprimeCodigo(pFun);
		}
		for(i = 0; i < argc-2; i++){
			parametros[i] = atoi(argv[i+2]);
		}
	}
	
	resposta = (*pFun)(parametros[0],parametros[1],parametros[2],parametros[3],parametros[4]);
	
	printf("resposta = %d\n", resposta);
	
  	return 0;
}

void ImprimeCodigo(funcp pFun){
	int i;
	unsigned char *tst;
	
	tst = (unsigned char*) pFun;
	for(i=0; tst[i] != 0xFF || tst[i-1] != 0xC3; i++){
		printf("%0x\n", tst[i]);
	}
}
