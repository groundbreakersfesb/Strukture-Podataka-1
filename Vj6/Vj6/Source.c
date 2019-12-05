#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


//6. Napisati program koji pomoću vezanih listi simulira rad :
//a) stoga,
//b) reda.
//Napomena: Funkcija "push" sprema cijeli broj, slučajno generirani u opsegu od 10 - 100

struct cvor;

typedef struct cvor *Pozicija;

typedef struct cvor {

	int el;
	Pozicija next;

}_cvor;

int push(const Pozicija);
int popS(const Pozicija);
int popR(const Pozicija);
int generiraj();

int main(void)
{
	srand(time(NULL));
	_cvor HeadS, HeadR;
	HeadS.next = NULL;
	HeadR.next = NULL;
	char unos[30];
	int provjera = 0;

	while(1){

		printf("\nMeni:\n1-Unos na stog\n2-Skidanje sa stoga\n3-Unos u red\n4-Brisanje s reda\n0-izlaz\n");
		scanf(" %s", unos);


		if (strcmp(unos, "0") == 0)
			break;

		else if (strcmp(unos, "1") == 0) {
			provjera = push(&HeadS);
			if (provjera != 0)
				printf("Greska kod unosa.\n");
			else
				printf("Element je uspjesno dodan na stog :)\n");
		}


		else if (strcmp(unos, "2") == 0) {
			provjera = popS(&HeadS);
			if (provjera == -1)
				printf("\nStog je prazan.");
			else
				printf("Element %d je izbrisan sa stoga :)\n", provjera);
		}


		else if (strcmp(unos, "3") == 0) {
			provjera = push(&HeadR);
			if (provjera != 0)
				printf("\nGreska kod unosa.");
			else
				printf("Element je uspjesno dodan u red :)\n");
		}



		else if(strcmp(unos, "4")==0){
			provjera = popR(&HeadR);
		if (provjera == -1)
			printf("Red je prazan.\n");
		else
			printf("\nElement %d je izbrisan iz reda :)\n", provjera);
	}

		else
			printf("Krivo ste upisali!\n");
}

	getchar();
	getchar();
	return 0;
}


int push(const Pozicija Head)
{
	int x;
	Pozicija q;
	Pozicija p = Head;

	x = generiraj();
	printf("Generiran je broj %d\n", x);

	q = (Pozicija)malloc(sizeof(_cvor));

	if (q == NULL) return -1;

	q->el = x;
	q->next = p->next;
	p->next = q;

	return 0;
}
int generiraj() {

	return rand() % 91 + 10;
}

int popS(const Pozicija Head) {
	Pozicija p = Head;
	Pozicija temp;
	int x = 0;

	temp = p->next;
	if (temp == NULL)
		return -1;

	x = temp->el;
	p->next = p->next->next;
	free(temp);
	return x;

}
int popR(const Pozicija Head) {

	Pozicija p = Head;
	Pozicija temp;
	int x=0;

	if (p->next == NULL)
		return -1;

	while (p->next->next!= NULL)
		p = p->next;

	temp = p->next;
	x = temp->el;
	p->next = NULL;
	free(temp);
	return x;

}