/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301 Jogo de Xadrez
*  Autores: avs
*  Coautores: Guilherme Araujo e Jo�o Pedro Fontaine
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*	  0       Gui   10/out/2014 acr�scimo de algumas fun��es
*
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/


/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/


typedef enum {

	LIS_CondRetOK = 0,
	/* Concluiu corretamente */

	LIS_CondRetListaVazia = 2 ,
	/* A lista n�o possui elementos */

	LIS_CondRetNaoExiste = 3 ,
	/* A lista nao existe */
	
	LIS_CondRetFimLista = 4,
	/* Foi atingido o fim de lista */
	
	LIS_CondRetNoCorrPrim = 5,
	/* N� corrente � o primeiro */

    LIS_CondRetFaltouMemoria = 6,
	/* Faltou mem�ria ao tentar criar um elemento de lista */

	LIS_TipoEspacoCabeca = 7,
	/* Tipo de espaco de dados cabeca */

	LIS_TipoEspacoNo = 8,
	/* Tipo de espaco de dados no */

	LIS_CondRetErroEstrutura = 9
	/* Estrutura da lista est� errada */

	LIS_CondRetNaoAchou = 10
	/* Elemento procurado n�o foi encontrado */

} LIS_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Modos de deturpar
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

         DeturpaTipoCabeca        =  1 ,
               /* Modifica o tipo da cabe�a */

         DeturpaCorrenteNulo      =  2 ,
               /* Anula ponteiro corrente */

         DeturpaCabecaLixo          =  3 ,
               /* Faz cabeca apontar para lixo */

         DeturpaCorrenteLixo      =  4 ,
               /* Faz corrente apontar para lixo */

         DeturpaTipoNo            =  5 ,
               /* Modifica tipo n� corrente */

         DeturpaPtCabecaNulo      =  6 ,
               /* Anula ponteiro cabe�a */

		 DeturpaPtOrigemNulo      =  7 ,
               /* Anula ponteiro origem */

		 DeturpaPtFimNulo      =  8 ,
               /* Anula ponteiro final */

         DeturpaPtProxNulo         =  9 ,
               /* Anula ponteiro proximo */

         DeturpaPtAntNulo         = 10 ,
               /* Anula ponteiro anterior */

         DeturpaPtCabecaLixo      = 11 ,
               /* Faz ponteiro cabe�a apontar para lixo */

         DeturpaPtOrigemLixo         = 12 ,
               /* Faz ponteiro origem apontar para lixo */

         DeturpaPtFimLixo         = 13 ,
               /* Faz ponteiro final apontar para lixo */

		DeturpaPtProxLixo         = 14 ,
               /* Faz prox apontar para lixo */

         DeturpaPtAntLixo         = 15 ,
               /* Faz anterior apontar para lixo */

         DeturpaValor             = 16 ,
               /* Atribui valor de tamanho 1 byte maior do que o alocado */

         DeturparEspacoCabeca     = 17 ,
               /* Deturpa espa�o da cabeca */

         DeturparEspacoNo         = 18,
               /* Deturpa espa�o do n� */

		 DeturparNumNo			  = 19
				/* Deturpa numero de nos */

   } LIS_tpModosDeturpacao ;

#endif


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     idLista  -     ponteiro para a estrutura identificadora
*						da lista
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

LIS_tppLista LIS_CriarLista( void * idLista ) ;     

/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter Id Lista
*
*  $ED Descri��o da fun��o
*     Obtem o ponteiro para a estrutura identificadora da lista
*     O par�metro ponteiro para a lista n�o � modificado.
*
*  $FV Valor retornado
*     Ponteiro para a estrutura identificadora da lista
*
***********************************************************************/

void * LIS_ObterIdLista( LIS_tppLista pLista );    

/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir no
*
*  $ED Descri��o da fun��o
*     Insere novo no ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     CondRetOK
*     CondRetFaltouMemoria
*
***********************************************************************/

LIS_tpCondRet LIS_InserirNo( LIS_tppLista pLista , void * pValor );    

/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no no
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no no corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     n�o NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

