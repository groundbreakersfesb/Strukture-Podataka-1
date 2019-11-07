#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define VEL 30

struct _osoba;
typedef struct _osoba *Pozicija;

typedef struct _osoba {

	char ime[VEL];
	char prezime[VEL];
	int gr;
	Pozicija next;
} osoba;

char* Meni();
Pozicija NoviStudent(char *, char *, int);
int Povezivanje(Pozicija, Pozicija);
int unosPocetak(const Pozicija);
int unosKraj(const Pozicija);
int unosIza(const Pozicija, char *);
int unosIspred(const Pozicija, char *);
int unesi_u_datoteku(const Pozicija, char *);
void ispis(const Pozicija);
void procitaj_iz_datoteke(char *);
int brisiel(const Pozicija, char *);
void sortiraj_po_prez(const Pozicija);
Pozicija traziprethodni(const Pozicija, char *);
Pozicija traziprezime(const Pozicija, char *);


int main(void)
{

	osoba head;
	head.next = NULL;
	int provjera = 0;
	char imedat[VEL]="Studenti.txt",odabir[VEL]="0",prez[VEL];
	Pozicija tr_prez;


	do{
		strcpy(odabir, Meni());

		if (!strcmp(odabir, "0")) {}

		else if (!strcmp(odabir, "1"))
		{
			provjera = unosPocetak(&head);
			if (provjera == -1) printf("\nGreska pri unosu.");
		}

		else if (!strcmp(odabir, "2")) {
			provjera = unosKraj(&head);
			if (provjera == -1) printf("\nGreska pri unosu.");
		}

		else if (!strcmp(odabir, "3"))
		{
			ispis(&head);
			puts("");
		}

		else if (!strcmp(odabir, "4")) {

			printf("\nUpisi prezime:");
			scanf(" %s", prez);
			tr_prez = traziprezime(&head, prez);

			if (tr_prez == NULL)
				printf("\nNismo pronasli osobu s tim prezimenom!");
			else
				printf("\nOsoba je: %s %s %d", tr_prez->ime, tr_prez->prezime, tr_prez->gr);
		}

		else if (!strcmp(odabir, "5")) {

			printf("\nKoje prezime zelite izbrisati?");
			scanf(" %s", prez);
			provjera = brisiel(&head, prez);

			if (provjera == -1) printf("\nElement nije uspjesno izbrisan!");
			else printf("\nElement je uspjesno izbrisan!");
		}

		else if (!strcmp(odabir, "6")) {

			printf("\nIza koje osobe zelite unijeti novu? ");
			scanf(" %s", prez);
			provjera = unosIza(&head, prez);

			if (provjera == -1) printf("\nElement nije uspjesno dodan!");
			else printf("\nElement je uspjesno dodan!");
		}

		else if (!strcmp(odabir, "7")) {

			printf("\nIspred koje osobe zelite unijeti novu? ");
			scanf(" %s", prez);

			provjera = unosIspred(&head, prez);
			if (provjera == -1) printf("\nElement nije uspjesno dodan!");
			else printf("\nElement je uspjesno dodan!");
		}

		else if (!strcmp(odabir, "8")) {
			sortiraj_po_prez(&head);
			printf("\n\nSortiran ispis je:\n");
			ispis(&head);
		}

		else if (!strcmp(odabir, "9")) {
			provjera = unesi_u_datoteku(&head, imedat);
			if (provjera == -1)
				printf("\nGreska!");
			else
				printf("Lista je uspjesno unesena u datoteku!\n");
		}
		else if (!strcmp(odabir, "10")) {

			printf("\nIspis datoteke:\n");
			procitaj_iz_datoteke(imedat);

		}
		else
			printf("Pogresan unos!\n");

	} while (strcmp(odabir, "0"));

	getchar();
	getchar();
	return 0;

}

