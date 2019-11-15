#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//5. Za dvije sortirane liste L1 i L2(mogu se proèitati iz datoteke ili unijeti ruèno, bitno je
//	samo da su sortirane), napisati program koji stvara novu vezanu listu tako da raèuna :
//a) L1VL2,
//b) L1^L2.
//Liste osim pokazivaèa na slijedeæu strukturu imaju i jedan cjelobrojni element, po
//kojem su sortir

#define list_foreach(p, head) for (p = head->next; p != NULL; p = p->next)

struct cvor;

typedef struct cvor *Pozicija;
typedef struct cvor {
	int el;
	Pozicija next;

}_cvor;

int unos(const Pozicija, int);
int unosSortirano(const Pozicija Head, int x);
int sort(const Pozicija);
int ispis(const Pozicija);
int unija(const Pozicija, const Pozicija, const Pozicija);
int presjek(const Pozicija, const Pozicija, const Pozicija);
int trazi(const Pozicija, int);

int main(void)
{

	_cvor Head1, Head2, HeadU, HeadP;
	int br1 = 0;
	int br2 = 0;
	int i, x;
	Head1.next = NULL;
	Head2.next = NULL;
	HeadU.next = NULL;
	HeadP.next = NULL;


	printf("Upisite broj elemenata prve liste:");
	scanf("%d", &br1);

	for (i = 0; i < br1; i++)
	{
		printf("\nUnesite %d. element: ", i + 1);
		scanf(" %d", &x);
		if (trazi(&Head1, x) != 0) {
			printf("Ovaj element je vec unesen! Unesite novi: ");
			i--;
			continue;
		}

		unosSortirano(&Head1, x);
	}

	printf("Upisite broj elemenata druge liste:");
	scanf(" %d", &br2);

	for (i = 0; i < br2; i++)
	{
		printf("\nUnesite %d. element: ", i + 1);
		scanf("%d", &x);
		if (trazi(&Head2, x) != 0) {
			printf("Ovaj element je vec unesen! Unesite novi: ");
			i--;
			continue;
		}

		unosSortirano(&Head2, x);
	}

	printf("\nLista 1: ");
	ispis(&Head1);

	printf("\nLista 2: ");
	ispis(&Head2);

	unija(&Head1, &Head2, &HeadU);
	printf("\nUnija: ");
	ispis(&HeadU);

	presjek(&Head1, &Head2, &HeadP);
	printf("\nPresjek: ");
	ispis(&HeadP);

	getchar();
	getchar();
	return 0;

}

int unos(const Pozicija Head, int x)
{
	Pozicija q;
	Pozicija p;
	p = Head;

	q = (Pozicija)malloc(sizeof(_cvor));

	if (q == NULL) return -1;

	q->el = x;
	q->next = p->next;
	p->next = q;

	return 0;
}

int unosSortirano(const Pozicija Head, int x)
{
	Pozicija it = Head;

	for (; it->next != NULL; it = it->next)
	{
		if (it->next->el == x)
		{
			// Vec postoji, ne radi nista, izadji iz funkcije o d m a h
			return 0;
		}


		if (it->next->el < x)
		{
			break;
		}
	}

	return unos(it, x);
}

int ispis(const Pozicija Head)
{
	Pozicija p;
	p = Head->next;

	for (p = Head->next; p != NULL; p = p->next)
	{
		printf("%d ", p->el);
	}

	return 0;
}

int unija(const Pozicija Head1, const Pozicija Head2, const Pozicija Head3) {

	Pozicija p1;
	Pozicija p2;
	Pozicija p3 = Head3;

	for (p1 = Head1->next; p1 != NULL; p1 = p1->next)
		unosSortirano(p3, p1->el);
	
	for (p2 = Head2->next; p2 != NULL; p2 = p2->next)
		unosSortirano(p3, p2->el);

	return 0;
}

int presjek(const Pozicija Head1, const Pozicija Head2, const Pozicija Head3) {

	Pozicija p1;
	Pozicija p2;
	Pozicija p3 = Head3;

	for (p2 = Head2->next; p2 != NULL; p2 = p2->next) {
		for (p1 = Head1->next; p1 != NULL; p1 = p1->next)
			if (p2->el == p1->el)
			{
				unosSortirano(p3, p2->el);
			}
	}

	return 0;
}
int trazi(const Pozicija Head, int x) {

	Pozicija p = Head->next;
	while (p != NULL) {
		if (p->el == x)
			return 1;
		p = p->next;
	}

	return 0;
}
