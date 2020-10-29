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
void Ispis(Position );
void unosPocetak(Position, Position);
void unosKraj(Position, Position);
Position Trazi(Position, char *);
Position TraziPret(Position, char *);
void Brisi(Position, char *);

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
		printf("\nOdaberite:\r\nP = novi element na pocetak liste\r\nK = novi element na kraj liste\r\nN = pronalazak elementa u listi\r\nB = brisanje elementa u listi\r\nE = kraj\r\n");
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
		case 'E':
			return 0;
			break;
		default:
			printf("Krivi unos\r\n");
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

	while(p != NULL)
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

	while (p->next != NULL && strcmp(p->prezime, b))
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
