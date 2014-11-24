/* Guilherme Araujo 1311835 3WB */
/* Joao Pedro Fontaine de Carvalho 0920931 3WA */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "geracod.h"

#define NUM_MAX 1000

static unsigned char comeco[]={0x55,0x89,0xe5,0x83,0xec,0x14}; /* salva o ebx e aloca espaco para 5 variaveis locais */

static unsigned char final[]={0x83,0xc4,0x14,0x89,0xec,0x5d,0xc3}; /* libera o ebx e o espaco das 5 variaveis locais */

static unsigned char marcadorDesvio[]={0x39,0xc8,0x74,0x00};

static void error (const char *msg, int line) {
	fprintf(stderr, "erro %s na linha %d\n", msg, line);
	exit(EXIT_FAILURE);
}

/***** Protótipos das funções encapuladas no módulo *****/

void checkVar(char var, int idx, int line);

int uniVet (unsigned char vet1[], unsigned char vet2[], int posicao, int tamVet2);

void calculaDesvio(unsigned char codigo[], int desvionum[], int desviolinha[], int desvioposicao[], int enderecosnum[]);

int Atribuicao (unsigned char *codigo, int posicao, char var0, int idx0, char var1, int idx1, char op, char var2, int idx2);

int DesvioCondicional(unsigned char *codigo, int posicao, char var0, int idx0, char var1, int idx1);


/* Funções Encapsuladas no módulo */


funcp geracod (FILE *myfp){

	unsigned char *codigoRet;
	unsigned char *codigo = (unsigned char*)malloc(NUM_MAX*(sizeof(unsigned char)));
	int posicao = 0;
	int line = 1;
	int c;
	int indice;
	int i;
	int desvionum[50];			/*armazena os numeros para onde serão desviados */
	int desviolinha[50];		/*armazena a linha em que há o comando de desvio */
	int desvioposicao[50];		/*armazena a posicao no veto de codigo onde o desvio sera colocado */
	int enderecosnum[50];		/*armazena os enderecos dos comandos*/
	int idx0, idx1, idx2, num;
	char var0, var1, var2, op;
	unsigned char aux[] = {0x8b, 0x45};
	posicao = uniVet(codigo, comeco, posicao, 6);
	
	for(i=0;i<50;i++){
		desviolinha[i]=0;
	}
	i=0;
	
	while ((c = fgetc(myfp)) != EOF) {

		enderecosnum[line-1] = posicao;  		/*armazena os enderecos dos comandos*/

		switch (c) {
		case 'r':   /* retorno */
			
			if (fscanf(myfp, "et %c%d", &var0, &idx0) != 2) 
				error("comando invalido", line);
			if (var0 != '$') checkVar(var0, idx0, line);

			switch (var0) {
			case '$': 
				codigo[posicao++] = 0xb8;
				codigo[posicao++] = (unsigned char) ( idx0 );
				codigo[posicao++] = (unsigned char) ( idx0 >> 8 );
				codigo[posicao++] = (unsigned char) ( idx0 >> 16 );
				codigo[posicao++] = (unsigned char) ( idx0 >> 24 );
				break;

			case 'v': case 'p':
				indice = ( var0 == 'p' ) ? (idx0+2)*4 : -(idx0+1)*4;
				posicao = uniVet(codigo, aux, posicao, 2);
				codigo[posicao++] = (unsigned char) indice;
				break;

			}
			posicao = uniVet(codigo,final,posicao,7);
			break;


		case 'i': /* ifeq */
			if (fscanf(myfp, "feq %c%d %c%d %d", &var0, &idx0, &var1, &idx1, 
				&num) != 5)
				error("comando invalido i",line);
			if (var0 != '$') checkVar(var0, idx0, line);
			if (var1 != '$') checkVar(var1, idx1, line);

			desvionum[i]=num;      /*armazena os numeros dos desvios */
			desviolinha[i]=line;   /*armazena a linha em que há o comando de desvio */
			posicao = DesvioCondicional(codigo, posicao, var0, idx0, var1, idx1);
			posicao = uniVet(codigo,marcadorDesvio,posicao,4);
			desvioposicao[i++] = posicao-1;
			break;

		case 'v': case 'p':  /* atribuicao */
			var0 = c;
			if (fscanf(myfp, "%d := %c%d %c %c%d",
				&idx0, &var1, &idx1, &op, &var2, &idx2) != 6)
				error("comando invalido", line);

			checkVar(var0, idx0, line);
			if (var1 != '$') {checkVar(var1, idx1, line);}
			if (var2 != '$') {checkVar(var2, idx2, line);}
			if (op != '+' && op != '-' && op != '*') {error("operacao invalida na atribuicao", line);}

			posicao = Atribuicao(codigo, posicao, var0, idx0, var1, idx1, op, var2, idx2);
			break;

		default: error("comando desconhecido", line);
		}
		line ++;
		fscanf(myfp, " ");
	}	
	posicao = uniVet(codigo,final,posicao,7);
	codigo[posicao++] = 0xFF;
	calculaDesvio(codigo,desvionum,desviolinha,desvioposicao,enderecosnum);
	codigoRet = (unsigned char*)malloc(posicao*(sizeof(unsigned char)));
	uniVet(codigoRet,codigo,0,posicao);
	free(codigo);
	return (funcp)codigoRet;
}

