#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN 10
#define MAX 100

typedef struct cvor;
typedef struct cvor* Pozicija;

struct cvor
{
	int El;

	Pozicija next;
};

int ispis(Pozicija);
int Random(int, int);
int push(int, Pozicija);
int pop(Pozicija);
int Umetanje_Red(int, Pozicija);
int Brisi_Red(Pozicija);

int main()
{
	struct cvor s, r;
	int i;

	s.next = NULL;
	r.next = NULL;

	srand(time(0));

	for(i = 0; i < 5; i++)
		push(Random(MIN, MAX), &s);

	printf("Sadrzaj stoga:\r\n");
	ispis(s.next);

	pop(&s);
	printf("\nSadrzaj stoga nakon sto maknemo prvi element:\r\n");
	ispis(s.next);

	for (i = 0; i < 5; i++)
		Umetanje_Red(Random(MIN, MAX), &r);

	printf("\nSadrzaj reda:\r\n");
	ispis(r.next);

	Umetanje_Red(Random(MIN, MAX), &r);
	printf("\nSadrzaj reda nakon dodavanja elemenata na kraj:\r\n");
	ispis(r.next);

	Brisi_Red(&r);
	printf("\nSadrzaj reda nakon sto maknemo prvi element:\r\n");
	ispis(r.next);

	system("pause");

	return 0;
}

int ispis(Pozicija s)
{
	if (s == NULL)
		printf("Lista je prazna!\r\n");

	while (s != NULL)
	{
		printf(" %d\t", s->El);
		s = s->next;
	}

	puts("");

	return 1;
}

int Random(int min, int max)
{
	int a;

	a = (rand() % (max - min + 1)) + min;
	return a;

}

int push(int x, Pozicija s)
{
	Pozicija q;

	q = (Pozicija)malloc(sizeof(struct cvor));

	if (q == NULL)
	{
		printf("Greska!");
		return -1;
	}

	q->El = x;

	q->next = s->next;
	s->next = q;

	return 1;

}

int pop(Pozicija s)
{
	int x;
	Pozicija temp;


	if (s->next == NULL) 
	{
		printf("Lista je prazna!\n");
		return -1;
	}
	else 
	{
		x = s->next->El;
		temp = s->next;
		s->next = temp->next;
		free(temp);
	}

	return 1;

}

int Umetanje_Red(int x, Pozicija s)
{
	while (s->next != NULL)
		s = s->next;

	push(x, s);
}

int Brisi_Red(Pozicija s)
{
	Pozicija pom;

	if (s->next != NULL)
	{
		pom = s->next;
		s->next = pom->next;
		free(pom);
	}

	return 1;
}