#include <math.h>
#include "client.h"
#include <unistd.h>
#include <sys/types.h>



/******************************************************************************************************************************
 *  Comentários globais:                                                                                                       *
 *  Todas as funções e procedimentos invocados a partir deste momento irão ter como argumento o nome de utilizador do cliente  *
 *  que está a utilizar o programa, de forma a identificá-lo.                                                                  *
 *  Em alguns casos ao longo do programa, é comparado se o retorno de atoi ou atof são iguais a 0 ou 0.00 respectivamente      *
 *  pois se o que for introduzido não for um número inteiro ou decimal válido, atoi e atof retornam esses valores.             * 
 *  Além de mais, nos casos em que se utilizou esse método de verificação, tanto 0 como 0.00 não são valores aceitáveis nesses *
 *  campos.                                                                                                                    *
 *  As funções de editar ficheiros seguem o mesmo raciocinio logo apenas será comentada uma.                                   *
 *******************************************************************************************************************************/
	
/*>>>>A função startshopping cria uma ligação durante o processo de compra.*/
	
/******************************************************************************************************************************
 *  Esta função inicializa variáveis e apontadores que permitem receber variados valores importantes.                          *
 *  De seguida, invoca as funções checkbalance e prepareshoppinglist, para receber o saldo atual e inicializar no ficheiro que *
 *  guarda a informação a instância da lista de compras. Ao longo do programa são invocadas varias funções que efectuam        *
 *  verificações. Se o produto introduzido for aceite, no final é atualizado o stock, o saldo e é adicionado à lista de compras*
 *  Usando a opção L, é possivel ver a lista em qualquer momento, e a opção '-1' é usada para invocar a função de finalização  * 
 *  encerrando assim a instância da lista de compras, e mostrando o total.                                                     *
 *******************************************************************************************************************************/
	

void startshopping(char* userx)
{
  //Declaração de dados
  FILE* filep = openfile("product_db");
  FILE* filesl = openfile_append("shoppinglist_db");
  FILE* fileu = openfile("user_db");
			
  char* productstr = (char*) malloc(sizeof(char)*MAXLINE);
  char* productcode = (char*) malloc(sizeof(char)*MAXSTR);
  char* productname = (char*) malloc(sizeof(char)*MAXSTR);
			
  int numberofproducts = 0;
  float initialbalance = 0.00; 
  float requestedqtty = 0.00; 
  float finalbalance = 0.00; 
  float finalstock = 0.00;
  float pricecost = 0.00; 
  float total = 0.00;		
  float availableqtty = 0.00;
  float pricesale = 0.00;
  float pricefinal = 0.00;
  float* ptpricefinal = &pricefinal;
  float* ptfinalstock = &finalstock;
  float* ptfinalbalance = &finalbalance;		
			
  //Instruções
  if (filep == NULL || filesl == NULL || fileu == NULL)
        {
          free(productstr);free(productcode);free(productname);
          printf("ERRO! Use o shell script para criar os ficheiros de db na primeira vez que iniciar o programa.\nPrima ENTER para continuar...");
          getchar();
          return;
        }			
  initialbalance = extractbalance(userx);
  prepareshoppinglist(userx,filesl);			
  while (1)
    {
      getchar();
      system("clear");
					
      numberofproducts = listproduct(filep);
      if (numberofproducts == 1)
      {
      	system("clear");
      	printf("Não existem ainda produtos para se efectuar uma compra! Volte mais tarde.\nPrima ENTER para continuar.");
      	getchar();
      	finishshopping(filesl,total);
	  	closefile(filesl);closefile(filep);closefile(fileu);free(productstr);free(productcode);free(productname);
      	return;
      }
					
      printf("Insira o código do produto que deseja adicionar à lista, 'L'. Para visualizar a sua lista atual prima 'l' ou -1 para terminar a compra:");
      fgets(productcode,MAXSTR,stdin);
					
      if ( (*productcode) == '-' && *(productcode+1) == '1' )
	{
	  finishshopping(filesl,total);
	  closefile(filesl);closefile(filep);closefile(fileu);free(productstr);free(productcode);free(productname);
	  printf("A sua compra foi fechada. O total é: %.2f\nPrima ENTER para continuar...",total);
	  getchar();
	  return;
	}
      else if ((*productcode) == 'L' || (*productcode) == 'l')
	{
	  closefile(filesl);
	  listshoppinglist();
	  filesl = openfile_append("shoppinglist_db");
	  printf("Prima ENTER para continuar...");
	  getchar();
	  rewind(filep);
	}
      else if ( pickproduct(filep,atoi(productcode),productstr,numberofproducts) == true )
	{
												
	  sscanf(productstr,"%[^#]#%f#%f#%f",productname,&availableqtty,&pricecost,&pricesale);
	  printf("Insira a quantidade a adquirir:");
	  scanf("%f",&requestedqtty);
									
	  if (checkquantity(requestedqtty,availableqtty,ptfinalstock) == false)
	    {
	      printf("A quantidade que escolheu não está disponível.");
	      getchar();
	      getchar();
	      rewind(filep);
											
	    }
	  else if (checkbalance(pricesale,initialbalance,ptfinalbalance,requestedqtty,ptpricefinal) == false)
	    {
	      printf("Não tem saldo suficiente para efetuar a compra selecionada.");
	      getchar();
	      getchar();
	      rewind(filep);										
	    }
	  else	
	    {
	      addtolist(filesl,productname,ptpricefinal,requestedqtty);
	      updatestocks(filep,ptfinalstock,productcode,productname,pricecost,pricesale);
	      updatebalance(fileu,ptfinalbalance,userx);
        initialbalance=(*ptfinalbalance);
	      total+=(*ptpricefinal);
	      rewind(filep);
	      printf("O produto foi adicionado com sucesso!\n Prima ENTER para continuar...");
	      								
	    }
								
	}
      else
	{
	  printf("O codigo que inseriu e invalido.\n Prima Enter para continuar...");
	  getchar();
	}
    }
}

