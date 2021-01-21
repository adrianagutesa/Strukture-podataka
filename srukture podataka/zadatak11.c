#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define VEL 11
#define MAX_DAT 1024

struct cvorListe;
typedef struct cvorListe* Pozicija;
struct hashT;
typedef struct hashT* hashTab;

struct cvorListe
{
	char ime[MAX];
	char prezime[MAX];
	int mat_br;
	Pozicija next;
};

struct hashT
{
	int vel_tab;
	Pozicija *studenti;
};


hashTab InicijalizacijaTablice(int);
int Citanje_Datoteke(char*, hashTab);
int Stvori_Kljuc(char*);
int Dodaj_Studenta(char*, char*, int, int, hashTab);
int Usporedi(Pozicija, Pozicija);
int Ispis_Tablice(hashTab);
int Ispis_Broja(hashTab);
Pozicija Trazi(char*, char*, hashTab);


int main()
{
	hashTab H = NULL;
	int odabir = 0;
	char dat[MAX_DAT] = { 0 };

	H = InicijalizacijaTablice(VEL);

	printf("Unesite ime datoteke iz koju zelite ucitati listu studenata:\t\t");
	scanf(" %s", dat);
	Citanje_Datoteke(dat, H);

	Ispis_Tablice(H);

	while (1)
	{
		printf("\nUnesite:\r\n1 - ispis maticnog broja studenta\r\n2 - izlaz\r\nMoj odabir:   ");
		scanf(" %d", &odabir);

		switch (odabir)
		{
		case 1:

			Ispis_Broja(H);

			break;
		case 2:

			return 0;

			break;
		default:

			printf("Krivi unos!\r\n");

			break;
		}

	}

	return 0;
}

hashTab InicijalizacijaTablice(int x)
{
	hashTab H = NULL;
	int i;

	H = (hashTab)malloc(sizeof(struct hashT));

	if (!H)
	{
		printf("Greska pri alokaciji memorije!");
		return NULL;
	}

	H->vel_tab = VEL;
	H->studenti = (Pozicija*)malloc(VEL * sizeof(struct cvorListe));

	if (!H->studenti)
	{
		printf("Greska pri alokaciji memorije!");
		return NULL;
	}

	for (i = 0; i < H->vel_tab; i++)
	{
		H->studenti[i] = (Pozicija)malloc(sizeof(struct cvorListe));
		H->studenti[i]->next = NULL;
	}

	return H;


}

int Citanje_Datoteke(char *dat, hashTab H)
{
	FILE *fp = NULL;
	int kljuc = 0, br = 0;
	char ime[MAX], prezime[MAX];

	fp = fopen(dat, "r");

	if (!fp)
	{
		printf("Greska pri otvaranju datoteke!");
		return NULL;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d", ime, prezime, &br);

		kljuc = Stvori_Kljuc(prezime);

		Dodaj_Studenta(ime, prezime, br, kljuc, H);

		if (!Dodaj_Studenta)
		{
			printf("Student se ne moze dodati!");
			return NULL;
		}

	}

	fclose(fp);

	return 0;
}

int Stvori_Kljuc(char* prezime)
{
	int sum = 0;
	int i;

	for (i = 0; i < 5; i++)
		sum += tolower(prezime[i]);

	return sum % VEL;
}

int Dodaj_Studenta(char* ime, char* prezime, int br, int kljuc, hashTab H)
{
	Pozicija P = NULL;
	Pozicija Q = NULL;

	P = H->studenti[kljuc];

	Q = (Pozicija)malloc(sizeof(struct cvorListe));

	if (!Q)
	{
		printf("Greska pri alokaciji memorije!");
		return NULL;
	}

	strcpy(Q->ime, ime);
	strcpy(Q->prezime, prezime);
	Q->mat_br = br;

	while (P->next != NULL && strcmp(P->next->prezime, Q->prezime) < 0)
		P = P->next;

	while (P->next != NULL && strcmp(P->next->prezime, Q->prezime) == 0 && strcmp(P->next->prezime, Q->prezime) < 0)
		P = P->next;

	Q->next = P->next;
	P->next = Q;

	return 0;
}

int Ispis_Tablice(hashTab H)
{
	int i;
	Pozicija P = NULL;

	printf("\r\n\tTablica:\r\n");

	for (i = 0; i < H->vel_tab; i++)
	{
		if (H->studenti[i]->next != NULL)
		{
			P = H->studenti[i]->next;

			printf("\r\n\t%d. kljuc:\r\n", i + 1);

			while (P!=NULL)
			{
				printf("\r\nIme:\t%s\r\nPrezime:\t%s\r\nMaticni broj:\t%d\r\n", P->ime, P->prezime, P->mat_br);
				P = P->next;
			}
		}
		
	}

	puts("-------------------------------------------------------------------");


	return 0;
}

int Ispis_Broja(hashTab H)
{
	char ime[VEL], prezime[VEL];
	int br;
	Pozicija cvor = NULL;

	printf("\r\n\r\nUnesite ime i prezime studenta kojem zelite ispisati maticni broj: ");
	scanf(" %s %s", ime, prezime);

	cvor = Trazi(ime, prezime, H);

	if (!cvor)
		printf("Student ne postoji u listi!\r\n");
	else
		printf("\r\n%s %s: %d\r\n", cvor->ime, cvor->prezime, cvor->mat_br);

}

Pozicija Trazi(char* ime, char* prezime, hashTab H)
{
	Pozicija P = NULL;

	P = H->studenti[Stvori_Kljuc(prezime)];

	while (P != NULL && strcmp(ime, P->ime) != 0 && strcmp(prezime, P->prezime) != 0)
		P = P->next;

	return P;
}



