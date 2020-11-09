#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct _polinom;
typedef struct _polinom *position;

int citanjeDatoteke(position);
int Ispis(position);
int Suma(position, position, position);
int Produkt(position, position, position);
position novi();

typedef struct _polinom
{
	int koef;
	int exp;

	position next;
}polinom;

int main()
{	
	polinom p1, p2, suma, produkt;

	p1.next = NULL;
	p2.next = NULL;
	suma.next = NULL;
	produkt.next = NULL;

	citanjeDatoteke(&p1);
	puts("----------------------------------------------------");
	printf("\tPrvi polinom:\r\n ");
	Ispis(p1.next);
	puts("");

	citanjeDatoteke(&p2);
	puts("----------------------------------------------------");
	printf("\tDrugi polinom:\n ");
	Ispis(p2.next);

	puts("----------------------------------------------------");
	printf("\tSuma polinoma:\n ");
	Suma(p1.next, p2.next, &suma);
	Ispis(suma.next);

	puts("----------------------------------------------------");
	printf("\tProdukt: \n ");
	Produkt(p1.next, p2.next, &produkt);
	Ispis(produkt.next);

	return 0;
}

int citanjeDatoteke(position p)
{
	char dat[50];
	FILE *fp = NULL;
	position q, prev, pom;

	printf("Upisi ime datoteke iz koje zelite unijeti polinom (npr. datoteka.txt): ");
	scanf(" %s", dat);

	fp = fopen(dat, "r");
	
	if (fp == NULL)
	{
		printf("\t\tGreska pri otvranju datoteke!\r\n");
		exit(1);
	}

	while (!feof(fp))
	{
		q = (position)malloc(sizeof(polinom));

		if (q == NULL) 
			return -1;

		q->next = NULL;

		fscanf(fp, "%d %d", &q->koef, &q->exp);

		prev = p;
		pom = p->next;

		while (pom != NULL && pom->exp > q->exp)
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

int Ispis(position p)
{
	while (p->next != NULL)
	{
		printf("%d*x^%d + ", p->koef, p->exp);
		p = p->next;
	}

	printf("%d*x^%d", p->koef, p->exp);

	puts("");

	return 2;
}

int Suma(position p1, position p2, position p3)
{
	position pom1, pom2;

	while (p1 != NULL && p2 != NULL)
	{
		pom1 = novi();

		if (p1->exp == p2->exp)
		{
			pom1->exp = p1->exp;
			pom1->koef = p1->koef + p2->koef;
			p1 = p1->koef;
			p2 = p2->next;

		}
		else if (p1->exp < p2->exp)
		{
			pom1->exp = p2->exp;
			pom1->koef = p2->koef;
			p2 = p2->next;
		}
		else
		{
			pom1->exp = p1->exp;
			pom1->koef = p1->koef;
			p1 = p1->next;
		}

		pom1->next = p3->next;
		p3->next = pom1;
		p3 = pom1;
	}

	return 0;
}

int Produkt(position p1, position p2, position p3)
{
	position pom1 = NULL;
	position pom2 = p2;
	position pom3 = p3;

	while (p1 != NULL)
	{
		p2 = pom2;

		while (p2 != NULL)
		{
			pom1 = novi();
			pom1->exp = p1->exp + p2->exp;
			pom1->koef = p1->koef*p2->koef;

			pom1->next = p3->next;
			p3->next = pom1;
			p3 = pom1;

			p2 = p2->next;
		}

		p1 = p1->next;
	}
	return 0;
}

position novi()
{
	position n = NULL;

	n = (position)malloc(sizeof(polinom));

	if (n == NULL)
		printf("Greška!!!\r\n");

	n->next = NULL;

	return n;
}