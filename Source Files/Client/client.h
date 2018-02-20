/*Ficheiro de cabeçalhos/Header Files - Programa Client*/
/*Este ficheiro inclui os protótipos e as estruturas de dados criadas para o programa client.*/
/*Projecto de LABC - João Lucas Pires e Solange Perdigão - 201606617 e 201603610*/

#include <stdio.h>		
#include <stdlib.h>		
#include <string.h>	
#define MAXLINE 100
#define MAXSTR 50
#define MAXPRODUCTS 500

//Estruturas de Dados 

typedef enum {
	false,
	true
	} bool;

typedef struct prodstat {
	char name[50];
	float qtd;
	float prcf;
} prodstat;

//Prótotipos das funções

int main();
void menuinit(char* userx);
void balancemenu(char* userx);
void statsmenu(char* userx);
void askproduct(bool isqtd,prodstat* ptstat,FILE* filep);
void preparestatsdb(char* userx,prodstat* ptstat,FILE* filep);
int getindex(char* strp,FILE* filep);
void listprdctsstats(FILE* filex, bool listqtd,prodstat* ptstat);
int countproducts(FILE* filep);
FILE* openfile(char* filex);
FILE* openfile_append(char* filex);
void closefile(FILE* closex) ;
void startshopping(char* userx);
void updatestocks(FILE* filep,float* ptstckfinal,char* prdctcode,char* name,float precocusto,float precovenda);
void updatebalance(FILE* fileu,float* ptsldfinal,char* userx);
void prepareshoppinglist(char* userx,FILE* filesl);
int listproduct(FILE* filep);
bool pickproduct(FILE* filep, int code, char* productstr, int numberofproducts);
bool checkquantity(float qtdpedida,float qtd, float* ptstckfinal);
bool checkbalance(float precovenda, float saldoinicial, float* ptsldfinal,float qtdpedida, float* preco);
void addtolist(FILE* filesl,char* name,float* preco,float qtdpedida);
void listshoppinglist();	
void finishshopping(FILE* filex,float total);
bool verifyuserpass(char* userx, char* passwx,bool usronly);
void addfunds(char* userx);
float extractbalance(char* userx);
void totalproducts(FILE* filep,prodstat* ptstat);