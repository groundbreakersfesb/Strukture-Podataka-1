#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define VEL 50

struct Polinom;

typedef struct Polinom *Pozicija;

typedef struct Polinom {

	int koef;
	int pot;
	Pozicija next;
}_polinom;

int procitajIzDat(char *, const Pozicija);
int unos(const Pozicija, int, int);
int Povezivanje(Pozicija, Pozicija);
int pomnoziPolinome(const Pozicija, const Pozicija, Pozicija);
int ispis(const Pozicija);
int suma(const Pozicija, const Pozicija, const Pozicija);

int main(void)
{

	_polinom Head1, Head2, HeadS, HeadM;
	Head1.next = NULL;
	Head2.next = NULL;
	HeadS.next = NULL;
	HeadM.next = NULL;
	int provjera = 0;
	char imedat1[VEL] = "polinom1.txt";
	char imedat2[VEL] = "polinom2.txt";

	//polinom 1
	provjera = procitajIzDat(imedat1, &Head1);
	if (provjera == -1) printf("Greska u citanju iz datoteke!");

	//polinom 2
	provjera = procitajIzDat(imedat2, &Head2);
	if (provjera == -1) printf("Greska u citanju iz datoteke!");

	printf("\nPolinom1:\n");
	ispis(&Head1);

	printf("\nPolinom2:\n");
	ispis(&Head2);

	provjera = suma(&Head1, &Head2, &HeadS);
	if (provjera != 0) printf("\nGreska pri zbrajanju.");

	printf("\nSuma:\n");
	ispis(&HeadS);

	pomnoziPolinome(&Head1, &Head2, &HeadM);
	printf("\n\nUmnozak polinoma:\n\n");
	ispis(&HeadM);

	getchar();
	return 0;
}

int procitajIzDat(char* imedat, const Pozicija Head) {
	int a, b;
	FILE* ulz;
	char buffer[1024];

	ulz = fopen(imedat, "r");

	if (ulz == NULL) return -1;
	fgets(buffer, 1024, ulz);

	while (!feof(ulz))
	{
		fscanf(ulz, " %d %d", &a, &b);
		unos(Head, a, b);
	}

	fclose(ulz);
	return 0;

}
int unos(const Pozicija head, int tempK, int tempP)
{

	Pozicija q, p;
	p = head;

	while (p->next != NULL && p->next->pot>tempP)
	{
		p = p->next;
	}

	if (p->next != NULL && p->next->pot == tempP)
	{
		p->next->koef += tempK;
	}

	else {

		q = (Pozicija)malloc(sizeof(_polinom));

		q->koef = tempK;
		q->pot = tempP;

		Povezivanje(p, q);

	}
	return 0;

}
int Povezivanje(Pozicija p, Pozicija q) {

	if (!p) return -1;
	q->next = p->next;
	p->next = q;

	return 0;
}
int pomnoziPolinome(const Pozicija P1, const Pozicija P2, Pozicija U) {

	Pozicija k = P1->next;
	Pozicija l = P2->next;

	while (k != NULL) {
		while (l != NULL) {
			unos(U, k->koef * l->koef, k->pot + l->pot);
			l = l->next;
		}

		l = P2->next;
		k = k->next;
	}

	return 0;
}
int ispis(const Pozicija head) {

	int prvi = 1;
	Pozicija q = head->next;

	while (q != NULL) {

		if (prvi) {
			printf("%dx^%d ", q->koef, q->pot);
			prvi = 0;
		}
		else if (q->pot > 0)
			printf("+ %dx^%d ", q->koef, q->pot);
		else
			printf("+%d", q->koef);

		q = q->next;
	}
	return 0;
}
int suma(const Pozicija Head1, const Pozicija Head2, const Pozicija HeadS)
{
	Pozicija p1, p2;
	p1 = Head1->next;
	p2 = Head2->next;

	while (p1 != NULL)
	{
		unos(HeadS, p1->koef, p1->pot);
		p1 = p1->next;
	}

	while (p2 != NULL)
	{
		unos(HeadS, p2->koef, p2->pot);
		p2 = p2->next;
	}

	return 0;

}
