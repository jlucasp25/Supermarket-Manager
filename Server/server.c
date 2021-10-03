#include "server.h"

	/*****************************************************************************************************************************
	*  Comentários globais:                                                                                                      *
	*  Todas as ocorrências de system("clear") servem para limpar o ecrã do terminal.                                            *
	*  Foi criado um tipo de dados booleano de forma manual usando typedef e enum, para uma leitura mais fácil de certas funções.*
	*                                                                                                                            *
	*	                                                                                                                         *
	******************************************************************************************************************************/

	/*A função main inicia o programa e pede a palavra-passe do Gestor, se a palavra-passe corresponder, inicia o menu.
 	Caso contrário, encerra o programa.*/
	int main() 
		{
			//Declarações de dados
			char *passw = (char*) malloc(sizeof(char) * MAXSTR);
			char psx[] = "fcup17\n"; 
	
			//Instruções
			system("clear");
			printf("Insira a senha do GESTOR:\n");
			fgets(passw,MAXSTR,stdin);
			if (strcmp(passw,psx) == 0)
				{
					free(passw);
					system("clear");
					menuinit();
				}
			else
				{	
					free(passw);
					printf("A password inserida está incorrecta. O programa vai encerrar!\n");
				return -1;
				}
			return 0;
		}	