#include "client.h"

/******************************************************************************************************************************
 *  Comentários globais:                                                                                                       *
 *  Todas as funções e procedimentos invocados a partir deste momento irão ter como argumento o nome de utilizador do cliente  *
 *  que está a utilizar o programa, de forma a identificá-lo.                                                                  *
 *  Em alguns casos ao longo do programa, é comparado se o retorno de atoi ou atof são iguais a 0 ou 0.00 respectivamente      *
 *  pois se o que for introduzido não for um número inteiro ou decimal válido, atoi e atof retornam esses valores.             * 
 *  Além de mais, nos casos em que se utilizou esse método de verificação, tanto 0 como 0.00 não são valores aceitáveis nesses *
 *  campos.                                                                                                                    *
 *******************************************************************************************************************************/
	
/*>>>>A função menuinit é o menu principal que efectua a ligação com os outros menus do programa.*/
	
void menuinit(char* userx)
{
  //Declaração de dados
  char x = '0';

  //Instruções
  while (1)
    {
      system("clear");
					
      printf("Bem vindo ao 'client'!\nO Painel de Controlo do Cliente\n\nOpções:\n1:Gerir Saldo\n2:Iniciar Compra\n3:Ver Estatísticas\n4:Logout\n\nIntroduza a sua opção:");	
      x = getchar(); 
      switch (x)                                         
	{
	case '1': {balancemenu(userx);break;}         /************************************************************/
	case '2': {startshopping(userx);break;}       /* A função é muito simples. Imprime as opções, recebe a    */
	case '3': {statsmenu(userx);break;}           /* opção do standard input e invoca a função correspondente.*/
	case '4': {return;}                           /* A opção 4 sai da função e volta para a main, que por não */
	}                                             /* ter mais instruções a seguir, encerra o programa.        */
    }                                           /************************************************************/
  return;
}

/*>>>>A função balancemenu é o menu que permite ver e adicionar dinheiro ao saldo do cliente.*/
	
void balancemenu(char* userx)
{
  //Declaração de dados
  char x = '0';

  //Instruções
  while (1)
    {
      system("clear");                                                                 
                                                                                            
      printf("O seu saldo atual é:%.2f€\n\nDeseja adicionar mais dinheiro ao seu saldo actual? (s/n->Enter)\n",extractbalance(userx));
      x = getchar();                                        
      switch (x)
	{                                                              
	case 'S': {addfunds(userx);break;} 
  case 's': {addfunds(userx);break;}                              /***************************************************/
  case 'n': {return;}                                             /* Esta função segue o raciocinio da anterior.     */
	case 'N': {return;}                                             /* No entanto, invoca a função checkbalance        */
	}                                                               /* para receber o saldo do utilizador e o mostrar. */
    }                                                             /* Usando a opção N, sai-se da função, e volta-se  */
  return;                                                         /* ao controlo da função anterior.                 */
}                                                                 /***************************************************/

/*>>>>A função statsmenu é o menu que permite selecionar qual opção de estatística o cliente deseja ver.*/
	
void statsmenu(char* userx)
{
  //Declaração de dados
  char x = '0';
  FILE* filep = openfile("product_db");

  //Instruções
  if (filep == NULL)
    {
      printf("ERRO! Crie os ficheiros db usando o shell script na primeira ocorrência do programa.\nPrima ENTER para continuar...");
      getchar();
      return;
    }
  while (1)
    {
      system("clear");


      int i = 0; 
      int maxsize = countproducts(filep);
      prodstat db[MAXPRODUCTS];
      rewind(filep);
      while (i < MAXPRODUCTS)
	{
	  db[i].name[0] = '\0';
	  db[i].qtd = 0.00;                                /**************************************************************************************************/                                                                                                       
	  db[i].prcf = 0.00;                               /* Esta parte inicial das instruções cria um vetor de structs para armazenar as estatisticas por  */
	  i++;
	}
	  prodstat* ptstat = db;                           /* produto, e a função preparestatsdb é invocada para inserir os dados no vetor.                  */
      preparestatsdb(userx,ptstat,filep);            /**************************************************************************************************/
			
      printf("Opções de Estatísticas:\n1.Quantidade total de produtos adquiridos\n2.Quantidade comprada de um determinado produto\n3.Valor total gasto num determinado produto\n4.Voltar\nInsira a opção:");			
      x = getchar();
      switch (x)
	{		
	case '1': {totalproducts(filep,ptstat);break;}
	case '2': {askproduct(true,ptstat,filep);break;}        /***********************************************************************************/
	case '3': {askproduct(false,ptstat,filep);break;}       /* Esta função segue o padrão de menus das funções anteriores. O caso 4 envolve a  */
	case '4': {closefile(filep);return;}                    /* saída da função, fechando o ficheiro aberto pois já não é necessário.           */
	}                                                       /***********************************************************************************/
    }
}

/*>>>>A função askproduct é um menu intermediário que permite que o cliente selecione o código correspondente à estatistica que deseja ver.*/
	
void askproduct(bool isqtd,prodstat* ptstat,FILE* filep)
{
  //Declaração de dados
  char* str = (char*) malloc(sizeof(char)*MAXSTR);
			
  //Instruções
  system("clear");
  getchar();
  listprdctsstats(filep,false,ptstat);
  if (isqtd == true)
    {
      printf("Insira o código do produto que deseja ver a quantidade comprada:");                /***********************************************************/
      fgets(str,MAXSTR,stdin);                                                                   /* Esta função invoca a função listprdctsstats para mostrar*/
      if (atoi(str) != 0) {
        if((*(ptstat+atoi(str)-1)).qtd!=0)
                                                                                                  /* a tabela com os códigos dos produtos disponiveis. De    */
	printf("Comprou %.2f de %s.\n",(*(ptstat+atoi(str)-1)).qtd,(*(ptstat+atoi(str)-1)).name);   
                                                                                               /* seguida pede ao cliente o código do produto que deseja  */
      else  
       printf("Não comprou nada desse produto.\n");  
       }
       else                                                                                    /* ver as estatísticas, verifica se é válido e imprime a   */
	{                                                                                              /* informação desejada.                                    */
	  printf("Inseriu um codigo invalido.Pressione ENTER para voltar...\n");                       /***********************************************************/ 
	  getchar();
	  return;
	}
    }                                                                                                                                                                
  else 
    {
      printf("Insira o código do produto que deseja ver o quanto gastou nele:");
      fgets(str,MAXSTR,stdin);
      if (atoi(str) != 0){
        if((*(ptstat+atoi(str)-1)).prcf != 0.00)
      
	printf("Gastou %.2f em %s.\n",(*(ptstat+atoi(str)-1)).prcf,(*(ptstat+atoi(str)-1)).name);
      else
        printf("Não gastou nada neste produto.\n");
    }
    else
	{
	  printf("Inseriu um codigo invalido. Pressione ENTER para voltar...\n");
	    getchar();
	  return;
	}
    }
  printf("\nPressione ENTER para continuar...");
  getchar();

  //Instruções de finalização
  free(str);
  return;
}
