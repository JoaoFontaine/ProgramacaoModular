##################################################
###
### Diretivas de MAKE para o construto: INTERFACE
### Gerado a partir de: trab4.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = INTERFACE


### Nomes de paths

Pobj                 = .
Perr                 = .
PDEFAULT             = .
Pc                   = .

### Nomes de diretórios para geração

Fobj                 = .
Ferr                 = .
FDEFAULT             = .
Fc                   = .

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\Tab.obj   $(Fobj)\Lista.obj   $(Fobj)\Partida.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\Tab.obj :  {$(Pc)}\Tab.c \
    {$(PDEFAULT)}CESPDIN.h            {$(PDEFAULT)}CONTA.h              {$(PDEFAULT)}Generico.h           \
    {$(PDEFAULT)}LISTA.h              {$(PDEFAULT)}TAB.h                {$(PDEFAULT)}TST_Espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\Lista.obj :  {$(Pc)}\Lista.c \
    {$(PDEFAULT)}CESPDIN.h            {$(PDEFAULT)}Conta.h              {$(PDEFAULT)}GENERICO.h           \
    {$(PDEFAULT)}LISTA.h              {$(PDEFAULT)}TST_Espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\Partida.obj :  {$(Pc)}\Partida.c \
    {$(PDEFAULT)}LISTA.h              {$(PDEFAULT)}PARTIDA.h            {$(PDEFAULT)}TAB.h               
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\Tab.obj   $(Fobj)\Lista.obj   $(Fobj)\Partida.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: INTERFACE
###
##################################################

