#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//9. Napisati program koji omogućava rad s binarnim stablom pretraživanja.Treba
//omogućiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
//nekog elementa.

//Za sve pisemo rekurziju

struct stablo;
typedef struct stablo *StabloPtr;

typedef struct stablo {

	int El;
	StabloPtr L;
	StabloPtr D;
}_stablo;

StabloPtr unesiEl(StabloPtr, int);
void ispisPreorder(const StabloPtr);
StabloPtr brisi(StabloPtr, int);
StabloPtr TraziMin(const StabloPtr);
StabloPtr Trazi(const StabloPtr, int);

int main(void)
{
	StabloPtr Root = NULL;
	char op = ' ';
	int test = 1;
	int x = 0;
	StabloPtr provjera = NULL;

	while (test) {

		printf("\nUpisite broj za zeljenu operaciju:\n1-unos novog elementa\n2-ispis elemenata\n3-brisanje\n4-pronalazenje elementa\n5-izlaz\n");
		scanf(" %c", &op);

		switch (op) {

		case '1':
			printf("\nUnesite element: ");
			scanf(" %d", &x);
			Root = unesiEl(Root, x);
			if (Root == NULL) {
				printf("Greska!\n");
				test = 0;
			}
			break;

		case '2':
			ispisPreorder(Root);
			break;

		case '3': 
			printf("Unesite element kojeg zelite obrisati: ");
			scanf(" %d", &x);
			provjera = brisi(Root, x);
			if (provjera == Root)
				printf("Elemet je obrisan.\n");
			break;

		case '4': 
			printf("Unesite element kojeg zelite pronaci: ");
			scanf(" %d", &x);
			provjera = Trazi(Root, x);
			if (provjera == NULL)
				printf("Tog elementa nema u stablu.\n");
			else
				printf("Element %d je pronaden.\n", provjera->El);
			break;

		case '5': 
			test = 0;
			break;

		default: printf("\nUnijeli ste krivo, unesite ponovo!\n");
			break;

		}
	}

	getchar();
	getchar();
	return 0;
}

StabloPtr unesiEl(StabloPtr Root, int x) {

	StabloPtr p = Root;

	if (p == NULL)
	{
		p = (StabloPtr)malloc(sizeof(_stablo));
		if (p == NULL) return NULL;
		p->El = x;
		p->D = NULL;
		p->L = NULL;

	}

	else if (x > p->El)
	{
		p->D = unesiEl(p->D, x);
	}

	else if (x < p->El)
	{
		p->L = unesiEl(p->L, x);
	}


	return p;
}

void ispisPreorder(const StabloPtr Root) {

	if (Root != NULL) {
		printf("%d ", Root->El);
		ispisPreorder(Root->L);
		ispisPreorder(Root->D);
	}
	return;
}

StabloPtr brisi(StabloPtr p, int x) {

	StabloPtr temp = NULL;

	if (p == NULL)
		printf("Tog elementa nema u stablu!\n");

	else if (x < p->El)
		p->L= brisi(p->L, x);

	else if (x > p->El)
		p->D= brisi(p->D, x);

	else if (p->D && p->L != NULL) {		//Nasli smo taj element i ima 2 djece
		temp = TraziMin(p->D);
		p->El = temp->El;
		p->D = brisi(p->D, p->El);
	}

	else {				//Nasli smo taj element, ima 1 ili 0 djece
		temp = p;
		if (p->L == NULL)
			p = p->D;
		else
			p = p->L;
		free(temp);
	}

	return p;
}

StabloPtr TraziMin(const StabloPtr p) {

	if (p == NULL) return NULL;

	else if (p->L == NULL) return p; //Ako slijeva nema element, znaci da je najmanji

	else return TraziMin(p->L);	//Ako slijeva ima elemente, tu je minimum

}

StabloPtr Trazi(const StabloPtr p, int x) {

	if (p == NULL) return NULL;

	else if (x < p->El) return Trazi(p->L, x);

	else if (x > p->El) return Trazi(p->D, x);

	else return p;
}