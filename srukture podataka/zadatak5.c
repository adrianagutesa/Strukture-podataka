#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _lista;
typedef struct _lista *Position;

int Citanje(Position);
int Ispis(Position);
int Unija(Position, Position, Position);
int Presjek(Position, Position, Position);

typedef struct _lista
{
	int El;

	Position next;

}lista;

int main()
{
	lista L1, L2, U, P;

	L1.next = NULL;
	L2.next = NULL;
	U.next = NULL;
	P.next = NULL;

	Citanje(&L1);
	printf("\nSadrzaj prve liste:\r\n");
	Ispis(L1.next);

	puts("");
	Citanje(&L2);
	printf("\nSadrzaj druge liste:\r\n");
	Ispis(L2.next);

	printf("\nUnija:\r\n");
	Unija(L1.next, L2.next, &U);
	Ispis(U.next);

	printf("\nPresjek:\r\n");
	Presjek(L1.next, L2.next, &P);
	Ispis(P.next);

	system("pause");

	return 0;
}

int Citanje(Position p)
{
	FILE *fp = NULL;
	char dat[20];
	Position pom, q, prev;

	printf("Unesite ime datoteke iz koje zelite ucitati listu: ");
	scanf(" %s", dat);

	fp = fopen(dat, "r");

	if (fp == NULL)
	{
		printf("Datoteka ne postoji!\r\n");
		exit (1);
	}

	while (!feof(fp))
	{
		q = (Position)malloc(sizeof(lista));

		if (q == NULL)
		{
			printf("Greska pri alokaciji memorije!\r\n");
			return -2;
		}

		q->next = NULL;

		fscanf(fp, " %d", &q->El);

		prev = p;
		pom = p->next;

		while (pom != NULL && pom->El > q->El)
		{
			prev = pom;
			pom = pom->next;
		}
		q->next = pom;
		prev->next = q;
	}

	fclose(fp);

	return 1;
	
}

int Ispis(Position p)
{

	puts("------------------------------------------------------------");


	while (p != NULL)
	{
		printf("\t%d\r\n", p->El);
		p = p->next;
	}

	puts("------------------------------------------------------------");

	return 2;

}

int Unija(Position p1, Position p2, Position u)
{
	Position x, y;

	while (p1 != NULL && p2 != NULL)
	{
		x = (Position)malloc(sizeof(lista));

		if (x == NULL)
			return -1;

		u->next = x;
		x->next = NULL;

		if (p1->El < p2->El)
		{
			x->El = p2->El;
			p2 = p2->next;
		}
		else if (p1->El > p2->El)
		{
			x->El = p1->El;
			p1 = p1->next;
		}
		else
		{
			x->El = p1->El;
			p1 = p1->next;
			p2 = p2->next;

		}

		u = u->next;

		x->next = u->next;
		u->next = x;
		u = x;
	}

	if (p1)
		y = p1;
	else
		y = p2;

	while (y)
	{
		x = (Position)malloc(sizeof(lista));

		u->next = x;
		x->next = NULL;
		x->El = y->El;

		u = u->next;
		y = y->next;
	}

	return 4;

}

int Presjek(Position p1, Position p2, Position p)
{
	Position x = NULL;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->El < p2->El)
			p2 = p2->next;
		else if (p1->El > p2->El)
			p1 = p1->next;
		else
		{
			x = (Position)malloc(sizeof(lista));

			if (x == NULL)
				return x;

			x->next = NULL;

			if (x == NULL)
				return -1;

			x->El = p1->El;

			x->next = p->next;
			p->next = x;
			p = x;
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	return 5;
}