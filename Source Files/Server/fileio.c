#include "server.h"
#include <unistd.h>
#include <sys/types.h>


FILE* openfile(char* filex) /*Função para abrir ficheiro em modo de leitura e escrita, aponta para o inicio*/
	{
		FILE *fptr;
		fptr = fopen(filex,"r+");
		return fptr;
	}


FILE* openfile_append(char* filex) /*Função para abrir ficheiro em modo de leitura e escrita e aponta para o fim*/
	{
		FILE *fptr;
		fptr = fopen(filex,"a+"); //alterar permissao
		return fptr;
	}

void closefile(FILE* closex) /*Função para fechar ficheiro (Não era necessária, mas foi criada por convenção do nome)*/
	{
		fclose(closex);
		return;
	}
 
/*>>>>> O procedimento editvalueproducts, edita o ficheiro permitindo mudar valores já existentes.*/
	void editvalueproducts(int field,int linha,float value) 
		{
			//Declarações de dados iniciais
			FILE* filex = openfile("product_db");
			char* str = (char*) malloc(sizeof(char)*MAXLINE);
			char* temp = (char*) malloc(sizeof(char)*MAXLINE);
			char* field1 = (char*) malloc(sizeof(char)*MAXLINE);
			char* field2 = (char*) malloc(sizeof(char)*MAXLINE);
			char* field3 = (char*) malloc(sizeof(char)*MAXLINE);
			int i = 0;
			int offset = 0;
			int fxdescriptor = 0;
			long filesize = 0;
			long until = 0;
			long buffersize = 0;

			//Instruções
			fseek(filex,0L,SEEK_END);
			filesize = ftell(filex);
			rewind(filex);
			for (i = 0 ; i < linha ; i++)
					{
						fgets(str,MAXLINE,filex);
						until+=strlen(str);
					}
			buffersize = filesize - until;
			char* buffer = (char*) malloc(sizeof(char)*buffersize);
			buffer[0] = '\0';
			while (fgets(str,MAXLINE,filex) != NULL)
				{
					strcat(buffer,str);
				}
			rewind(filex);
			for (i = 0 ; i < linha ; i++)
					{
						fgets(str,MAXLINE,filex);
					}
			rewind(filex);
			for (i = 0 ; i < (linha - 1) ; i++)
				{
					fgets(temp,MAXLINE,filex); //este ciclo serve para voltar uma linha atrás, truncando também a linha repetida :)
				}
			fxdescriptor = fileno(filex);
			ftruncate(fxdescriptor,until); /* o 2º argunmento de ftruncate é do tipo off_t, que é um alias para signed int, logo um int regular pode ser usado*/
			if (field == 1) //editar qtd
				{
						strcpy(temp,str+offset);
						strcpy(field1,strtok(temp,"#"));
						offset+=(strlen(temp)+1);
						strcpy(temp,str+offset);
						offset+=(strlen(strtok(temp,"#"))+1);
						strcpy(temp,str+offset);
						strcpy(field2,strtok(temp,"#"));
						offset+=(strlen(temp)+1);
						strcpy(temp,str+offset);
						strcpy(field3,strtok(temp,"#"));
						offset+=(strlen(temp)+1);
						field3[strlen(field3)-1] = '\0';
						fprintf(filex,"%s#%.2f#%s#%s\n",field1,value,field2,field3);
						buffer[strlen(buffer)-1] = '\0';
						fputs(buffer,filex);
				}
			else if (field == 2) //editar prc custo
				{
					strcpy(temp,str+offset);
					strcpy(field1,strtok(temp,"#"));
					offset+=(strlen(temp)+1);
					strcpy(temp,str+offset);
					strcpy(field2,strtok(temp,"#"));
					offset+=(strlen(temp)+1);
					strcpy(temp,str+offset);
					offset+=(strlen(strtok(temp,"#"))+1);
					strcpy(temp,str+offset);
					strcpy(field3,strtok(temp,"#"));
					offset+=(strlen(temp)+1);
					field3[strlen(field3)-1] = '\0';
					fprintf(filex,"%s#%s#%.2f#%s\n",field1,field2,value,field3);
					buffer[strlen(buffer)-1] = '\0';
					fputs(buffer,filex);
				}
			else //3 : editar prc venda
				{
					strcpy(temp,str+offset);
					strcpy(field1,strtok(temp,"#"));
					offset+=(strlen(temp)+1);
					strcpy(temp,str+offset);
					strcpy(field2,strtok(temp,"#"));
					offset+=(strlen(temp)+1);
					strcpy(temp,str+offset);
					strcpy(field3,strtok(temp,"#"));
					offset+=(strlen(temp)+1);
					strcpy(temp,str+offset);
					offset+=(strlen(strtok(temp,"#"))+1);
					fprintf(filex,"%s#%s#%s#%.2f\n",field1,field2,field3,value);
					buffer[strlen(buffer)-1] = '\0';
					fputs(buffer,filex);
				}	

			//Instruções de finalização
			fclose(filex);
			free(str);
			free(temp);
			free(field1);
			free(field2);
			free(field3);
			free(buffer);
		}

/*>>>>> O procedimento editvalueproducts, edita o ficheiro permitindo mudar valores já existentes.*/
	void removeproducts(int linha) 
		{
			//Declarações de dados iniciais
			FILE* filex = openfile("product_db");
			char* str = (char*) malloc(sizeof(char)*MAXLINE);
			char* temp = (char*) malloc(sizeof(char)*MAXLINE);
			int i = 0;
			int fxdescriptor = 0;
			long filesize = 0;
			long until = 0;
			long buffersize = 0;

			//Instruções
			fseek(filex,0L,SEEK_END);
			filesize = ftell(filex);
			rewind(filex);
			for (i = 0 ; i < linha ; i++)
					{
						fgets(str,MAXLINE,filex);
						until+=strlen(str);
					}
			buffersize = filesize - until;
			char* buffer = (char*) malloc(sizeof(char)*buffersize);
			buffer[0] = '\0';
			while (fgets(str,MAXLINE,filex) != NULL)
				{
					strcat(buffer,str);
				}
			rewind(filex);
			for (i = 0 ; i < linha ; i++)
					{
						fgets(str,MAXLINE,filex);
					}
			rewind(filex);
			for (i = 0 ; i < (linha - 1) ; i++)
				{
					fgets(temp,MAXLINE,filex); //este ciclo serve para voltar uma linha atrás, truncando também a linha repetida :)
				}
			fxdescriptor = fileno(filex);
			ftruncate(fxdescriptor,until); /* o 2º argunmento de ftruncate é do tipo off_t, que é um alias para signed int, logo um int regular pode ser usado*/
			fputs(buffer,filex);
			
			//Instruções de finalização
			fclose(filex);
			free(str);
			free(temp);
			free(buffer);
		}