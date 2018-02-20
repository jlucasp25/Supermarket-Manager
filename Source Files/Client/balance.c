#include "client.h" 
#include <unistd.h>
#include <sys/types.h>



	/*****************************************************************************************************************************
	*  Comentários globais:                                                                                                      *
	*  Sem Comentários                                                                                                           *
	*****************************************************************************************************************************/

	/*>>>> Esta função procura a linha que contém a informação do cliente e extrai o saldo.*/
	
	float extractbalance(char* userx)
		{
			//Declaração de dados
			FILE* fileu = openfile("user_db");
			char* str = (char*) malloc(sizeof(char)* MAXLINE);
			char* user = (char*) malloc(sizeof(char)*MAXSTR);
			char* temp = (char*) malloc(sizeof(char)*MAXSTR);
			char* temp2 = (char*) malloc(sizeof(char)*MAXSTR);
			float balance = -1.00;

			//Instruções
			while (fgets(str,MAXLINE,fileu) != NULL)
				{
				  fflush(fileu);
				  sscanf(str,"%[^#]#%[^#]#%[^#]#%[^#]#%f\n",temp,temp,user,temp,&balance);
				  fflush(fileu);
					if (strcmp(user,userx) == 0)
						{
							break;
						}
				}
			
			//Instruções de finalização
			closefile(fileu);free(str);free(user);free(temp);return balance;
	}

	/*>>>> Esta função permite ao cliente adicionar fundos ao seu saldo, atualizando a sua informação no ficheiro.*/
	
	void addfunds(char* userx)
		{
			//Declaração de dados
			FILE* fileu = openfile("user_db");
			
			char* str = (char*) malloc(sizeof (char) * MAXLINE);
			char* name = (char*) malloc(sizeof(char) * MAXSTR);
			char* contact = (char*) malloc(sizeof(char) * MAXSTR);
			char* user = (char*) malloc(sizeof(char) * MAXSTR);
			char* passw = (char*) malloc(sizeof(char) * MAXSTR);
			char* temp = (char*) malloc(sizeof(char) * MAXSTR);
			
			float saldo = 0.00;
			float add = 0.00;
			int linha = 1;
			int i = 0;
			int offset = 0;
			int fxdescriptor = 0;
			long filesize = 0;
			long until = 0;
			long buffersize = 0;

			//Instruções
			getchar();

			/*Procura a linha que contém a informação do utilizador, extrai as informações e mostra o saldo. De seguida pede ao
			utilizador quanto é que deve adicionar,soma ao saldo inicial e atualiza o ficheiro. */
			while (fgets(str,MAXLINE,fileu) != NULL)
				{
					sscanf(str,"%[^#]#%[^#]#%[^#]#%[^#]#%f",name,contact,user,passw,&saldo);
					if (strcmp(user,userx) == 0)
						{
							printf("Tem %.2f de saldo. Quanto deseja adicionar?\n",saldo);
							fgets(temp,MAXSTR,stdin);
							if (atof(temp) == 0.00)
								{
									printf("Ocorreu um erro.\n");
									getchar();
									return; 
								}
							else
								{
									saldo += atof(temp);
									
									//Tamanho do ficheiro em bytes
									fseek(fileu,0L,SEEK_END);
									filesize = ftell(fileu);
									
									//Tamanho em bytes até à linha a editar
									rewind(fileu);
									for (i = 0 ; i < linha ; i++)
										{
											fgets(str,MAXLINE,fileu);
											until+=strlen(str);
										}

									//O tamanho do buffer será (tamanho_total-tamanho_ate_editar) bytes
									buffersize = filesize - until;
									char* buffer = (char*) malloc(sizeof(char)*buffersize);

									//Concatena tudo até ao final do ficheiro no buffer
									while (fgets(str,MAXLINE,fileu) != NULL)
										{
											strcat(buffer,str);
										}

									//Posiciona o ficheiro no local para inserir a linha	
									rewind(fileu);
									for (i = 0 ; i < (linha - 1) ; i++)
										{
											fgets(temp,MAXSTR,fileu);
										}

									//Cria um descritor de ficheiro a partir da estrutura FILE*
									fxdescriptor = fileno(fileu);

									//Trunca o ficheiro
									ftruncate(fxdescriptor,until);
									
									//Imprime a linha editada e o buffer para o ficheiro
									fprintf(fileu,"%s#%s#%s#%s#%.2f\n",name,contact,user,passw,saldo);
									fputs(buffer,fileu);
									break;
								}
							}
							linha++;
				}

			//Instruções de finalização
			closefile(fileu);free(str);free(user);free(temp);free(name);free(contact);free(passw);return;
	}
