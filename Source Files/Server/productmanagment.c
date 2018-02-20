#include "server.h"


  	/*>>>> O procedimento editproduct permite editar ou remover um produto.*/
	void editproduct(bool edit) /*true para editar, false para remover*/
		{
			//Declaração de dados
			char* str = (char*) malloc(sizeof(char)*MAXSTR);
			char* product = (char*) malloc(sizeof(char)*MAXLINE);
			int linha = 0;
			str[0] = '\0';

			//Instruções
			system("clear");
			getchar();
			while (1)
				{
					FILE* filex = openfile("product_db");
					if (filex == NULL)
						{
					printf("Nao existe algum ficheiro necessário. Utilize o shell script para criar os ficheiros na primeira vez que iniciar o programa.\nPrima ENTER para continuar...");
					getchar();
					getchar();
					return;
						}
					listproduct();	
					rewind(filex);	
					printf("Insira o código do produto a editar/remover (ou 'q' para voltar):");
					
					fgets(str,MAXSTR,stdin);
					linha = atoi(str);
					if (str[0] == 'q') 
						{
							free(str);
							free(product);
							closefile(filex);
							system("clear");
							return;
						}
					else
						{
							closefile(filex);
							if (edit == true)
								editmenu(linha);
							else
								removemenu(linha);

						}
					system("clear");
				}
			free(str);
			free(product);	
			return;
		}

	/*>>>> A função listproduct é utilizada para mostrar no ecrã uma tabela com a informação de todos os produtos<<<<*/
	void listproduct() //optimizada
		{
			//Declaraçoes de dados
			FILE* filex = openfile("product_db");
			char* str = (char*) malloc(sizeof(char) * MAXLINE);
			char* print = (char*) malloc(sizeof(char) * MAXLINE);
			int offset = 0;
			int codigo = 1;
			
			//Instruções
			printf("+----------------------------------------------------------------------------------+\n");
			printf("|Código     | Descrição                   | Quantidade | Preço Custo | Preço Venda |\n");
			while (fgets(str,MAXLINE,filex) != NULL)
				{

					printf("|%11d",codigo);     			/*************************************************************/
												            /* Antes de imprimir 'print', adiciona-se a str, (offset).   */
					strcpy(print,(str+offset));		       /* (offset) corresponde ao comprimento do que foi impresso   */
					printf("|%29s",strtok(print,"#"));     /*  + o delineador, ou seja strlen(print) + 1.               */
					offset+=(strlen(print)+1);             /*************************************************************/
					strcpy(print,(str+offset));           
					printf("|%12s",strtok(print,"#"));
					offset+=(strlen(print)+1);
					strcpy(print,(str+offset));
					printf("|%13s",strtok(print,"#"));
					offset+=(strlen(print)+1);
					strcpy(print,(str+offset));
					printf("|%13s|\n",strtok(print,"\n"));
					codigo++;	
					offset = 0;	
				} 
			printf("+----------------------------------------------------------------------------------+\n\n");
			
			//Instruções de finalização
			free(print);
			free(str);
			closefile(filex);
			return;
	}

	/*>>>> A função printproduct é utilizada para mostrar no ecrã a informação de um produto seleccionado<<<<*/
	
	void printproduct(int linha)
		{
			//Declarações de dados
			FILE* filex = openfile("product_db");
			char* str = (char*) malloc(sizeof(char) * MAXLINE);
			char* print = (char*) malloc(sizeof(char) * MAXLINE);
			int offset=0;
			int i;
						
			//Instruções
			for (i = 0;i<linha;i++)
			{
				fgets(str,MAXSTR,filex); 					/*Sendo que o código do produto é igual à linha em que se encontra no ficheiro*/ 
			}                        					/*          , este ciclo permite encontrar a linha do produto                 */
			
			printf("Código:%d\n",linha);                    
									                                 /*************************************************************/
			strcpy(print,(str+offset));                               /* Antes de imprimir 'print', adiciona-se a str, (offset).   */
			printf("Descrição:%s\n",strtok(print,"#"));               /* (offset) corresponde ao comprimento do que foi impresso   */
			offset+=(strlen(print)+1);                                /*  + o delineador, ou seja strlen(print) + 1.               */
			strcpy(print,(str+offset));                               /*************************************************************/                                                                
			printf("Quantidade:%s\n",strtok(print,"#"));
			offset+=(strlen(print)+1);
			strcpy(print,(str+offset));
			printf("Preço de Custo:%s\n",strtok(print,"#"));
			offset+=(strlen(print)+1);
			strcpy(print,(str+offset));
			printf("Preço de Venda:%s\n",strtok(print,"\n"));
			
			//Instruções de Finalização
			free(str);
			free(print);
			return;
	}

	/*>>>> A função insertproduct é utilizada para inserir um novo produto no ficheiro que guarda a informacao<<<<*/

	void insertproduct()
		{
			//Declarações de dados iniciais
			FILE* filer = openfile("product_db");	
			char* str = (char*) malloc(sizeof(char)*MAXLINE);
			int codigo = 0;

			//Instruções
			system("clear");
			if (filer == NULL)
				{
					printf("Nao existe algum ficheiro necessário. Utilize o shell script para criar os ficheiros na primeira vez que iniciar o programa.\nPrima ENTER para continuar...");
					getchar();
					getchar();
					return;
				}	

			//Obter o próximo código automaticamente (os códigos são sequenciais)
			while (fgets(str,MAXLINE,filer) != NULL)
				{
					codigo++; /*Cada linha representa um produto, logo percorrer o ficheiro até ao EOF devolve o código mais recente*/
				}
			codigo++;
			closefile(filer);

			//Inserir novo produto
			FILE* filex = openfile_append("product_db");
			getchar(); //Para absorver o barra n do input buffer 

			printf("Novo produto\nCodigo:%d\n",codigo);

			while (1)
				{
					printf("Nome:");
					fgets(str,MAXLINE,stdin);
					str[strlen(str)-1] = '\0';  
					if (verifyspecialchars(str) == false && verifysize(str,3,MAXSTR) == false)
						{fprintf(filex,"%s#",str);break;}
				}

			while (1)
				{
					printf("Quantidade (forma: xx.yy) :");
					fgets(str,MAXLINE,stdin);
					if (verifyspecialchars(str) == false)
						{
							if (atof(str) == 0.0) //Se atof retornar 0.0 não efectuou a conversão
								{
									printf("Inseriu algo inválido. A quantidade é na forma xx.yy . Volte a tentar.");
									getchar();
								}
							else 
								{
									fprintf(filex,"%.2f#",atof(str));break;
								}
						}
				}

			while (1)
				{
					printf("Preço de Custo:");
					fgets(str,MAXLINE,stdin);
					if (verifyspecialchars(str) == false)
						{
							if (atof(str) == 0.0) //Se atof retornar 0.0 não efectuou a conversão
								{
									printf("Inseriu algo inválido. O preco de custo é na forma xx.yy . Volte a tentar.");
									getchar();
								}
							else 
								{
									fprintf(filex,"%.2f#",atof(str));break;
								}
						}
				}
			float verifcusto = atof(str);
			while (1)
				{
					printf("Preço de Venda:");
					fgets(str,MAXLINE,stdin);
					if (verifyspecialchars(str) == false)
						{
							if (atof(str) == 0.0) //Se atof retornar 0.0 não efectuou a conversão
								{
									printf("Inseriu algo inválido. O preco de venda é na forma xx.yy . Volte a tentar.");
									getchar();
								}
							else if (verifcusto >= atof(str))
								{
									printf("O preco de venda nao pode ser inferior ao preco de custo. Volte a tentar.");
									getchar();
								}
							else 
								{
									fprintf(filex,"%.2f\n",atof(str));break;
								}
						}
				}

			printf("\nO produto foi adicionado com sucesso... Prima Enter para continuar..\n"); 
			getchar();
			//Instruções de encerramento
			closefile(filex);
			free(str);
			return;	
		}


