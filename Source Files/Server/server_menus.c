#include "server.h"

	/*****************************************************************************************************************************
	*  Comentários globais:                                                                                                      *
	*  Todas as ocorrências de system("clear") servem para limpar o ecrã do terminal.                                            *
	*  Foi criado um tipo de dados booleano de forma manual usando typedef e enum, para uma leitura mais fácil de certas funções.*
	*                                                                                                                            *
	*	                                                                                                                         *
	******************************************************************************************************************************/

	/*>>>> O procedimento menuinit imprime as opções de escolha do menu principal e é a ponte entre os vários menus do programa.*/
	void menuinit()
		{
			//Declarações de dados
			char x = '0';
			
			//Instruções
			while (1)
				{
					system("clear");
					printf("Bem vindo ao 'server'!\nO Painel de Controlo do Gestor\n\nOpções:\n1:Criar novo utilizador de cliente\n2:Gerir Stocks\n3:Ver Estatísticas\n4:Logout\n\nIntroduza a sua opção:");
					x = getchar(); 
					switch (x)
						{
							case '1': {newuser();break;}
							case '2': {stocksmenu();break;}
							case '3': {statsmenu();break;}
							case '4': {return;}
						}
					system("clear");
				}
			return;
	}

	/*>>>> O procedimento stocksmenu imprime as opções de escolha do menu de stocks e permite invocar as funções para adicionar, editar ou remover um produto.*/
	
	void stocksmenu() 
		{
			//Declarações de dados
			char x = '0';
			
			//Instruções
			getchar(); //Absorve um suposto \n que vem do menu anterior.
			while (1)
				{
					system("clear");
					printf("Gerir Stocks:\n1:Introduir novo produto\n2:Alterar atributos de um produto\n3:Eliminar um produto\n4:Voltar\n\nIntroduza a sua opção:");
					x = getchar();
					switch (x)
						{
							case '1': {insertproduct();break;} 
							case '2': {editproduct(true);break;}
							case '3': {editproduct(false);break;}
							case '4': {return;}
						}
				}
			return;
		}


 	/*>>> Menu para selecionar qual elemento editar*/
	void editmenu(int linha)
		{
			//Declaração de dados
			char x = '0';
			char* str = (char*) malloc(sizeof(char)*MAXLINE);
			//Instruções
			while (1)
				{
					system("clear");
					printproduct(linha);
					printf("\nOpções de edição:\n\n1:Editar Quantidade\n2:Editar Preco de Custo\n3:Editar Preco de Venda\n4:Voltar\n\nInsira a opção:");
					x = getchar();
					switch (x)
						{
							case '1':{	
										system("clear");
										getchar();
										printf("Insira a nova quantidade:");
										fgets(str,MAXLINE,stdin);
										if (atof(str) == 0.0)
											{
												printf("Inseriu algo invalido. O preco de custo e na forma xx.yy . Volte a tentar.");
												getchar();
											}
										else 
											{
												editvalueproducts(1,linha,atof(str));
											}
									break;
									}									
							case '2':{
										system("clear");
										getchar();
										printf("Insira o novo preco de custo:");
										fgets(str,MAXLINE,stdin);
										if (atof(str) == 0.0)
											{
												printf("Inseriu algo invalido. O preco de custo e na forma xx.yy . Volte a tentar.");
												getchar();
											}
										else 
											{
												editvalueproducts(2,linha,atof(str));
											}
										break;
									 }
							case '3':{
										system("clear");
										getchar();
										printf("Insira o novo preco de venda:");
										fflush(stdin);
										fgets(str,MAXLINE,stdin);
										if (atof(str) == 0.0)
											{
												printf("Inseriu algo inválido. O preco de custo é na forma xx.yy . Volte a tentar.");
												getchar();
											}
										else 
											{
												editvalueproducts(3,linha,atof(str));
											}
										break;
									 }
							case '4':{
										getchar();
										free(str);
										return;
									 }
						}
				}
			return;
		}

	/*>>> Menu para selecionar se deseja apagar o produto*/
	void removemenu(int linha)
		{
			//Declaração de dados
			char x = '0';

			//Instruções
			printproduct(linha);
			printf("\nTem a certeza que deseja apagar o seguinte produto? (S->Enter para confirmar ou qualquer outra tecla para cancelar)");
			x = getchar();
			getchar();
			switch (x)
				{
					case 'S':{removeproducts(linha);break;}
					case 's':{removeproducts(linha);break;}
					default :{return;}
				}
			return;
		}

	/*>>> Menu para selecionar qual estatistica editar*/
	void statsmenu()
		{
			//Declarações de dados
			char x = '0';

			//Instruções
			getchar();
			while (1)
				{
					prodstat db[MAXLINE] = {{"",0.00,0.00,0.00}};
					prodstat *ptstat = db;
					userstat dbu[MAXLINE] = {{"","","",0.00}};
					userstat *ptustat = dbu;
					listproducts(ptstat);
					listusers(ptustat);
					if (strcmp(db[0].name,"") == 0)
						{
							printf("Não existem ainda compras efectuadas. Irá voltar ao menu anterior\nPrima ENTER para continuar...");
							getchar();
							return;
						}
					system("clear");
					printf("Estatísticas\n1.Quantidades e preco de venda total\n2.Quantidades vendidas por produto\n3.Lucro por Produto\n4.Compras por cliente\n5.Voltar\n\nIntroduza a sua opção:");
					x = getchar();
					switch (x)
						{
							case '1': {listprdctsstats(ptstat,true);break;} 
							case '2': {askproduct(true,ptstat);break;}
							case '3': {askproduct(false,ptstat);break;}
							case '4': {shoppinglistbyclient(ptustat);break;}
							case '5': {return;}
						}
				}
			return;
		}