char* Meni() {
	char izbor[VEL];
	printf("\nUnesite:\n0 - izlaz\n1 - unos na pocetak\n2 - unos na kraj\n3 - ispis liste\n4 - trazenje elementa po prezimenu\n5 - brisanje elementa\n6 - unos iza odredenog elementa\n7 - unos ispred odredenog elementa\n8 - sortiranje liste\n9 - ispis u datoteku\n10 - citanje iz datoteke\n");
	scanf(" %s", izbor);
	return izbor;
}
Pozicija NoviStudent(char *imeS, char *prezS, int godrod) {

	Pozicija p = (Pozicija)malloc(sizeof(osoba));
	if (!p)
		return p;
	p->gr = godrod;
	strcpy(p->ime, imeS);
	strcpy(p->prezime, prezS);
	p->next = NULL;
	return p;
}
int Povezivanje(Pozicija poslije, Pozicija prije) {

	if (!prije) return -1;
	poslije->next = prije->next;
	prije->next = poslije;
	return 0;
}
int unosPocetak(const Pozicija head)
{
	Pozicija q,p=head;
	int godrod;
	char im[VEL], prez[VEL];

	printf("Unesite podatke o osobi: ");
	scanf(" %s %s %d", im, prez, &godrod);

	q = NoviStudent(im, prez, godrod);
	if (q == NULL) return -1;
	Povezivanje(q, p);

	return 0;
}
void ispis(const Pozicija head) {
	Pozicija p = head->next;
	while (p != NULL)
	{
		printf("\n%s %s %d", p->ime, p->prezime, p->gr);
		p = p->next;
	}

}

int unosKraj(const Pozicija head)
{
	Pozicija p = head;
	while (p->next != NULL)
		p = p->next;

	return unosPocetak(p);

}

Pozicija traziprezime(const Pozicija head, char *prez)
{
	Pozicija p = head->next;
	while (p != NULL && strcmp(prez, p->prezime) != 0)
		p = p->next;

	return p;
}

int brisiel(const Pozicija head, char *prez)
{
	Pozicija temp,p=head;

	p = traziprethodni(p, prez);

	if (p == NULL) return -1;
	else {

		temp = p->next;
		p->next = p->next->next;
		free(temp);

		return 0;

	}

}

Pozicija traziprethodni(const Pozicija head, char *prez)
{
	Pozicija p = head;
	while (p->next != NULL && strcmp(prez, p->next->prezime))
		p = p->next;

	if (p->next == NULL) return NULL;
	else return p;

}

int unosIza(const Pozicija head, char *prez)
{
	Pozicija p = head;
	p = traziprezime(p, prez);

	if (p == NULL) return -1;

	return unosPocetak(p);

}

int unosIspred(const Pozicija head, char *prez)
{
	Pozicija p = head;
	p = traziprethodni(p, prez);

	if (p == NULL) return -1;

	return unosPocetak(p);

}

void sortiraj_po_prez(const Pozicija head)						
{
	Pozicija p = head;
	Pozicija j, prev_j, temp, end;
	end = NULL;

	while (p->next != end) {

		prev_j = p;
		j = p->next;

		while (j->next != end) {

			if (strcmp(j->prezime, j->next->prezime) > 0) {

				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			prev_j = j;
			j = j->next;

		}

		end = j;
	}
}                
int unesi_u_datoteku(const Pozicija head, char *imedat)			
{
	FILE *ulz;
	Pozicija p = head->next;

	ulz = fopen(imedat, "w");

	if (ulz == NULL) return -1;

	while (p != NULL) {

		fprintf(ulz, "\n%s %s %d", p->ime, p->prezime, p->gr);

		p = p->next;
	}

	fclose(ulz);
	return 0;
}
void procitaj_iz_datoteke(char * imedat) {				

	FILE *izl;
	izl = fopen(imedat, "r");
	osoba temp;

	if (izl == NULL) {
		printf("\nGreska!");
		return 1;
	}

	while (!feof(izl)) {
		fscanf(izl, " %s %s %d", temp.ime, temp.prezime, &temp.gr);
		printf("\n%s %s %d", temp.ime, temp.prezime, temp.gr);
	}


	fclose(izl);
}