#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VEL 11
#define MAX_DAT 1024

struct cvorStabla;
typedef struct cvorStabla *Stablo;
struct Stog;
typedef struct Stog *Pozicija;

struct cvorStabla
{
	char El[VEL];
	Stablo Left;
	Stablo Right;
};

struct Stog
{
	Stablo El;
	Pozicija Next;
};

Stablo Citanje_Postfixa(char*, Stablo);
Stablo Stvori_Stablo(char*);
int Push(Stablo, Pozicija);
Pozicija Stvori_Stog(Stablo);
Stablo Pop(Pozicija);
int Upis_Infixa(char*, Stablo);

int main()
{
	Stablo root = NULL;
	char dat[MAX_DAT] = { 0 };

	printf("Unesite ime datoteke iz koje zelite ucitati postfix izraz:\t");
	scanf(" %s", dat);

	root = Citanje_Postfixa(dat, root);

	if (!root)
		return NULL;

	printf("Unesite ime datoteke u koju zelite upisati infix izraz:\t\t");
	scanf(" %s", dat);

	Upis_Infixa(dat, root);

	return 0;
}

Stablo Citanje_Postfixa(char* dat, Stablo S)
{
	FILE *fp = NULL;
	char buffer[VEL] = { 0 };
	struct Stog head;
	Stablo rezultat = NULL;

	head.Next = NULL;

	fp = fopen(dat, "r");

	if (!fp)
	{
		printf("Datoteka ne postoji!\r\n");
		return NULL;
	}

	while (!feof(fp))
	{
		Stablo cvor = NULL;

		fscanf(fp, " %s", buffer);
		cvor = Stvori_Stablo(buffer);

		if (!cvor)
		{
			fclose(fp);
			return NULL;
		}

		if (atoi(cvor->El))
			Push(cvor, &head);
		else
		{
			cvor->Right = Pop(&head);

			if (!cvor->Right)
			{
				printf("Postfix izraz nije tocan!\r\n");
				return NULL;
			}

			cvor->Left = Pop(&head);

			if (!cvor->Left)
			{
				printf("Postfix izraz nije tocan!\r\n");
				return NULL;
			}

			Push(cvor, &head);
		}

	}

	rezultat = Pop(&head);

	if (!rezultat)
	{
		printf("Datoteka je prazna!\r\n");
		return NULL;
	}

	return rezultat;
}

Stablo Stvori_Stablo(char* buffer)
{
	Stablo S = NULL;

	S = (Stablo)malloc(sizeof(struct cvorStabla));

	if (!S)
	{
		printf("Alokacija stabla nije uspjela!\r\n");
		return NULL;
	}

	strcpy(S->El, buffer);
	S->Left = NULL;
	S->Right = NULL;

	//return S;
}

int Push(Stablo S, Pozicija P)
{
	Pozicija Q = NULL;

	Q = Stvori_Stog(S);

	if (!Q)
		return -1;

	Q->Next = P->Next;
	P->Next = Q;

	return 0;
}

Pozicija Stvori_Stog(Stablo S)
{
	Pozicija P = NULL;

	P = (Pozicija)malloc(sizeof(struct Stog));

	if (!P)
	{
		printf("Alokacija stabla nije uspjela!\r\n");
		return NULL;
	}

	P->El = S;
	P->Next = NULL;

	return P;
}

Stablo Pop(Pozicija P)
{
	Pozicija temp = NULL;
	Stablo rezultat = NULL;

	if (P->Next == NULL)
		return NULL;

	temp = P->Next;
	rezultat = temp->El;
	P->Next = temp->Next;
	free(temp);

	return rezultat;
}

int Upis_Infixa(char* dat, Stablo S)
{
	FILE *fp = NULL;

	fp = fopen(dat, "a");

	if (!fp)
	{
		printf("Greska pri otvaranju datoteke!\r\n");
		return NULL;
	}

	if (S->Left != NULL)
	{
		fprintf(fp, "(");
		fclose(fp);

		Upis_Infixa(dat, S->Left);

		fp = fopen(dat, "a");
		fprintf(fp, " %s ", S->El);
		fclose(fp);

		Upis_Infixa(dat, S->Right);

		fp = fopen(dat, "a");
		fprintf(fp, ")");

	}
	else
		fprintf(fp, "%s", S->El);


	fclose(fp);

	return 0;
}

