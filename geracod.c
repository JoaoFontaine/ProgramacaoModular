/* Guilherme Araujo 1311835 Turma */
/* Joao Pedro Fontaine Matricula Turma */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM_MAX 1000

typedef int (*funcp) ();

static unsigned char comeco[]={0x55,0x89,0xe5,0x53,0x83,0xec,0x14}; /* salva o ebx e aloca espaco para 5 variaveis locais */

static unsigned char final[]={0x83,0xec,0x14,0x5b,0x89,0xec,0x5d,0xc3};  /* libera o ebx e o espaco das 5 variaveis locais */




static void error (const char *msg, int line) {
  fprintf(stderr, "erro %s na linha %d\n", msg, line);
  exit(EXIT_FAILURE);
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


funcp geracod (FILE *f){

	unsigned char * codigo = (unsigned char*)malloc(NUM_MAX*(sizeof(unsigned char)));
	int posicao = 0;
    int line = 1;
    int  c;
	int i=0;
    FILE *myfp;
	int jumpsnum[50];
	int jumpslinha[50];
	int enderecosnum[50];
	int enderecoslinha[50];
	posicao = uniVet(codigo, comeco, posicao, 7);

	if ((myfp = fopen ("programa", "r")) == NULL){
		perror ("nao conseguiu abrir arquivo!");
	}
	while ((c = fgetc(myfp)) != EOF) {

		enderecosnum[line-1]=(int) &codigo[posicao];  /*armazena os enderecos dos comandos*/
		enderecoslinha[line-1] = line;				/*armazena as linhas do comando  */

		switch (c) {
		  case 'r': {  /* retorno */
			int idx;
			char var;
			if (fscanf(myfp, "et %c%d", &var, &idx) != 2) 
				error("comando invalido", line);
			if (var != '$') checkVar(var, idx, line);
			printf("ret %c%d\n", var, idx);
			
			switch (var) {
				case '$': {
					codigo[posicao] = 0xb8;
					posicao ++;
				/*	codigo[posicao] = idx;   */

					break;
					}
				case 'p': {
					unsigned char aux[] = {0x8b, 0x45};
					posicao = uniVet(codigo,aux,posicao,2);
					codigo[posicao] = ((idx *4) + 8);
					posicao ++;
					break;
					}
				case 'v': {
					/**/
					break;
					}
			}
			posicao = uniVet(codigo,final,posicao,8);
			break;
			}
		
		  case 'i': {  /* ifeq */
			int idx0, idx1, num;
			char var0, var1;
			if (fscanf(myfp, "feq %c%d %c%d %d", &var0, &idx0, &var1, &idx1, 
		                                        &num) != 5)
			error("comando invalido i",line);
			if (var0 != '$') checkVar(var0, idx0, line);
			if (var1 != '$') checkVar(var1, idx1, line);
			printf("ifeq %c%d %c%d %d\n", var0, idx0, var1, idx1, num);

			jumpsnum[i]=num;      /*armazena os numeros dos desvios */
			jumpslinha[i]=line;   /*armazena a linha em que h� o comando de desvio */
			switch (var1) {
				case '$': {
					
			}
			break;
		  }

		case 'v': case 'p': case '$': {  /* atribuicao */
			int idx0, idx1, idx2;
			char var0 = c, var1, var2;
			char op;
			if (fscanf(myfp, "%d %c %c%d -> %c%d",
			           &idx0, &op, &var1, &idx1, &var2, &idx2) != 6)
			  error("comando invalido", line);
			if (var0 != '$') checkVar(var0, idx0, line);
			if (var1 != '$') checkVar(var1, idx1, line);
			checkVar(var2, idx2, line);
			printf("%c%d %c %c%d -> %c%d\n",
			        var0, idx0, op, var1, idx1, var2, idx2);
			break;
		}	
		default: error("comando desconhecido", line);
		}
		line ++;
		fscanf(myfp, " ");
	}	
	return (funcp)codigo;
	}