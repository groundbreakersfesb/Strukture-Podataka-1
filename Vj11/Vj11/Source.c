#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define VEL 50

//11. Napisati kod koji za zadane podatke studenata(matični broj, ime i prezime) pravi hash tablicu sa zasebnim redovima.
//Tablica ima 11 mjesta, a funkcija za preslikavanje ključ računa da se zbraja ASCII vrijednost prvih pet slova prezimena
//i zatim računa ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice.
//Studenti s istim ključem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
//Kada se tablica izgradi treba ispisati cijelu tablicu(naglasiti na kojem ključu se nalaze koji podaci) te ponuditi mogućnost 
//da se za određenog studenta(prezime i ime) ispiše njegov matični broj.

struct CvorListe;
struct HashT;
typedef struct CvorListe* Lista;
typedef struct HashT* hashTab;

typedef struct CvorListe {
	char ime[VEL];
	char prezime[VEL];
	int mb;
	Lista next;
}cvorListe;

typedef struct HashT {
	int velTab;
	Lista* hashListe;
};

hashTab inicijalizacijaTablice(int);
int preslikavanje(char*, int);
bool citanje(hashTab);
bool dodajUListu(Lista, char*, char*, int);
bool ispis(hashTab);
Lista trazi(hashTab, char*, char*);

int main(void) {

	hashTab tablica = NULL;
	bool provjera = false;
	char odabir[VEL] = "";
	char ime[VEL]="", prez[VEL]="";
	Lista cvor = NULL;

	tablica = inicijalizacijaTablice(11);
	if (!tablica) {
		printf("Greska!\n");
		return 1;
	}

	provjera = citanje(tablica);
	if (!provjera) {
		printf("Greska!\n");
		return 1;
	}

	provjera = ispis(tablica);
	if (!provjera) {
		printf("Greska!\n");
		return 1;
	}

	while (1) {

		printf("Unesite 1 ako zelite ispisati maticni broj studenta, za izlaz unesite 0: ");
		scanf(" %s", odabir);
		
		if (strcmp(odabir, "1") == 0)
		{
			printf("Unesite ime: ");
			scanf(" %s", ime);
			printf("Unesite prezime: ");
			scanf(" %s", prez);
			cvor = trazi(tablica, ime, prez);
			if (!cvor)
				printf("\nNema toga studenta.\n");
			else
				printf("\n%s %s, maticni broj: %d\n", cvor->ime, cvor->prezime, cvor->mb);
		}

		else if (strcmp(odabir, "0")==0)
			break;

		else
			printf("Pogresan unos!\n");
	}

	getchar();
	getchar();
	return 0;
}

hashTab inicijalizacijaTablice(int vel) {

	hashTab T = NULL;
	int i=0;

	T = (hashTab)malloc(sizeof(struct HashT));
	if (!T) return NULL;

	T->velTab = vel;
	T->hashListe = (Lista*)malloc(sizeof(Lista) * vel);

	if (T->hashListe == NULL) return NULL;

	for (i = 0; i < vel; i++)
	{
		T->hashListe[i] = (Lista)malloc(sizeof(cvorListe));
		T->hashListe[i]->next = NULL;
	}
	
	return T;
}

int preslikavanje(char* prezime, int vel) {

	int i = 0;
	int redak = 0;
	int duljinaStringa = strlen(prezime);

	while (i < 5 && i < duljinaStringa)	//za slucaj da je prezime krace od 5 slova
	{
		redak += (int)prezime[i];
		i++;
	}

	return redak % vel;
}

bool citanje(hashTab Tablica) {

	FILE* ulz;
	int mb=0, redak = 0;
	char ime[VEL] = "";
	char prez[VEL] = "";
	bool provjera = false;
	int x = 0;

	ulz = fopen("studenti.txt", "r");

	if (!ulz) return false;

	while (!feof(ulz))
	{
		x=fscanf(ulz, " %d %s %s", &mb, ime, prez);
		if (x != 3) return false;		//Nije se sve uspjesno ucitalo

		redak = preslikavanje(prez, Tablica->velTab);

		provjera = dodajUListu(Tablica->hashListe[redak], ime, prez, mb); //Problem, kad se vrati pokazivač opet NULL

		if (Tablica->hashListe[redak] == NULL)
			return false;

		if (!provjera) return false;
	}

	fclose(ulz);
	return true;

}

bool dodajUListu(Lista Head, char*ime, char*prez, int mb) {

	Lista q = NULL;
	Lista p = Head;

	q = (Lista)malloc(sizeof(cvorListe));
	if (q == NULL) return false;

	strcpy(q->ime, ime);
	strcpy(q->prezime, prez);
	q->mb = mb;

	while (p->next!=NULL && strcmp(p->next->prezime, q->prezime) < 0)	//Sortiramo prema prezimenu
		p = p->next;

	//Ako vise ljudi ima isto prezime, sortiramo po imenu
	while (p->next!=NULL && strcmp(p->next->prezime, q->prezime)==0 && strcmp(p->next->ime, q->ime) < 0)
		p = p->next;
		
	q->next = p->next;
	p->next = q;

	return true;
}

bool ispis(hashTab Tablica) {

	int i = 0;
	Lista p = NULL;

	for (i = 0; i < Tablica->velTab; i++)
		if (Tablica->hashListe[i]->next != NULL) {	//Nesto je uneseno u tom retku tablice
			p = Tablica->hashListe[i]->next;

			printf("Kljuc %d:\n", i);
			while (p != NULL) {
				printf("\t%d  %s %s\n", p->mb, p->ime, p->prezime);
				p = p->next;
			}
		}
	return true;
}

Lista trazi(hashTab Tablica, char* ime, char* prezime) {

	int redak = preslikavanje(prezime, Tablica->velTab);
	Lista p = Tablica->hashListe[redak]->next;

	while (p != NULL && strcmp(p->prezime, prezime) != 0 && strcmp(p->ime, ime) != 0)
		p = p->next;

	return p;
}