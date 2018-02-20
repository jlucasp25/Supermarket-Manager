#include "server.h"


	// usermanagment.c

	/*****************************************************************************************************************************
	*  Comentários globais:                                                                                                      *
	*  Todas as ocorrências de system("clear") servem para limpar o ecrã do terminal.                                            *
	*  Foi criado um tipo de dados booleano de forma manual usando typedef e enum, para uma leitura mais fácil de certas funções.*
	*                                                                                                                            *
	*	                                                                                                                         *
	******************************************************************************************************************************/

	/*>>>> O procedimento newuser é utilizada para criar um novo utilizador para o cliente e para guardar a informação no ficheiro<<<<*/
	
	void newuser()
		{
			//Declaração de dados
			FILE* filex = openfile_append("user_db");
			char* str = (char*) malloc(sizeof(char)*MAXSTR);
			//Instruções
			system("clear");
			fflush(filex); //Para limpar o buffer e permitir escrita
			getchar(); //Para absorver o \n do input buffer
           
			while (1)
				{			                                    /*******************************************************/
					printf("Novo utilizador:\nNome:");          /* Cada campo inclui um conjunto de verificações adequ-*/
					fgets(str,MAXSTR,stdin);	
					str[strlen(str)-1] = '\0';                  /* adas por razões lógicas.                            */
					if (verifysize(str,2,20) == false)          /* Em cima do cabeçalho de cada função estão descritas */
						{fprintf(filex,"%s#",str);break;}       /* as finalidades de cada função de verificação.       */
				}                                               /*                                                     */
			                                                    /*                                                     */
			while (1)                                           /*******************************************************/
				{
					printf("Contato:");                         /*:::: KNOWN BUGS :::*/
					fgets(str,MAXSTR,stdin);
					str[strlen(str)-1] = '\0'; 				//Cada fprintf insere um \n; possivel fix: concatenar todas as str e fazer um fprintf no fim
					if (verifysize(str,5,20) == false)
						{fprintf(filex,"%s#",str);break;}
				}

			while (1)
				{
					printf("Username:");
					fgets(str,MAXSTR,stdin);
					str[strlen(str)-1] = '\0'; 
					if (verifyuserpass(str,NULL,true) == false && verifyspecialchars(str) == false && verifysize(str,3,20) == false)
						{fprintf(filex,"%s#",str);break;}
					else
						printf("O utilizador inserido já existe, por favor utilize um nome diferente.\n"); /*!!!!!ESta mensagem aparece junto com outros erros*/
				}
			
			while (1)
				{
					printf("Password:");
					fgets(str,MAXSTR,stdin);
					str[strlen(str)-1] = '\0';
					if (verifyspecialchars(str) == false && verifysize(str,5,20) == false)
						{fprintf(filex,"%s#",str);break;}			
				}

			fprintf(filex,"0.00\n"); //Esta instrução adiciona o saldo do utilizador a 0.00 e muda de linha para permitir a próxima escrita
			
			printf("\nO novo utilizador foi adicionado com sucesso! Pressione ENTER para continuar...\n");
			getchar();

			//Instruções de encerramento		
			free(str);
			closefile(filex);
			return;
	}	

    /*>>>> A função verifyuserpass é utilizada para verificar se existe utilizador e password no ficheiro que guarda a informação<<<<*/
	
	bool verifyuserpass(char* userx, char* passwx,bool usronly)
		{
			//Declaração de dados
			FILE* filex = openfile("user_db");
			char* linha = (char*) malloc(sizeof(char) * MAXLINE);
			char* temp = (char*) malloc(sizeof(char) * MAXSTR);
			char* user = (char*) malloc(sizeof(char) * MAXSTR);
			char* passw = (char*) malloc(sizeof(char) * MAXSTR);
			bool verif = false;
		
			//Instruções
			while (fgets(linha,MAXLINE,filex) != NULL)
				{
					verif = false;
					sscanf(linha,"%[^#]#%[^#]#%[^#]#%[^#]#",temp,temp,user,passw);
					if (strcmp(userx,user) == 0) 
						{
							if (usronly == true)    /*A variável useronly é igual a 'true' quando apenas se deseja verificar se existe*/
								{                   /*		                       o nome do utilizador.                              */
									verif = true;
									break;
								}
							if (strcmp(passwx,passw) == 0)
								{
									verif=true;
									break;
								} 	
						}		
				}

		//Instruções de encerramento
		closefile(filex);
		free(linha);free(temp);free(user);free(passw);
		return verif;
	}

	/*>>>> A função verifyspecialchars é utilizada para verificar se existe algum caracter especial que cause conflitos no programa ou ficheiro<<<<*/
	
	bool verifyspecialchars(char* str)
		{
			if( (strchr(str,'#') != NULL) || (strchr(str,'%') != NULL) ) //Escolheu-se excluir os caracteres '%' e '#' pois serão usados como deliniadores nos ficheiros
				{
					printf("Este campo não pode conter carateres especiais como o '#' ou '%%'. Volte a introduzi-lo.\n");
					return true;
				}
			return false;		
		}

	/*>>>> A função verifysize é utilizada para verificar se o tamanho da string é menor que min ou maior que max<<<<*/

	bool verifysize(char* str, int min, int max)
		{
			if(strlen(str) < min || strlen(str)>max) /*Para impedir erros na formatação do ficheiro, escolheu-se impedir as strings de tomarem um*/
				{                                    /*                tamanho muito pequeno ou muito grande dependendo do caso                  */
					printf("Este campo não pode ter um tamanho menor que %d ou maior que %d. Volte a introduzi-lo.\n",min,max);
					return true;
				}
			return false;		
		}	