/*>>>>A função updatestocks atualiza o stock do produto depois da sua compra no ficheiro.*/
	
/******************************************************************************************************************************
 *  Esta função é utilizada para atualizar o stock do produto comprado no ficheiro de produtos. Em termos de algoritmo e ins-  *
 *  truções, este segue um padrão igual a outras funções de edição de ficheiros.                                               *
 *  Determina o tamanho total do ficheiro em bytes, e determina o tamanho do ficheiro até à linha a alterar, de seguida é      *
 *  criado um buffer para acomodar o resto do ficheiro a seguir à linha a editar, e é copiada essa parte para esse buffer.     *
 *  Cria-se um descriptor de ficheiro e trunca-se o ficheiro na linha a editar. De seguida,escreve-se para o ficheiro a nova   * 
 *  linha editada e o buffer, atualizando assim o ficheiro.                                                                    *
 *******************************************************************************************************************************/
	
void updatestocks(FILE* filep,float* ptstckfinal,char* prdctcode,char* name,float precocusto,float precovenda)
{
  //Declaração de dados inicial
  char* str = (char*) malloc(sizeof(char)*MAXLINE);
  char* temp = (char*) malloc(sizeof(char)*MAXLINE);
			
  int i;
  int line = atoi(prdctcode);
  int offset = 0;
  int fxdescriptor = 0;
  long filesize = 0;
  long until = 0;
  long buffersize = 0;
			
  //Determina o tamanho total do ficheiro em bytes
  fseek(filep,0L,SEEK_END);  
  filesize = ftell(filep);
  rewind(filep);
			
  //Determina o tamanho em bytes do ficheiro até à linha a alterar.
  for (i = 0 ; i < line ; i++)
    {
      fgets(str,MAXLINE,filep);
      until+=strlen(str);
    }

  //O buffer será então (tamanho_do_ficheiro - tamanho_até_alterar) bytes
  buffersize = filesize - until;
  char* buffer = (char*) malloc(sizeof(char)*buffersize);
  *buffer = '\0';				
  //É concatenado tudo o que estiver a seguir no ficheiro para o buffer.
  while (fgets(str,MAXLINE,filep) != NULL)
    {
      strcat(buffer,str);
    }

  rewind(filep);
  for (i = 0 ; i < (line - 1) ; i++)
    {
      fgets(temp,MAXLINE,filep);
    }

  //É criado um descritor de ficheiro a partir da estrutura FILE*	
  fxdescriptor = fileno(filep);

  //O ficheiro é truncado
  ftruncate(fxdescriptor,until);

  //É impressa a linha com as informações atualizadas e em seguida o buffer
  fprintf(filep,"%s#%.2f#%.2f#%.2f\n",name,(*ptstckfinal),precocusto,precovenda);
  getchar();
  fputs(buffer,filep);

  //Instruções de finalização
  free(str);
  free(temp);
  free(buffer);
  return;
}

