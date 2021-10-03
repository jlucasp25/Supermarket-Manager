	#include "server.h" 

	
	/*****************************************************************************************************************************
	*  Comentários globais:                                                                                                      *
	*  Foram criadas structs para guardar informação dos produtos e dos utilizadores para as estatisticas.                       *
	*                                                                                                                            *
	*                                                                                                                            *
	*	                                                                                                                         *
	******************************************************************************************************************************/

	/*>>>> O procedimento listproducts lista as estatisticas e armazena as na estrutura*/
	void listproducts(prodstat* ptstat) {

		//Declarações de dados iniciais
		FILE* filex = openfile("shoppinglist_db");
		char* str = (char*) malloc(sizeof(char)*MAXLINE);
		char* str2 = (char*) malloc(sizeof(char)*MAXLINE);
		int index = 0;
		float qtd,prcf;

        //Instruções
		if(filex==NULL) {
			return;
		}
		while (fgets(str,MAXLINE,filex) != NULL)
			{
				if ((*(str+0)=='u' && *(str+1)=='s' && *(str+2)=='e'))
					{
						fgets(str,MAXLINE,filex);
						sscanf(str,"%[^#]#%f#%f",str2,&qtd,&prcf);
						index = searchcode(str2);
						strcpy((*(ptstat+index-1)).name,str2);
						(*(ptstat+index-1)).qtd+=qtd;
						(*(ptstat+index-1)).prcf+=prcf;
					}
				else if((*(str+0)=='t' && *(str+1)=='o' && *(str+2)=='t'))
					{
						fgets(str,MAXLINE,filex);
						if (fgets(str,MAXLINE,filex) == NULL)
							{break;}
						else 
							{
								fgets(str,MAXLINE,filex);
								sscanf(str,"%[^#]#%f#%f",str2,&qtd,&prcf);
								index = searchcode(str2);
								strcpy((*(ptstat+index-1)).name,str2);
								(*(ptstat+index-1)).qtd+=qtd;
								(*(ptstat+index-1)).prcf+=prcf;		
							} 
					}
				else
					{ 
						sscanf(str,"%[^#]#%f#%f",str2,&qtd,&prcf);
						index = searchcode(str2);
						strcpy((*(ptstat+index-1)).name,str2);
						(*(ptstat+index-1)).qtd+=qtd;
						(*(ptstat+index-1)).prcf+=prcf;
					}
			}
		free(str);
		free(str2);
		closefile(filex);
	}

	/*>>>> O procedimento updateprdctcost atualiza o preço de custo na estructura*/
	void updateprdctcost(prodstat* ptstat)
		{
			//Declarações de dados iniciais
			FILE* filex = openfile("product_db");
			char* str = (char*) malloc(sizeof(char)*MAXLINE);
			char* temp = (char*) malloc(sizeof(char)*MAXLINE);
			int linha = 1;
			int offset = 0;

			//Instruções
			while (fgets(str,MAXLINE,filex) != NULL)
				{
					strcpy(temp,str+offset);
					if (strcmp(strtok(temp,"#"),(*(ptstat+linha)).name) == 0)
					{
						offset+=(strlen(temp)+1);
						strcpy(temp,str+offset);
						strtok(temp,"#");
						offset+=(strlen(temp)+1);
						strcpy(temp,str+offset);
						(*(ptstat+linha)).prcc = atof(strtok(temp,"#")); 
					}
					offset = 0;
					linha++;
				}
			closefile(filex);free(str);free(temp);
		}

	/*>>>> O procedimento listusers guarda na estrutura a informação dos utilizadores*/
	void listusers(userstat* ptustat)
		{
			//Declarações de dados iniciais
			FILE* fileu = openfile("user_db");
			char* str = (char*) malloc(sizeof(char)*MAXLINE);
			char* tmp = (char*) malloc(sizeof(char)*MAXLINE);
			int i = 0;

            //Instruções
			if(fileu==NULL) {
				return;

			}
			while (fgets(str,MAXLINE,fileu) != NULL)
				{	
					sscanf(str,"%[^#]#%[^#]#%[^#]#%[^#]#%f",(*(ptustat+i)).name,(*(ptustat+i)).contact,(*(ptustat+i)).uname,tmp,&(*(ptustat+i)).saldo);
					i++;
				}
		closefile(fileu);
		free(str);free(tmp);
		}

	/*>>>> O procedimento listofclients lista os clientes registados e mostra as informações colectadas */
	int listofclients(userstat* ptustat)
			{
				
				//Declarações de dados iniciais
				int i = 0, x = 0;


				//Instruções
				system("clear");
				printf("++++++++++++++++++++++++++Clientes registados na loja+++++++++++++++++++++++++++++++\n");
				printf("+----------------------------------------------------------------------------------+\n");
				printf("|Código     |Nome                            |Contacto             |Saldo          |\n");
				while (i < MAXLINE)
					{
						if (strcmp("",((*(ptustat+i)).name)) != 0)
						{
							printf("|%11d|%32s|%21s|%15.2f|\n",(i+1),(*(ptustat+i)).name,(*(ptustat+i)).contact,(*(ptustat+i)).saldo);
						}
						i++;
					}
				printf("+----------------------------------------------------------------------------------+\n\n");
				printf("Insira o numero do cliente que deseja ver as compras efectuadas:");
				scanf("%d",&x);
				return x;
			}

	/*>>>> O procedimento shoppinglistbyclient mostra as listas de compras por utilizador*/
	void shoppinglistbyclient(userstat* ptustat)
		{	
		    //Declarações de dados iniciais
			int cliente = listofclients(ptustat);
			system("clear");
			int offset = 0;
			int i = 1;
			FILE* filesl = openfile("shoppinglist_db");
			char* str = (char*) malloc(sizeof(char)*MAXLINE);
			char* temp = (char*) malloc(sizeof(char)*MAXLINE);
			printf("Cliente:%s\n\n",(*(ptustat+cliente-1)).name);

            //Instruções
			while (fgets(str,MAXLINE,filesl) != NULL)
				{
				if (*str == 'u' && *(str+1) == 's' && *(str+2) == 'e' && *(str+3) == 'r')
					{
						strcpy(temp,str+5);
						strtok(temp,"\n");
						if (strcmp(temp,(*(ptustat+cliente-1)).uname) == 0)
							{
								printf("+--------------------------Compra %d--------------------------------------+\n",i);
								printf("|Produto                         | Quantidade comprada | Preco final     |\n");
								fgets(str,MAXLINE,filesl);
								while(strcmp(str,"%%\n") != 0)
									{
										if (*str == 't' && *(str+1) == 'o' && *(str+2) == 't')
											{
												strcpy(temp,str+4);
												printf("|--------------------------- total: %.2f --------------------------------|\n",atof(temp));
												printf("+------------------------------------------------------------------------+\n\n\n");	
												offset = 0;
												i++;
												fgets(str,MAXLINE,filesl);
												break;
											}
										strcpy(temp,str+offset);
										strtok(temp,"#");
										offset+=(strlen(temp)+1);
				 						printf("|%32s|",temp);
										strcpy(temp,str+offset);
										strtok(temp,"#");
										offset+=(strlen(temp)+1);
										printf("%21s|",temp);
										strcpy(temp,str+offset);
										strtok(temp,"#");
										offset+=(strlen(temp)+1);
										temp[strlen(temp)-1] = '\0';
										printf("%17s",temp);
										printf("|\n");
										fgets(str,MAXLINE,filesl);
										offset = 0;
									}
							}
					}
			}
		printf("Prima ENTER para continuar ...");
		getchar();
		getchar();
		closefile(filesl);
		free(str);
		free(temp);
	}

	/*>>>> O procedimento listprdctsstats mostra as estatisticas de cada producto */
	void listprdctsstats(prodstat* ptstat,bool allinfo)
		{
		    //Declarações de dados iniciais
			int i=0;
			system("clear");
			char* str = (char*) malloc(sizeof(char)*MAXSTR);

			//Instruções
			if (allinfo == true)
			{
			printf("++++++++++++Quantidade total e preço pago pelos clientes por produto++++++++++++++++\n");
			printf("+----------------------------------------------------------------------------------+\n");
			printf("|Código     | Descrição                      |Quantidade comprada | Dinheiro gasto |\n");
			while (i < MAXLINE)
				{
					if ((*(ptstat+i)).prcf != 0.00)
					{
						sprintf(str,"%d",(i+1));
						printf("|%11s",str);
						printf("|%32s|",(*(ptstat+i)).name);
						sprintf(str,"%.2f",(*(ptstat+i)).qtd);
						printf("%20s|",str);
						sprintf(str,"%.2f",(*(ptstat+i)).prcf);
						printf("%16s|\n",str);
					}
					i++;
				}
			printf("+----------------------------------------------------------------------------------+\n\n");
			printf("Prima ENTER para continuar...");
			getchar();
			getchar();
			}
			else
			{	
			printf("++++++++++++Quantidade total e preço pago pelos clientes por produto++++++++++++++++\n");
			printf("+----------------------------------------------------------------------------------+\n");
			printf("|Código     | Descrição                                                            |\n");
			while (i < MAXLINE) /*pq é o tamanho do array maximo neste caso*/
				{
					if ((*(ptstat+i)).prcf != 0.00)
					{
						printf("%11d",(i+1));
						printf("|%70s|\n",(*(ptstat+i)).name);
					}
					i++;
				}
			printf("+----------------------------------------------------------------------------------+\n\n");
			}
			free(str);
			return;}

	/*>>>> A função searchcode recebe um nome e retorna a linha do utilizador desejado*/
	int searchcode(char* name)
		{
			//Declarações de dados iniciais
			FILE* filep = openfile("product_db");
			char* str = (char*) malloc(sizeof(char)*MAXLINE);
			char* substr = (char*) malloc(sizeof(char)*MAXLINE);
			int linha = 1;

			//Instruções
			while (fgets(str,MAXLINE,filep) != NULL)
				{
					strcpy(substr,str);
					strtok(substr,"#");
					if (strcmp(name,substr) == 0)
						{free(str);free(substr);return linha;}
					linha++;
				}
			closefile(filep);free(str);free(substr);		
			return -1;
		}

	/*>>>> O procedimento askproduct permite ver a estatistica de um determinado produto*/
	void askproduct(bool isqtd,prodstat* ptstat)
		{
			//Declarações de dados iniciais
			int x=0;
			float lucro = 0.00;

            //Instruções
            system("clear");
			listprdctsstats(ptstat,false);
			if (isqtd == true)
			{
				printf("Insira o código do produto que deseja ver a quantidade vendida:");
				scanf("%d",&x);
				printf("Foi vendido %.2f de %s.\n",(*(ptstat+x-1)).qtd,(*(ptstat+x-1)).name);
			}
			else {
				printf("Insira o código do produto que deseja ver o lucro gerado:"); 
																											
				scanf("%d",&x);
				lucro = (float) ( ((*(ptstat+x-1)).prcf) / ((*(ptstat+x-1)).qtd) ) - ((*(ptstat+x-1)).prcc);
				printf("O lucro do produto %s foi de %.2f.\n",(*(ptstat+x-1)).name,lucro);
			}
			printf("\nPrima ENTER para continuar...");
			getchar();
			getchar();
		}