void * LIS_ObterNo( LIS_tppLista pLista );     

/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir no
*
*  $ED Descri��o da fun��o
*     Exclui o no corrente da lista dada.
*     Se existir o no aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o no � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*	  Se a lista estiver vazia, nao faz nada e retorna com mensagem de erro
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.

***********************************************************************/

void LIS_ExcluirNoCorr( LIS_tppLista pLista );     

/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir no proximo
*
*  $ED Descri��o da fun��o
*     Avan�a o no corrente  na lista em 1 no para frente
*
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista est� vazia
*
***********************************************************************/

LIS_tpCondRet LIS_IrProx( LIS_tppLista pLista ) ;   

/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir no anterior
*
*  $ED Descri��o da fun��o
*     O no corrente passa a ser o anterior do no corrente atual
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetNoCorrPrim - se o no corrente � o primeiro da lista,
*							nao realiza modificacoes
*     CondRetListaVazia - se a lista est� vazia
*
***********************************************************************/

LIS_tpCondRet LIS_IrAnt( LIS_tppLista pLista ) ;   

/***********************************************************************
*
*  $FC Fun��o: LIS  &Alterar no corrente
*
*  $ED Descri��o da fun��o
*     Altera o ponteiro para o valor do no corrente
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*     pValor - ponteiro para o novo valor do no corrente
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetNaoExiste  - se a lista nao existe
*     CondRetListaVazia - se a lista est� vazia
*
***********************************************************************/

LIS_tpCondRet LIS_AlterarNoCorr( LIS_tppLista pLista , void * pValor ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento inicial
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

void LIS_IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento final
*
*  $ED Descri��o da fun��o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

void LIS_IrFinalLista( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     Libera os espacos de dados correspondentes a todas as estruturas
*	  contidas na lista
*
*  $FV Valor retornado
*     CondRetOK         - destruiu sem problemas
*     CondRetNaoExiste  - se a lista nao existe
*
***********************************************************************/

LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;    


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

void LIS_EsvaziarLista( LIS_tppLista pLista );

LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista, void* pValor );

/***********************************************************************
*
*  $FC Fun��o: LIS  &Verificar uma lista
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Verifica completamente uma determinada lista.
*     Tamb�m marca todos os espa�os por ela ocupados.
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarLista( LIS_tppLista pLista) ;

#endif


/***********************************************************************
*
*  $FC Fun��o: LIS  &Verificar a cabeca da lista
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Verifica a integridade da cabeca da lista
*
*  $EP Par�metros
*     $P pLista - ponteiro para um espa�o que deveria ser uma cabe�a
*                      de lista.
*
*  $FV Valor retornado
*     Condi��o de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarCabeca( void * pLista ) ;

#endif


/***********************************************************************
*
*  $FC Fun��o: LIS  &Verificar um n� da lista
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Verifica a integridade de um n� da lista
*
*  $EP Par�metros
*     $P pNo - ponteiro para espa�o que deveria ser um n� da lista.
*
*  $FV Valor retornado
*      Condi��o de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarNo( void * pNo ) ;

#endif


   /***********************************************************************
*
*  $FC Fun��o: LIS  &Deturpar lista
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Corrompe elementos espec�ficos da estrutura da lista.
*     Essa fun��o destina-se a preparar os cen�rios de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da �rvore.
*     Esta fun��o n�o tem prote��o contra erros de uso, consequentemente
*     poder� levar o programa a ser cancelado pelo sistema operacional.
*
*  $EP Par�metros
*     $P pLista  - lista a ser deturpada
*     $P ModoDeturpar - identifica como deve ser feita a deturpa��o
*                       LIS_tpModosDeturpacao identifica os modos de
*                       deturpa��o conhecidos
*
***********************************************************************/

#ifdef _DEBUG

   void LIS_Deturpar( LIS_tppLista pLista ,
                      LIS_tpModosDeturpacao ModoDeturpar ) ;

#endif

   /********** Fim do m�dulo de defini��o: LIS  M�dulo lista **********/