/*A função updatebalance atualiza o saldo do cliente de acordo com o gasto no produto.*/
void updatebalance(FILE* fileu,float* ptsldfinal,char* userx)
{
  //Declaração de dados iniciais
  char* str = (char*) malloc(sizeof(char)*MAXLINE);
  char* name = (char*) malloc(sizeof(char)*MAXSTR);
  char* contact = (char*) malloc(sizeof(char)*MAXSTR);
  char* uname = (char*) malloc(sizeof(char)*MAXSTR);
  char* passw = (char*) malloc(sizeof(char)*MAXSTR);
  char* temp = (char*) malloc(sizeof(char)*MAXSTR);

  float oldbalance = 0.00;
  int line = 1;
  int i = 0;
  int offset = 0;
  int fxdescriptor = 0;
  long filesize = 0;
  long until = 0;
  long buffersize = 0;
			
  //Instruções
  rewind(fileu);
			
  //Procura a linha do utilizador respectivo e recebe as suas informações
  while (fgets(str,MAXLINE,fileu) != NULL)
    {
      sscanf(str,"%[^#]#%[^#]#%[^#]#%[^#]#%f",name,contact,uname,passw,&oldbalance);
      if (strcmp(uname,userx) == 0)
	break;
      line++;
    }

  //Determina o tamanho total do ficheiro em bytes
  fseek(fileu,0L,SEEK_END);
  filesize = ftell(fileu);
  rewind(fileu);

  //Determina o tamanho em bytes do ficheiro até à linha a alterar.
  for (i = 0 ; i < line ; i++)
    {
      fgets(str,MAXLINE,fileu);
      until+=strlen(str);
    }

  //O buffer será então (tamanho_do_ficheiro - tamanho_até_alterar) bytes	
  buffersize = filesize - until;
  char* buffer = (char*) malloc(sizeof(char)*buffersize);
  buffer[0]='\0';

  //É concatenado tudo o que estiver a seguir no ficheiro para o buffer.
  while (fgets(str,MAXLINE,fileu) != NULL)
    {
      strcat(buffer,str);
    }
  rewind(fileu);	
  for (i = 0 ; i < (line - 1) ; i++)
    {
      fgets(temp,MAXSTR,fileu);
    }

  //Cria um descritor de ficheiro a partir da estrutura FILE*
  fxdescriptor = fileno(fileu);

  //Trunca o ficheiro no local desejado
  ftruncate(fxdescriptor,until);
			
  //Insere a linha com as informações necessárias e insere o buffer também
  fprintf(fileu,"%s#%s#%s#%s#%.2f\n",name,contact,uname,passw,*ptsldfinal);
  buffer[strlen(buffer)-1] = '\0';
  fputs(buffer,fileu);
			
  //Instruções de finalização
  free(str);
  free(name);
  free(contact);
  free(uname);
  free(passw);
  free(buffer);
  free(temp);
  return;
}

/*>>>>Inicia uma instância da lista de compras*/
void prepareshoppinglist(char* userx,FILE* filesl)
{
  //Instruções
  fprintf(filesl,"user %s\n",userx);
  return;
}

/*>>>>Esta função cria uma tabela com todos os produtos disponíveis e retorna o número de produtos.*/
int listproduct(FILE* filep)
{
  //Declarações de dados
  char* line = (char*) malloc(sizeof(char) * MAXLINE);
  char* name = (char*) malloc(sizeof(char) * MAXSTR);
  char* qtty = (char*) malloc(sizeof(char)* MAXSTR);
  char* price = (char*) malloc(sizeof(char)* MAXSTR);
  char* temp = (char*) malloc(sizeof(char)* MAXSTR);
  int i = 1;
			
  //Instruções
  //Imprime uma tabela recebendo cada linha do ficheiro e imprimindo-a formatada.
  printf("+----------------------------------------------------------------------------------+\n");
  printf("|Código     | Descrição                   | Quantidade | Preço                     |\n");
  while (fgets(line,MAXLINE,filep) != NULL)
    {
      sscanf(line,"%[^#]#%[^#]#%[^#]#%[^\n]",name,qtty,temp,price);
      printf("|%11d|%29s|%12s|%27s|\n",i,name,qtty,price);
      i++;
    } 
  printf("+----------------------------------------------------------------------------------+\n\n");

  //Instruções de finalizaão
  free(line);free(name);free(qtty);free(price);free(temp);
  return i;
}

