#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct CvorStabla;
typedef struct CvorStabla* Stablo;

struct CvorStabla
{
	int El;
	Stablo Lijevo;
	Stablo Desno;
};

Stablo Dodaj(Stablo, int);
void Ispis(Stablo);
Stablo Trazi(Stablo, int);
Stablo Brisi(Stablo, int);
Stablo Minimum(Stablo);

int main()
{
	Stablo Root = NULL;
	int odabir = 0;
	int broj, X;

	while (odabir != 5)
	{
		printf("\tOdaberite:\r\n1 - Unesi element\r\n2 - Trazi element\r\n3 - Brisi element\r\n4 - Ispis\r\n5 - Izlaz\r\n=> ");
		scanf(" %d", &odabir);

		switch (odabir)
		{
		case 1:

			printf("Unesite broj koji zelite dodati: ");
			scanf(" %d", &broj);
			Root = Dodaj(Root, broj);

			break;
		case 2:

			printf("Unesite broj koji zelite naci: ");
			scanf(" %d", &broj);
			X = Trazi(Root, broj);

			if (X != NULL)
				printf("Broj %d je pronaden.\r\n", broj);

			break;
		case 3:

			if (!Root)
				printf("Stablo je prazno!\r\n");
			else
			{
				printf("\nUnesite broj koji zelite izbrisati: ");
				scanf(" %d", &broj);
				Root = Brisi(Root, broj);
			}

			break;
		case 4:

			puts("----------------------------------------------------");
			Ispis(Root);
			puts("\n----------------------------------------------------");

			break;
		case 5:

			return 0;
			break;
		default:
			printf("Krivi unos!\r\n");
		}

		puts("");
	}

	return 0;
}

Stablo Dodaj(Stablo S, int x)
{
	if (S == NULL)
	{
		S = (Stablo)malloc(sizeof(struct CvorStabla));

		if (!S)
		{
			printf("Greska alokacije memorije!\r\n");
			return -1;
		}

		S->El = x;
		S->Desno = NULL;
		S->Lijevo = NULL;
	}
	else if (x < S->El)
	{
		S->Lijevo = Dodaj(S->Lijevo, x);

	}
	else if (x > S->El)
		S->Desno = Dodaj(S->Desno, x);
	else
		printf("Element vec postoji!\r\n");

	return S;
}

void Ispis(Stablo S)
{
	if (S != NULL)
	{
		Ispis(S->Lijevo);
		printf(" %d\t", S->El);
		Ispis(S->Desno);
	}
}

Stablo Trazi(Stablo S, int x)
{
	if (S == NULL)
	{
		printf("Element ne postoji!\r\n");
		return NULL;
	}

	if (x == S->El)
		return S;
	else if (x < S->El)
		Trazi(S->Lijevo, x);
	else
		Trazi(S->Desno, x);

}

Stablo Brisi(Stablo S, int x)
{
	Stablo pom = NULL;

	if (S == NULL)
	{
		printf("Element ne postoji!\r\n");
		return NULL;
	}
	if (x < S->El)
		S->Lijevo = Brisi(S->Lijevo, x);
	else if (x > S->El)
		S->Desno = Brisi(S->Desno, x);
	else if (S->Desno && S->Lijevo != NULL)
	{
		pom = Minimum(S->Desno);
		S->El = pom->El;
		S->Desno = Brisi(S->Desno, S->Desno);
	}
	else
	{
		pom = S;

		if (S->Lijevo == NULL)
			S = S->Desno;
		else
			S = S->Lijevo;

		free(pom);
	}

	return S;
}

Stablo Minimum(Stablo S)
{
	if (S != NULL)
	{
		while (S->Lijevo != NULL)
			S = S->Lijevo;
	}

	return S;
}


