#include "client.h"	



	/*****************************************************************************************************************************
	*  Comentários globais:                                                                                                      *
	*  Todas as ocorrências de system("clear") servem para limpar o ecrã do terminal.                                            *
	*  Foi criado um tipo de dados booleano usando typedef e enum, de forma a que o código fique mais compreensivel.             *
	*  Todas as strings que representam uma linha são de tamanho 100.                                                            *
	*  Instruções semelhantes vão ser colocadas na mesma linha para compactar o código.                                          *
	*****************************************************************************************************************************/

	/*>>>> A função main inicia o programa, recebe o nome de utilizador e palavra-passe, chama a função que as valida, e invoca o menu principal. */

	int main()
		{		
		  //Declaração de dados
		  char *userx = (char*) malloc(sizeof(char) * MAXSTR);
		  char *passwx = (char*) malloc(sizeof(char) * MAXSTR);
  			
		  //Instruções
		  system("clear");
  		
		  printf("Insira o seu username:\n");            /***************************************************************************/
		  fgets(userx,MAXSTR,stdin); 	                 /* Pede ao utilizador, o nome de utilizador e a palavra-passe. A cada uma  */
		  userx[strlen(userx) - 1] = '\0';               /* das strings recebidas, retira o '\n' para poder compará-las com os nomes*/
		                                                 /* respectivos que se encontram no ficheiro que guarda a informação dos    */
		  printf("Insira a sua password:\n");            /* utilizadores.                                                           */
		  fgets(passwx,MAXSTR,stdin);                    /***************************************************************************/
		  passwx[strlen(passwx) - 1] = '\0';
		  
		  if (verifyuserpass(userx,passwx,false) == true)    /******************************************************************************/
		    {                                                /* No caso de os dados serem verificados ou não, ambos os casos libertam      */
		      free(passwx);                                  /* memória das strings alocadas. Em caso de aceitação é invocado o menu e é   */
		      system("clear");                               /* passado como argumento a string que contém o nome de utilizador. Apenas é  */
		      menuinit(userx);                               /* libertada a string da password. Em caso contrário, uma mensagem de erro é  */
		    }	                                             /* apresentada, são libertadas ambas as strings e o programa encerra.         */ 
		  else                                               /******************************************************************************/
		    {
		      free(userx);
		      free(passwx);
		      printf("Não foi encontrado nenhuma combinação utiilizador/password correta!\n");
		      return -1;
		    }
		  return 0;
		}