/*>>>>Esta função recebe o código escolhido e vai ao ficheiro de produtos buscar a linha correspondente*/
	
bool pickproduct(FILE* filep, int code, char* productstr, int numberofproducts)
{	
  //Declaração de dados
  int i;

  //Instruções
  rewind(filep);
  //Se o código inserido estiver entre os códigos disponiveis, procura a linha do produto no ficheiros
  if (code >= 1 && code < numberofproducts)
    {
      for (i = 0; i < code; i++)
	fgets(productstr,MAXLINE,filep);
      return true;		
    }
  else
    return false;
}

/*>>>>Esta função recebe a quantidade pedida e verifica se existe quantidade suficiente. Guarda também, em caso afirmativo, o stock final do produto.*/
bool checkquantity(float qtdpedida,float qtd, float* ptstckfinal) 
{
  //Instruções
  if ( (qtd - qtdpedida) < 0.00)
    {
      return false;
    }
  else 
    {								
      *ptstckfinal = qtd - qtdpedida;
      return true;
    }
}

/*>>>>Esta função recebe o preço e a quantidade, calcula o valor a pagar pelo produto e compara com o saldo atual para verificar se é suficiente. Em caso afirmativo guarda o saldo final também.*/
	
bool checkbalance(float precovenda, float saldoinicial, float* ptsldfinal,float qtdpedida, float* preco)
{
  //Declaração de dados
  float temp = 0.00;

  //Instruções
  *preco = qtdpedida * precovenda;
  temp = saldoinicial - (*preco);
  if (temp < 0.00)
    {
      return false;
    }
  else 
    {
      (*ptsldfinal) = saldoinicial - (*preco);	
      return true;
    }
}	

/*>>>>Esta função adiciona à lista o produto comprado, a quantidade e o preço pago.*/
	
void addtolist(FILE* filesl,char* name,float* preco,float qtdpedida)
{
  //Instruções
  fprintf(filesl,"%s#%.2f#%.2f\n",name,qtdpedida,*preco);




  return;
}

/*>>>>Esta função lista os produtos comprados atualmente.*/
	
void listshoppinglist() 
{
  //Declaração de dados
  FILE* filesl = openfile("shoppinglist_db");
  char* str = (char*) malloc(sizeof(char)*MAXLINE);
  char* name = (char*) malloc(sizeof(char)*MAXSTR);
			
  int count1 = 0;
  int count2 = 0;
			
  float qtty = 0.00;
  float price = 0.00;
			
  //Instruções
			
  //No primeiro ciclo conta o número de listas de compras. No segundo pára antes de chegar à ultima (a que estamos a criar no momento).
  rewind(filesl);
  while (fgets(str,MAXLINE,filesl) != NULL)
    {
      if (strcmp(str,"%\n") == 0)
	{
	  count1++;
	}
    }
  rewind(filesl);
  while (fgets(str,MAXLINE,filesl) != NULL)
    {
      if (strcmp(str,"%\n") == 0)
	{
	  count2++;
	}
      if (count1 == count2)
	{
	  break;
	}
    }
  if (count1 > 0) // ou 1
    {fgets(str,MAXLINE,filesl);}

  //Imprime os dados que se encontram na lista de compras
  printf("++++++++++++++++++++++ Lista de Compras ++++++++++++++++++++++++\n");
  printf("|Nome                          | Quantidade | Preço final      |\n");
  while (fgets(str,MAXLINE,filesl) != NULL)
    {
      sscanf(str,"%[^#]#%f#%f",name,&qtty,&price);
      printf("|%30s|%12.2f|%18.2f|\n",name,qtty,price);
    }
  printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		
  //Instruções de finalização
  free(str);
  free(name);
  closefile(filesl);
  return;
}

/*>>>>Esta função escreve o total da lista de compras e finaliza a instância atual.*/
	
void finishshopping(FILE* filex,float total)
{ 	

  //Instruções
  fprintf(filex,"total %.2f\n%%\n",total);
  return;
}
