#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIR_NAME_LENGHT 1028

typedef struct dir;
typedef struct dir* Stablo;
typedef struct stack;
typedef struct stack* Position;

struct dir
{
	char *name;
	Stablo next;
	Stablo child;
};

struct stack
{
	Stablo pokStablo;
	Position following;
}; 

Position StvoriStog();
int Odabir(Stablo, Position);
char* odrediPolozaj(Position);
int Ispis(Position);
int Direktorij(Stablo, char *);
Stablo Pop(Position);
int Push(Position, Stablo);
Stablo cd(Stablo, Position, char*);
int Delete(Stablo);

int main()
{
	Stablo Korijen;
	Position Pocetak;
	Stablo Trenutno;

	Korijen = (Stablo)malloc(sizeof(struct dir));
	Pocetak = StvoriStog();

	Korijen->next = NULL;
	Korijen->child = NULL;
	Korijen->name = NULL;

	Trenutno = Korijen;

	Pocetak->pokStablo = Korijen;
	Pocetak->following = NULL;

	printf("Moguce naredbe:\n1 - \"md - make directory\"\n2 - \"cd dir - change directory\"\n3 - \"cd.. - return to previous directory\"\n4 - \"dir - list directory\"\n5 - \"exit\"\n");
	Odabir(Trenutno, Pocetak);

	system("pause");

	return 0;
}

Position StvoriStog()
{
	Position Element;
	Stablo novoStablo;

	Element = (Position)malloc(sizeof(struct stack));
	novoStablo = (Stablo)malloc(sizeof(struct dir));

	novoStablo->next = NULL;
	novoStablo->child = NULL;

	if (Element == NULL || novoStablo == NULL)
	{
		printf("Greska u alokaciji memorije!\r\n");
		return -1;
	}
	else
	{
		Element->pokStablo = novoStablo;
		Element->following = NULL;

		return Element;
	}
}

int Odabir(Stablo S, Position P)
{
	char *c;
	int i = 1, el = 0;
	char naredba[5], naziv[DIR_NAME_LENGHT], pol[DIR_NAME_LENGHT];

	c = (char *)malloc(DIR_NAME_LENGHT * sizeof(char));

	printf("\n\n");


	if (!c)
	{
		printf("Greska u alokaciji memorije!\r\n");
		return -1;
	}

	while (i != 0)
	{

		c = odrediPolozaj(P);
		strcpy(pol, c);

		printf("%s>", pol);
		scanf("%s", naredba);

		if (strcmp(naredba, "dir") == 0)
			i = Ispis(S);
		else if (strcmp(naredba, "exit") == 0)
		{
			Delete(S);

			return 0;
		}
		else if (strcmp(naredba, "md") != 0 && strcmp(naredba, "cd") != 0)
			i = 3;
		else 
			scanf("%s", naziv);
		


		if (strcmp(naredba, "md") == 0)
			i = Direktorij(S, naziv);
		else if (strcmp(naredba, "cd") == 0) 
		{
			if (strcmp(naziv, "..") == 0) 
				S = Pop(P);
			else 
				S = cd(S, P, naziv);
			
			i = 1;

		}

		if (i == 3) 
			printf("Nepoznata naredba!\r\n");
		

		printf("\n");
	}

	return 0;
}

char* odrediPolozaj(Position P)
{
	char a[DIR_NAME_LENGHT];
	strcpy(a, "C:\\User");

	while (P->following != NULL)
	{
		strcat(a, "\\");
		strcat(a, P->pokStablo->child->name);

		P = P->following;

	}

	return a;
}

int Ispis(Stablo S)
{
	int i = 0;
	Stablo x;

	x = S->child;

	printf("\n");

	while (x != NULL)
	{
		printf("\t\t%s\n", x->name);

		x = x->next;

		i++;
	}

	printf("\t\t\t\t%d DIR(s)\n", i);

	return 1;
}

int Direktorij(Stablo S, char *naziv)
{
	Stablo Novi;
	Stablo Dijete;

	Novi = (Stablo)malloc(sizeof(struct dir));

	Novi->next = NULL;
	Novi->child = NULL;

	Dijete = S->child;

	Novi->name = (char *)malloc(strlen(naziv) + 1);

	strcpy(Novi->name, naziv);


	if (S->child == NULL)
		S->child = Novi;
	else
	{
		Novi->next = Dijete;
		S->child = Novi;

	}

	return 1; 
}

Stablo Pop(Position P)
{
	Position Q;

	Q = P->following;

	if (Q->following != NULL) 
		P->following = Q->following;
	
	return Q->pokStablo;
}

Stablo cd(Stablo S, Position P, char* a)
{
	Stablo Direktorij = S->child;

	while (Direktorij != NULL && strcmp(Direktorij->name, a) != 0)
		Direktorij = Direktorij->next;
	
	if (Direktorij == NULL)
	{
		printf("Greska!\n");

		return S;
	}

	Push(P, S);

	return Direktorij;
}

int Push(Position P, Stablo S)
{
	Position dir;

	dir = StvoriStog();

	dir->pokStablo = S;
	dir->following = P->following;
	P->following = dir;

	return 0;
}

int Delete(Stablo S)
{
	if (S == NULL)
		return;

	Delete(S->next);
	Delete(S->child);

	free(S);
}

