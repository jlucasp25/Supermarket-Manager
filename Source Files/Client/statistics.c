#include "client.h"

/*****************************************************************************************************************************
 *  Comentários globais:                                                                                                      *
 *  Foi criada uma struct para acomodar as estatisticas do cliente, como visto noutros ficheiros.                             *
 *****************************************************************************************************************************/
	
/*>>>> Esta função prepara a struct que contém as estatisticas, inicializando-a com as informações do ficheiro. */
void preparestatsdb(char* userx,prodstat* ptstat,FILE* filep) 
{
  //Declaração de dados
  FILE* filex = openfile("shoppinglist_db");
			
  char* str = (char*) malloc(sizeof(char)*MAXLINE);
  char* str2 = (char*) malloc(sizeof(char)*MAXLINE);
			
  int i = 0,j=0,conta=0;
  int index = 0;
  float qtd,prcf;

  //Instruções
  while (fgets(str,MAXLINE,filex) != NULL)
    {
      str[strlen(str)-1] = '\0';
      if (strcmp(str+5,userx) == 0)
	{
	  while (1)
	    {
	      fgets(str,MAXLINE,filex);
	      if ( (*(str+0)=='t' && *(str+1)=='o' && *(str+2)=='t') || strcmp(str,"%\n") == 0)
		{
		  break;
		} 
	      sscanf(str,"%[^#]#%f#%f",str2,&qtd,&prcf);
	      index = getindex(str2,filep);
	      strcpy((*(ptstat+index-1)).name,str2);
	      (*(ptstat+index-1)).qtd+=qtd;
	      (*(ptstat+index-1)).prcf+=prcf;	
	    }
	}
    }		
			
  //Instruções de finalização
  free(str);
  free(str2);
  closefile(filex);
}

/*>>>>Esta função retorna o índice do ficheiro que se está a incializar*/
int getindex(char* strp,FILE* filep)
{
  //Declarações de dados
  char* str = (char*) malloc(sizeof(char)*MAXLINE);
  char* name = (char*) malloc(sizeof(char)*MAXSTR);
  int linha = 1;

  //Instruções
  rewind(filep);
  while (fgets(str,MAXLINE,filep) != NULL)
    {
      sscanf(str,"%[^#]#",name);
      if (strcmp(name,strp) == 0)
	{
	  free(str);free(name);return linha;
	}
      linha++;
    }

  //Instruções de excepção
  free(str);free(name); return -1;
}

/*>>>> Esta função lista os produtos mostrando as caracteristicas dependendo da situação*/
void listprdctsstats(FILE* filex, bool listqtd,prodstat* ptstat)
{
  //Instruções
  if (listqtd == false)
    {
      char* linha = (char*) malloc(sizeof(char) * MAXLINE);
      char* name = (char*) malloc(sizeof(char) * MAXLINE);
      int i=1;
      rewind(filex);
      printf("+----------------------------------------------------------------------------------+\n");
      printf("|Código     | Descrição                                                            |\n");
      while (fgets(linha,MAXLINE,filex) != NULL)
	{
	  sscanf(linha,"%[^#]#",name);
	  printf("|%11d|%70s|\n",i,name);
	  i++;
	} 
      printf("+----------------------------------------------------------------------------------+\n\n");
      free(linha);free(name);
      return;
    }
  else
    {
      int i=0;
      rewind(filex);
      printf("+----------------------------------------------------------------------------------+\n");
      printf("|Código     | Descrição                      |Quantidade comprada | Dinheiro gasto |\n");
      while (strcmp((*(ptstat+i)).name,"")!=0) 
	{								
	  if ((*(ptstat+i)).prcf != 0.00)
      {         
         printf("|%11d|%32s|%20.2f|%16.2f|\n",(i+1),(*(ptstat+i)).name,(*(ptstat+i)).qtd,(*(ptstat+i)).prcf);
         i++;
      }
    else
      i++;
	}
      printf("+----------------------------------------------------------------------------------+\n\n");
      return;}
}

void totalproducts(FILE* filep,prodstat* ptstat) 
{
  //Declarações de dados
	int i = 0;
	float prcftotal = 0.00;
	float qtdtotal = 0.00;

  //Instruções
	system("clear");
  getchar();
	listprdctsstats(filep,true,ptstat);
	while ((*(ptstat+i)).prcf > 0.00)
		{
			prcftotal += (*(ptstat+i)).prcf;
			qtdtotal += (*(ptstat+i)).qtd;
			i++;
		}
	rewind(filep);
	printf("A quantidade total e o gasto total em produtos, foi respectivamente: %.2f e %.2f\nPrima ENTER para continuar...",qtdtotal,prcftotal);
	getchar();
}

/*Esta função conta quantos produtos estão no ficheiro de produtos*/
int countproducts(FILE* filep) 
{
  //Declarações de dados
  char* str = (char*) malloc(sizeof(char)*MAXLINE);
  int productcount = 0;

	//Instruções			
  rewind(filep);
  while (fgets(str,MAXLINE,filep) != NULL)
    productcount++;
  rewind(filep);
  free(str);	
  return productcount;
}

