/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301 Jogo de Xadrez
*  Autores: avs
*  Coautores: Guilherme Araujo e João Pedro Fontaine
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*	  0       Gui   10/out/2014 acréscimo de algumas funções
*
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/


/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/


typedef enum {

	LIS_CondRetOK = 0,
	/* Concluiu corretamente */

	LIS_CondRetListaVazia = 2 ,
	/* A lista não possui elementos */

	LIS_CondRetNaoExiste = 3 ,
	/* A lista nao existe */
	
	LIS_CondRetFimLista = 4,
	/* Foi atingido o fim de lista */
	
	LIS_CondRetNoCorrPrim = 5,
	/* Nó corrente é o primeiro */

    LIS_CondRetFaltouMemoria = 6,
	/* Faltou memória ao tentar criar um elemento de lista */

	LIS_TipoEspacoCabeca = 7,
	/* Tipo de espaco de dados cabeca */

	LIS_TipoEspacoNo = 8,
	/* Tipo de espaco de dados no */

	LIS_CondRetErroEstrutura = 9
	/* Estrutura da lista está errada */

	LIS_CondRetNaoAchou = 10
	/* Elemento procurado não foi encontrado */

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
               /* Modifica o tipo da cabeça */

         DeturpaCorrenteNulo      =  2 ,
               /* Anula ponteiro corrente */

         DeturpaCabecaLixo          =  3 ,
               /* Faz cabeca apontar para lixo */

         DeturpaCorrenteLixo      =  4 ,
               /* Faz corrente apontar para lixo */

         DeturpaTipoNo            =  5 ,
               /* Modifica tipo nó corrente */

         DeturpaPtCabecaNulo      =  6 ,
               /* Anula ponteiro cabeça */

		 DeturpaPtOrigemNulo      =  7 ,
               /* Anula ponteiro origem */

		 DeturpaPtFimNulo      =  8 ,
               /* Anula ponteiro final */

         DeturpaPtProxNulo         =  9 ,
               /* Anula ponteiro proximo */

         DeturpaPtAntNulo         = 10 ,
               /* Anula ponteiro anterior */

         DeturpaPtCabecaLixo      = 11 ,
               /* Faz ponteiro cabeça apontar para lixo */

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
               /* Deturpa espaço da cabeca */

         DeturparEspacoNo         = 18,
               /* Deturpa espaço do nó */

		 DeturparNumNo			  = 19
				/* Deturpa numero de nos */

   } LIS_tpModosDeturpacao ;

#endif


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     idLista  -     ponteiro para a estrutura identificadora
*						da lista
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

LIS_tppLista LIS_CriarLista( void * idLista ) ;     

/***********************************************************************
*
*  $FC Função: LIS  &Obter Id Lista
*
*  $ED Descrição da função
*     Obtem o ponteiro para a estrutura identificadora da lista
*     O parâmetro ponteiro para a lista não é modificado.
*
*  $FV Valor retornado
*     Ponteiro para a estrutura identificadora da lista
*
***********************************************************************/

void * LIS_ObterIdLista( LIS_tppLista pLista );    

/***********************************************************************
*
*  $FC Função: LIS  &Inserir no
*
*  $ED Descrição da função
*     Insere novo no após o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
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
*  $FC Função: LIS  &Obter referência para o valor contido no no
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no no corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

void * LIS_ObterNo( LIS_tppLista pLista );     

/***********************************************************************
*
*  $FC Função: LIS  &Excluir no
*
*  $ED Descrição da função
*     Exclui o no corrente da lista dada.
*     Se existir o no aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o no à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*	  Se a lista estiver vazia, nao faz nada e retorna com mensagem de erro
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.

***********************************************************************/

void LIS_ExcluirNoCorr( LIS_tppLista pLista );     

/***********************************************************************
*
*  $FC Função: LIS  &Ir no proximo
*
*  $ED Descrição da função
*     Avança o no corrente  na lista em 1 no para frente
*
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

LIS_tpCondRet LIS_IrProx( LIS_tppLista pLista ) ;   

/***********************************************************************
*
*  $FC Função: LIS  &Ir no anterior
*
*  $ED Descrição da função
*     O no corrente passa a ser o anterior do no corrente atual
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetNoCorrPrim - se o no corrente é o primeiro da lista,
*							nao realiza modificacoes
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

LIS_tpCondRet LIS_IrAnt( LIS_tppLista pLista ) ;   

/***********************************************************************
*
*  $FC Função: LIS  &Alterar no corrente
*
*  $ED Descrição da função
*     Altera o ponteiro para o valor do no corrente
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*     pValor - ponteiro para o novo valor do no corrente
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetNaoExiste  - se a lista nao existe
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

LIS_tpCondRet LIS_AlterarNoCorr( LIS_tppLista pLista , void * pValor ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

void LIS_IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

void LIS_IrFinalLista( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
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
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

void LIS_EsvaziarLista( LIS_tppLista pLista );

LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista, void* pValor );

/***********************************************************************
*
*  $FC Função: LIS  &Verificar uma lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica completamente uma determinada lista.
*     Também marca todos os espaços por ela ocupados.
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarLista( LIS_tppLista pLista) ;

#endif


/***********************************************************************
*
*  $FC Função: LIS  &Verificar a cabeca da lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica a integridade da cabeca da lista
*
*  $EP Parâmetros
*     $P pLista - ponteiro para um espaço que deveria ser uma cabeça
*                      de lista.
*
*  $FV Valor retornado
*     Condição de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarCabeca( void * pLista ) ;

#endif


/***********************************************************************
*
*  $FC Função: LIS  &Verificar um nó da lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica a integridade de um nó da lista
*
*  $EP Parâmetros
*     $P pNo - ponteiro para espaço que deveria ser um nó da lista.
*
*  $FV Valor retornado
*      Condição de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarNo( void * pNo ) ;

#endif


   /***********************************************************************
*
*  $FC Função: LIS  &Deturpar lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Corrompe elementos específicos da estrutura da lista.
*     Essa função destina-se a preparar os cenários de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da árvore.
*     Esta função não tem proteção contra erros de uso, consequentemente
*     poderá levar o programa a ser cancelado pelo sistema operacional.
*
*  $EP Parâmetros
*     $P pLista  - lista a ser deturpada
*     $P ModoDeturpar - identifica como deve ser feita a deturpação
*                       LIS_tpModosDeturpacao identifica os modos de
*                       deturpação conhecidos
*
***********************************************************************/

#ifdef _DEBUG

   void LIS_Deturpar( LIS_tppLista pLista ,
                      LIS_tpModosDeturpacao ModoDeturpar ) ;

#endif

   /********** Fim do módulo de definição: LIS  Módulo lista **********/
