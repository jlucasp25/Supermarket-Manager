#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100
#define MAXSTR 50


	typedef enum {
		false,
		true
	} bool;

	typedef struct prodstat {
	char name[50];
	float qtd;
	float prcf;
	float prcc; } prodstat; /*preco de custo*/

	typedef struct userstat {
	char name[50];
	char contact[50];
	char uname[50];
	float saldo;
	} userstat;

//Prótotipos das funções
void newuser();
bool verifyuserpass(char* userx, char* passwx,bool usronly);
bool verifyspecialchars(char* str);
bool verifysize(char* str, int min, int max);
FILE* openfile(char* filex);
FILE* openfile_append(char* filex);
void closefile(FILE* closex);
void editvalueproducts(int field,int linha,float value);
void removeproducts(int linha);
void editproduct(bool edit);
void listproduct();
void printproduct(int linha);
void insertproduct();
int main();
void menuinit();
void stocksmenu();
void editmenu(int linha);
void removemenu(int linha);
void statsmenu();
void listproducts(prodstat* ptstat);
void updateprdctcost(prodstat* ptstat);
void listusers(userstat* ptustat);
int listofclients(userstat* ptustat);
void shoppinglistbyclient(userstat* ptustat);
void listprdctsstats(prodstat* ptstat,bool allinfo);
int searchcode(char* name);
void askproduct(bool isqtd,prodstat* ptstat);