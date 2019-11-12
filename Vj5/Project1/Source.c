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
int sort(const Pozicija); 
int ispis(const Pozicija); 
int unija(const Pozicija, const Pozicija, const Pozicija);
int presjek(const Pozicija, const Pozicija, const Pozicija);

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
		printf("\nUnesite %d. element", i + 1); 
		scanf("%d", &x); 

		unos(&Head1, x); 
	}

	printf("Upisite broj elemenata druge liste:");
	scanf("%d", &br2);

	for (i = 0; i < br2; i++)
	{
		printf("\nUnesite %d. element", i + 1);
		scanf("%d", &x);
		unos(&Head2, x);
	}

	sort(&Head1); 
	sort(&Head2); 

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
	q->next=p->next; 
	p->next = q; 

	return 0;
}

int sort(const Pozicija head)
{
	Pozicija p = head;
	Pozicija j, prev_j, temp, end;
	end = NULL;

	while (p->next != end) {

		prev_j = p;
		j = p->next;

		while (j->next != end) {

			if (j->el > j->next->el) {

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

	return 0; 
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
	int test = 1;

	for (p1 = Head1->next; p1 != NULL; p1 = p1->next)
		unos(p3, p1->el);

	for (p2 = Head2->next; p2 != NULL; p2 = p2->next) {
		for (p1 = Head1->next; p1 != NULL; p1 = p1->next)
			if (p2->el == p1->el)
			{
				test = 0;
				break;
			}

		if (test)
			unos(p3, p2->el);
		test = 1;

	}

	sort(p3);

	return 0;
}

int presjek(const Pozicija Head1, const Pozicija Head2, const Pozicija Head3) {

	Pozicija p1;
	Pozicija p2;
	Pozicija p3 = Head3;
	int test = 1;

	for (p2 = Head2->next; p2 != NULL; p2 = p2->next) {
		for (p1 = Head1->next; p1 != NULL; p1 = p1->next)
			if (p2->el == p1->el)
			{
				test = 0;
				break;
			}

		if (!test)
			unos(p3, p2->el);
		test = 1;

	}

	sort(p3);

	return 0;
}