void checkVar(char var, int idx, int line) {
	switch (var) {
	case 'v':
		if ((idx < 0) || (idx > 5))
			error("operando invalido", line);
		break;
	case 'p':
		if ((idx < 0) || (idx > 5))
			error("operando invalido", line);
		break;
	default:
		error("operando invalido", line);
	}
}

int uniVet (unsigned char vet1[], unsigned char vet2[], int posicao, int tamVet2){
	int i;
	for(i=0; i<tamVet2; i++, posicao++){
		vet1[posicao]=vet2[i];
	}
	return posicao;
}

void calculaDesvio(unsigned char codigo[], int desvionum[], int desviolinha[], int desvioposicao[], int enderecosnum[]){
	int linhaInicial;
	int linhaDestino;
	int diferencaDesvio;
	int posicao;
	int i;
	for(i=0;i<50;i++){
		if(desviolinha[i]!= 0){
			linhaDestino = desvionum[i]-1;
			linhaInicial = desviolinha[i];
			diferencaDesvio = enderecosnum[linhaDestino]-enderecosnum[linhaInicial];
			posicao = desvioposicao[i];
			/*
			printf("\n*****************\n%d\n",enderecosnum[linhaDestino]);
			printf("%d\n",enderecosnum[linhaInicial]);
			printf("%d\n*****************\n",diferencaDesvio);
			*/
			codigo[posicao] = (unsigned char) diferencaDesvio;
		}
	}
	/* Essa funcao vai procurar o comando de "je" no vetor de codigo e substituir o '0x00' pela diferenca entre os
	   enderecos   */

	return;
}


int Atribuicao (unsigned char *codigo, int posicao, char var0, int idx0, char var1, int idx1, char op, char var2, int idx2){
	int i = 0;
	int indice;
	unsigned char codAtribuicao[16];

	if ( var1 == '$' ){
		codAtribuicao[i++] = 0xB8;// %eax
		codAtribuicao[i++] = (char) ( idx1 );
		codAtribuicao[i++] = (char) ( idx1 >> 8 );
		codAtribuicao[i++] = (char) ( idx1 >> 16 );
		codAtribuicao[i++] = (char) ( idx1 >> 24 );
	}
	else{
		indice = ( var1 == 'p' ) ? (idx1+2)*4 : -(idx1+1)*4;
		codAtribuicao[i++] = 0x8B;
		codAtribuicao[i++] = 0x45;// %eax
		codAtribuicao[i++] = (char) indice;
	}

	if ( var2 == '$' ){
		codAtribuicao[i++] = 0xB9;// %ecx
		codAtribuicao[i++] = (char) ( idx2 );
		codAtribuicao[i++] = (char) ( idx2 >> 8 );
		codAtribuicao[i++] = (char) ( idx2 >> 16 );
		codAtribuicao[i++] = (char) ( idx2 >> 24 );
	}
	else{
		indice = ( var2 == 'p' ) ? (idx2+2)*4 : -(idx2+1)*4;
		codAtribuicao[i++] = 0x8B;
		codAtribuicao[i++] = 0x4D;// %ecx
		codAtribuicao[i++] = (char) indice;
	}

	switch (op)
	{
	case '+':
		codAtribuicao[i++] = 0x01;
		codAtribuicao[i++] = 0xC8;
		break;
	case '-':
		codAtribuicao[i++] = 0x29;
		codAtribuicao[i++] = 0xC8;
		break;
	case '*':
		codAtribuicao[i++] = 0x0F;
		codAtribuicao[i++] = 0xAF;
		codAtribuicao[i++] = 0xC1;
		break;
	default:
		error("operacao invalida na atribuicao", -1);
		break;
	}

	indice = ( var0 == 'p' ) ? (idx0+2)*4 : -(idx0+1)*4;
	codAtribuicao[i++] = 0x89;
	codAtribuicao[i++] = 0x45;// %eax
	codAtribuicao[i++] = (char) indice;

	return uniVet(codigo, codAtribuicao, posicao, i);
}

int DesvioCondicional(unsigned char *codigo, int posicao, char var0, int idx0, char var1, int idx1){
	int i = 0 ;
	int indice;
	unsigned char codDesvio[16];
	if ( var0 == '$' ){
		codDesvio[i++] = 0xB8;// %eax
		codDesvio[i++] = (char) ( idx0 );
		codDesvio[i++] = (char) ( idx0 >> 8 );
		codDesvio[i++] = (char) ( idx0 >> 16 );
		codDesvio[i++] = (char) ( idx0 >> 24 );
	}
	else{
		indice = ( var0 == 'p' ) ? (idx0+2)*4 : -(idx0+1)*4;
		codDesvio[i++] = 0x8B;
		codDesvio[i++] = 0x45;// %eax
		codDesvio[i++] = (char) indice;
	}

	if ( var1 == '$' ){
		codDesvio[i++] = 0xB9;// %ecx
		codDesvio[i++] = (char) ( idx1 );
		codDesvio[i++] = (char) ( idx1 >> 8 );
		codDesvio[i++] = (char) ( idx1 >> 16 );
		codDesvio[i++] = (char) ( idx1 >> 24 );
	}
	else{
		indice = ( var1 == 'p' ) ? (idx1+2)*4 : -(idx1+1)*4;
		codDesvio[i++] = 0x8B;
		codDesvio[i++] = 0x4D;// %ecx
		codDesvio[i++] = (char) indice;
	}

	return uniVet(codigo, codDesvio, posicao, i);
}
