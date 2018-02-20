#include "client.h"


	/******************************************************************************************************************************
	*  Comentários globais:                                                                                                       *
	*  Estas funções representam ações que envolvam ficheiros.                                                                    *
	*  Foram criadas funções que "encapsulam" outras de forma a permitir uma sintaxe mais fluída.                                 *
	*******************************************************************************************************************************/

 /*>>>>Função para abrir ficheiro em modo de leitura e escrita, aponta para o inicio*/
FILE* openfile(char* filex)
	{
		FILE *fptr;
		fptr = fopen(filex,"r+");
		return fptr;
	}

/*>>>>Função para abrir ficheiro em modo de leitura e escrita e aponta para o fim*/
FILE* openfile_append(char* filex) 
	{
		FILE *fptr;
		fptr = fopen(filex,"a+");
		return fptr;
	}

/*>>>>Função para fechar ficheiro*/
void closefile(FILE* closex) 
	{
		fclose(closex);
		return;
	}

