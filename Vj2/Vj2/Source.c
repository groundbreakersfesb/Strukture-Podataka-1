#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define VEL 30


//2. Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
//a) dinamički dodaje novi element na početak liste,
//b) ispisuje listu,
//c) dinamički dodaje novi element na kraj liste,
//d) pronalazi element u listi(po prezimenu),
//e) briše određeni element iz liste,
//U zadatku se ne smiju koristiti globalne varijable.

struct osoba;
typedef struct osoba *Pozicija;

struct osoba {

	char ime[VEL];
	char prezime[VEL];
	int gr;
	Pozicija next;
};

int unosPocetak(Pozicija);
int unosKraj(Pozicija);
void ispis(Pozicija);
int brisiel(Pozicija, char *);
Pozicija traziprethodni(Pozicija, char *);
Pozicija traziprezime(Pozicija, char *);

int main(void)
{

	struct osoba head;
	head.next = NULL;
	int provjera = 0;
	char prez[VEL];
	Pozicija tr_prez;

	provjera = unosPocetak(&head);
	if (provjera == -1) printf("\nGreska pri unosu.");

	provjera = unosKraj(&head);
	if (provjera == -1) printf("\nGreska pri unosu.");

	ispis(head.next);


	printf("\nUpisi prezime:");
	scanf(" %s", prez);

	tr_prez = traziprezime(head.next, prez);

	if (tr_prez == NULL) printf("\nNismo pronasli osobu s tim prezimenom!");

	else printf("\nOsoba je: %s %s %d", tr_prez->ime, tr_prez->prezime, tr_prez->gr);

	printf("\nKoje prezime zelite izbrisati?");
	scanf(" %s", prez);

	provjera = brisiel(&head, prez);

	if (provjera == -1) printf("\nElement nije uspjesno izbrisan!");
	else printf("\nElement je uspjesno izbrisan!");

	getchar();
	getchar();
	return 0;

}

int unosPocetak(Pozicija p)
{
	Pozicija q;

	q = (Pozicija)malloc(sizeof(struct osoba));

	if (q == NULL) return -1;

	printf("Unesite podatke osobe:");
	scanf(" %s %s %d", q->ime, q->prezime, &q->gr);

	q->next = p->next;
	p->next = q;

	return 0;
}
void ispis(Pozicija p) {
	while (p != NULL)
	{
		printf("\n%s %s %d", p->ime, p->prezime, p->gr);
		p = p->next;
	}

}

int unosKraj(Pozicija p)
{

	while (p->next != NULL)
		p = p->next;

	return unosPocetak(p);

}

Pozicija traziprezime(Pozicija p, char *prez)
{
	while (p != NULL && strcmp(prez, p->prezime) != 0)
		p = p->next;

	return p;
}

int brisiel(Pozicija p, char *prez)
{
	Pozicija temp;

	p = traziprethodni(p, prez);

	if (p == NULL) return -1;
	else {

		temp = p->next;
		p->next = p->next->next;
		free(temp);

		return 0;

	}

}

Pozicija traziprethodni(Pozicija p, char *prez)
{
	while (p->next != NULL && strcmp(prez, p->next->prezime))
		p = p->next;

	if (p->next == NULL) return NULL;
	else return p;

}