#include "client.h"


	
/******************************************************************************************************************************
 *  Comentários globais:                                                                                                       *
 *  Sem comentários.                                                                                                           *
 *******************************************************************************************************************************/

/*>>>>Função para verificar se existe utilizador e password (se o valor usronly for true apenas verifica a existência de utilizador)*/
bool verifyuserpass(char* userx, char* passwx,bool usronly) 
{
  //Declaração de dados
  FILE* filex = openfile("user_db");

  char* linha = (char*) malloc(sizeof(char) * MAXLINE);
  char* user = (char*) malloc(sizeof(char) * MAXSTR);
  char* pass = (char*) malloc(sizeof(char) * MAXSTR);
  char* temp = (char*) malloc(sizeof(char) * MAXSTR);
  bool verif = false;

  //Instruções
  if (filex == NULL)
        {
          printf("ERRO! Use o shell script para criar os ficheiros de db na primeira vez que iniciar o programa.\nPrima ENTER para continuar...");
          getchar();
          return false;
        }
  while (fgets(linha,100,filex) != NULL)
    {
      sscanf(linha,"%[^#]#%[^#]#%[^#]#%[^#]#%[^#]",temp,temp,user,pass,temp);
      if (strcmp(userx,user) == 0)
	{
	  if (usronly == true)
	    {
	      verif = true;break;
	    }
	  if (strcmp(passwx,pass) == 0)
	    {
	      verif = true;break;
	    } 	
	}		
    }

  //Instruções de finalização
  closefile(filex);
  free(linha);
  free(user);
  free(pass);
  return verif;
}
