#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct cvor;
typedef struct cvor* Pozicija;

struct cvor
{
	float El;
	Pozicija next;
};

float Citanje_Dat(Pozicija);
float Ispis(Pozicija);
float Push(Pozicija, float);
float Pop(Pozicija);
float Racunaj(Pozicija, char*);
float Operacija(Pozicija, char, int);

int main()
{
	struct cvor A;
	char *buffer;

	A.next = NULL;

	Citanje_Dat(&A);

	Ispis(A.next);

	system("pause");

	return 0;
}

float Citanje_Dat(Pozicija P)
{
	FILE *fp;
	char dat[50];
	char *buffer = NULL;
	int n;

	printf("Unesite ime datoteke:\t");
	scanf(" %s", dat);

	fp = fopen(dat, "r");

	if (!fp)
	{
		printf("\nDatoteka ne postoji!\r\n");
		exit(1);
	}

	buffer = (char *)malloc(1000 * sizeof(char));

	if (!buffer)
	{
		printf("Alokacija nije uspjela!\r\n");
		return -1;
	}


	fgets(buffer, 1000, fp);
	Racunaj(P, buffer);

	fclose(fp);

	free(buffer);

	return 1;
}

float Ispis(Pozicija P)
{
	if (P == NULL)
		printf("Lista je prazna!\r\n");

	while (P != NULL)
	{
		printf("\n\tRezultat stoga: %.3f\t", P->El);
		P = P->next;
	}

	puts("");

	return 1;
}

float Push(Pozicija P, float x)
{
	Pozicija Q;

	Q = (Pozicija)malloc(sizeof(struct cvor));

	if (!Q)
	{
		printf("Alokacija nije uspjela!\r\n");
		return -1;
	}

	Q->next = P->next;
	P->next = Q;
	Q->El = x;

	return 1;
}

float Pop(Pozicija P)
{
	float x;
	Pozicija temp;

	
	x = P->next->El;
	temp = P->next;
	P->next = P->next->next;

	free(temp);
	
	return x;
}

float Racunaj(Pozicija P, char* buffer)
{
	int n = 0;
	char operator= 0;
	float broj = 0;
	char *pBuffer = buffer;
	int odabir, a = 1;

	while (a)
	{
		printf("\nPrikaz operacija na stogu?\r\n1 - DA\t\t2 - NE\r\n");
		scanf(" %d", &odabir);

		if (odabir == 1 || odabir == 2)
			a = 0;
	}

	switch (odabir)
	{
		case 1:
			printf("\n\tOperacije na stogu:\r\n");
			puts("\t------------------\r\n");

			while (strlen(pBuffer) > 0)
			{
				if (sscanf(pBuffer, " %f%n", &broj, &n) == 1)
				{
					printf(" Dodavanje broja %.3f na stog.\r\n", broj);
					Push(P, broj, odabir);
					pBuffer += n;
				}
				else
				{
					sscanf(pBuffer, " %c%n", &operator, &n);
					Operacija(P, operator, odabir);
					pBuffer += n;
				}
			}

			break;
		case 2:
			while (strlen(pBuffer) > 0)
			{
				if (sscanf(pBuffer, " %f%n", &broj, &n) == 1)
				{
					Push(P, broj, odabir);
					pBuffer += n;
				}
				else
				{
					sscanf(pBuffer, " %c%n", &operator, &n);
					Operacija(P, operator, odabir);
					pBuffer += n;
				}
			}

			break;
	}

	return 1;
}

float Operacija(Pozicija P, char x, int odabir)
{
	float operand1 = 0;
	float operand2 = 0;

	switch (odabir)
	{
		case 1:
			switch (x)
			{
			case ('*'):
				printf("  Znak '*' u postfixu...\r\n");

				operand1 = Pop(P);
				operand2 = Pop(P);
				Push(P, operand1 * operand2);

				break;
			case ('/'):
				printf("  Znak '/' u postfixu...\r\n");

				operand1 = Pop(P);
				operand2 = Pop(P);
				Push(P, operand2 / operand1);

				break;
			case ('+'):
				printf("  Znak '+' u postfixu...\n");

				operand1 = Pop(P);
				operand2 = Pop(P);
				Push(P, operand1 + operand2);

				break;
			case ('-'):
				printf("  Znak '-' u postfixu...\r\n");

				operand1 = Pop(P);
				operand2 = Pop(P);
				Push(P, operand2 - operand1);

				break;
			default:
				printf("  Nepoznata operacija!\r\n");
				break;
			}

			break;
		case 2:
	
			switch (x)
			{
			case ('*'):
				operand1 = Pop(P);
				operand2 = Pop(P);
				Push(P, operand1 * operand2);

				break;
			case ('/'):
				operand1 = Pop(P);
				operand2 = Pop(P);
				Push(P, operand2 / operand1);

				break;
			case ('+'):
				operand1 = Pop(P);
				operand2 = Pop(P);
				Push(P, operand1 + operand2);

				break;
			case ('-'):
				operand1 = Pop(P);
				operand2 = Pop(P);
				Push(P, operand2 - operand1);

				break;
			default:
				printf("  Nepoznata operacija!\r\n");
				break;
			}

			break;
	}

	return 1;
}

