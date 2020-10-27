/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char ime[50];
	char prezime[50];
	int bodovi;
}Student;

int brojStud(FILE *);
int upis(FILE *, Student *, int a);
int ispis(Student *);

int main()
{
	FILE *fp;
	int brR, i;
	Student *s = NULL;

	//otvaranje datoteke uz provjeru
	printf("Otvaram datoteku za citanje.\r\n");
	if ((fp = fopen("studenti.txt", "r")) == NULL)
	{
		printf("Greska pri otvaranju datoteke!\r\n");
		exit(1);
	}
	else
		printf("Uspjeh!\r\n");

	//brojanje studenata i ispis broja
	brR = brojStud(fp);
	printf("Broj studenata: %d.\r\n", brR + 1);

	//alokacija memorije i provjera
	s = (Student *)malloc((brR + 1) * sizeof(Student));
	if (s == NULL)
	{
		printf("Alokacija nije uspjela!\n");
		exit(-1);
	}

	rewind(fp);

	//ucitavanje zapisa iz datoteke
	upis(fp, s, brR);

	//ispis
	printf("---------------------------------------------------------------\n");
	for (i = 0; i <= brR; i++)
		ispis(s + i);


	fclose(fp);
	free(s);
	
	return 0;
}

int brojStud(FILE *fp)
{
	int a = 0;

	while (!feof(fp))
	{
		if (fgetc(fp) == '\n')
			a++;

	}

	return a;
}

int upis(FILE *fp, Student *s, int a)
{
	int i = 0;

	while (!feof(fp))
	{
		for (i = 0; i <= a; i++)
		{
			fscanf(fp, "%s %s %d", s[i].ime, s[i].prezime, &s[i].bodovi);
		}

	}

	return -2;
}

int ispis(Student *s)
{
	float rel;
	int i = 0;

	rel = (s->bodovi / (float)15) * 100;

	printf("Ime:%s\r\nPrezime:%s\r\nApsolutni broj bodova:%d\r\nRelativni broj bodova:%.2f\r\n", s->ime, s->prezime, s->bodovi, rel);

	puts("");

	return -3;
}
*/