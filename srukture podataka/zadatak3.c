#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 256

struct _osoba;
typedef struct _osoba* Position;

typedef struct _osoba
{
	char ime[MAX];
	char prezime[MAX];
	int godina;

	Position next;

}osoba;

Position noviStudent(char *, char *, int);
void Ispis(Position);
void unosPocetak(Position, Position);
void unosKraj(Position, Position);
Position Trazi(Position, char *);
Position TraziPret(Position, char *);
void Brisi(Position, char *);
void Sortiraj(Position);
void Citaj(Position);
void Upisi(Position);

int main()
{
	osoba head;
	Position n, p;
	char ime[MAX], prez[MAX], pronaci[MAX];
	int god;
	char a;
	head.next = NULL;

	while (1)
	{
		printf("\nOdaberite:\r\nP = novi element na pocetak liste\r\nK = novi element na kraj liste\r\nN = pronalazak elementa u listi\r\nB = brisanje elementa u listi\r\n");
		printf("I = dodavanje elementa iza odredenog elementa\r\nD = dodavanje elementa ispred odredenog elementa\r\nS = sortiraj listu\r\nC = citanje datoteke\r\nU = unos u datoteku\r\nE = kraj\r\n");
		scanf(" %c", &a);

		a = toupper(a);

		switch (a)
		{
		case 'P':
			printf("\nUnesite ime:\t\t");
			scanf(" %s", ime);
			printf("Unesite prezime:\t");
			scanf(" %s", prez);
			printf("Unesite godinu rodenja:\t");
			scanf(" %d", &god);
			puts("");

			n = noviStudent(ime, prez, god);
			unosPocetak(&head, n);
			Ispis(head.next);

			break;
		case 'K':
			printf("\nUnesite ime:\t\t");
			scanf(" %s", ime);
			printf("Unesite prezime:\t");
			scanf(" %s", prez);
			printf("Unesite godinu rodenja:\t");
			scanf(" %d", &god);
			puts("");

			n = noviStudent(ime, prez, god);
			unosKraj(&head, n);
			Ispis(head.next);
			break;
		case 'N':
			printf("\nUnesite prezime koje zelite pronaci:\t");
			scanf(" %s", pronaci);

			p = Trazi(&head, pronaci);

			printf("\n%s %s %d\r\n", p->ime, p->prezime, p->godina);

			break;
		case 'B':
			printf("Unesite prezime koje zelite izbrisati:\t");
			scanf(" %s", pronaci);

			Brisi(&head, pronaci);
			Ispis(head.next);

			break;
		case 'I':
			printf("Unesite prezime iza kojeg zelite unijeti novi element:\t");
			scanf(" %s", pronaci);

			p = Trazi(&head, pronaci);
		
			printf("\nUnesite ime:\t\t");
			scanf(" %s", ime);
			printf("Unesite prezime:\t");
			scanf(" %s", prez);
			printf("Unesite godinu rodenja:\t");
			scanf(" %d", &god);
			puts("");
		
			n = noviStudent(ime, prez, god);

			unosPocetak(p, n);

			Ispis(head.next);
			
			
			break;
		case 'D':
			printf("Unesite prezime ispred kojeg zelite unijeti novi element:\t");
			scanf(" %s", pronaci);

			p = TraziPret(&head, pronaci);

			printf("\nUnesite ime:\t\t");
			scanf(" %s", ime);
			printf("Unesite prezime:\t");
			scanf(" %s", prez);
			printf("Unesite godinu rodenja:\t");
			scanf(" %d", &god);
			puts("");

			n = noviStudent(ime, prez, god);

			unosPocetak(p, n);

			Ispis(head.next);
			
			break;
		case 'S':
			Sortiraj(&head);
			Ispis(head.next);

			break;
		case 'C':
			Citaj(&head);
			Ispis(head.next);

			break;
		case 'U':
			Upisi(head.next);
			Ispis(head.next);

			break;
		case 'E':
			return 3;
			break;
		default:
			printf("Krivi unos!!\r\n");
		}
	}

	return 0;
}

Position noviStudent(char *i, char *pre, int g)
{
	Position p = NULL;

	p = (Position)malloc(sizeof(osoba));

	if (!p)
	{
		printf("Alokacija nije uspjela!\r\n");

		return NULL;
	}

	strcpy(p->ime, i);
	strcpy(p->prezime, pre);
	p->godina = g;

	p->next = NULL;

	return p;
}

void Ispis(Position p)
{
	printf("------------------------------------------------------------\n");
	printf("Studenti:\r\n");

	while (p != NULL)
	{
		printf("\t%s %s %d\r\n", p->ime, p->prezime, p->godina);
		p = p->next;
	}

	printf("------------------------------------------------------------");
}

void unosPocetak(Position q, Position p)
{
	p->next = q->next;
	q->next = p;
}

void unosKraj(Position q, Position p)
{
	while (q->next != NULL)
	{
		q = q->next;
	}

	unosPocetak(q, p);
}

Position Trazi(Position p, char *a)
{
	p = p->next;

	while (p != NULL && strcmp(p->prezime, a))
		p = p->next;

	if (p == NULL)
	{
		printf("Osoba ne postoji u listi!\r\n");
		return NULL;
	}

	return p;
}

Position TraziPret(Position p, char *b)
{
	Position pret = p;

	p = p->next;

	while (p->next != NULL && strcmp(p->prezime, b) != 0)
	{
		pret = p;
		p = p->next;
	}

	if (p == NULL)
	{
		printf("Osoba ne postoji u listi!\r\n");
		return NULL;
	}

	return pret;
}

void Brisi(Position p, char *c)
{
	Position prev;

	prev = TraziPret(p, c);

	if (prev != NULL)
	{
		p = prev->next;
		prev->next = p->next;
		free(p);
	}
}

void Sortiraj(Position p)
{
	Position i, j, k, pom, end;

	i = p;
	end = NULL;

	while (i->next != end)
	{
		k = i;
		j = i->next;

		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				pom = j->next;
				k->next = pom;
				j->next = pom->next;
				pom->next = j;
				j = pom;
			}

			k = j;
			j = j->next;
		}

		end = j;
	}
}

void Citaj(Position p)
{
	FILE *fp = NULL;
	char dat[50];
	Position pom = NULL;

	printf("\nUnesite ime datoteke iz koje zelite procitati listu: ");
	scanf(" %s", dat);

	fp = fopen(dat, "r");

	if (fp == NULL)
	{
		printf("\nGreska!\r\n");
		exit(1);
	}
	
	while (!feof(fp))
	{
		pom = (Position)malloc(sizeof(osoba));

		if (pom == NULL)
			return -1;

		fscanf(fp, "%s %s %d", pom->ime, pom->prezime, &pom->godina);

		pom->next = p->next;
		p->next = pom;
		p = pom;
	}

	fclose(fp);
	
}

void Upisi(Position p)
{
	FILE *fp;
	char dat[50];

	printf("\nUnesite ime datoteke u koju zelite spremiti listu: ");
	scanf(" %s", dat);

	fp = fopen(dat, "w");

	if (fp == NULL)
		printf("\nGreska!\r\n");
	else
	{
		while (p != NULL)
		{
			fprintf(fp, "%s %s %d\n", p->ime, p->prezime, p->godina);
			p = p->next;
		}

		fclose(fp);
	}
}