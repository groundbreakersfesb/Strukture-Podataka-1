#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define VEL 50

//8. Napisati program koji pomoću vezanih listi(stabala) predstavlja strukturu direktorija.
//Omogućiti unos novih direktorija i pod - direktorija, ispis sadržaja direktorija i
//povratak u prethodni direktorij.Točnije program treba preko menija simulirati
//korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.

struct stog;
struct stablo;

typedef struct stog* StogPtr;
typedef struct stablo* StabloPtr;

typedef struct stablo {
	char* ime;
	StabloPtr child;
	StabloPtr sibling;
}_stablo;

typedef struct stog {
	StabloPtr el;
	StogPtr next;
}_stog;

typedef struct directoryStatus {
	StabloPtr currentDirectory; // ante // ante
	StogPtr parentDirectories; // [ "Student", "Users", "C:" ] // [ "Student", "Users", "C:" ]
} DirectoryStatus;

typedef struct popResult {
	StabloPtr data;
	bool isSuccess;
} PopResult;


PopResult pop(StogPtr);
PopResult push(StogPtr, StabloPtr);
bool MD(StabloPtr, char*);
bool CdDir(DirectoryStatus*);
bool Cd(DirectoryStatus*);
void print(StogPtr);

int main(void) {

	_stog Stog;
	_stablo Stablo;
	PopResult popResult = { NULL, 0 };
	char name[VEL];
	Stog.next = NULL;
	Stablo.ime = "C:";
	Stablo.sibling = NULL;
	Stablo.child = NULL;
	int br = 0;
	bool provjera = false;
	int test = 1;
	DirectoryStatus current = { &Stablo, &Stog };  //Inicijaliziramo current na root i head stoga

	popResult = push(&Stog, &Stablo); //Dodajemo root na stog

	if (!popResult.isSuccess) return 1;

	//md-dodaj novi direktorij
	//cd dir-pomakni se na novi red
	//cd.. - vrati se red unazad
	//dir- ispis prethodnih direktorija

	while (test)
	{

		printf("\nMeni:\n1-md\n2-cd dir\n3-cd..\n4-dir\n5-izlaz\n");
		scanf(" %d", &br);


		switch (br) {
		case 1:
			printf("\nUpisite ime direktorija: ");
			scanf(" %s", name);
			provjera = MD(current.currentDirectory, name);
			if (!provjera) { 
				printf("\nGreska u unosu!"); 
				test = 0;
			}
			break;

		case 2:
			provjera = CdDir(&current);
			if (!provjera) {
				printf("\nGreska!");
				test = 0;
			}
			else printf("\nPomaknuli smo se na novi red.");
			break;

		case 3:
			provjera = Cd(&current);
			if (!provjera) {
				printf("\nGreska!");
				test=0;
			}
			else printf("\nVratili smo se red unatrag.");
			break;

		case 4:
			print(Stog.next);
			printf("%s", name); //Nakon roditeljskih direktorija ispisujemo ime zadnjega
			break;

		case 5:
			test = 0;
			break;

		default: printf("\nKrivo ste upisali!\n");
			break;
		}
	}

	getchar();
	getchar();
	return 0;
}

PopResult pop(StogPtr stack)
{
	PopResult popResult = { NULL, 0 };
	StogPtr firstEl = NULL;

	if (!stack)
	{
		popResult.data = NULL;
		popResult.isSuccess = false; // false
		return popResult;
	}

	if (!stack->next)
	{
		popResult.data = NULL;
		popResult.isSuccess = false;
		return popResult;
	}

	firstEl = stack->next;
	stack->next = firstEl->next;

	popResult.data = firstEl->el;
	popResult.isSuccess = true;
	free(firstEl);

	return popResult; // good good
}


PopResult push(StogPtr stack, StabloPtr dir) {


	PopResult popResult = { NULL, 0 };
	StogPtr firstEl = NULL;

	if (!stack)
	{
		popResult.data = NULL;
		popResult.isSuccess = false; // false
		return popResult;
	}

	firstEl = (StogPtr)malloc(sizeof(_stog));
	firstEl->next = stack->next;
	stack->next = firstEl;
	firstEl->el = dir; //postavljena adresa direktorija na stog

	popResult.data = dir;
	popResult.isSuccess = true;

	return popResult; //good
}

bool MD(StabloPtr parent, char *Ime) {

	StabloPtr sib = NULL;
	StabloPtr dir = NULL;

	if (parent == NULL)
		return false;

	dir = (StabloPtr)malloc(sizeof(_stablo));

	if (!dir->ime) return false;
	
	dir->ime = (char *)calloc((strlen(Ime) + 1), sizeof(char));

	strcpy(dir->ime, Ime);
	dir->child = NULL;
	dir->sibling = NULL;

	if (parent->child == NULL) //Ako dodajemo prvo dijete
	{
		parent->child = dir;
	}

	else {

		sib = parent->child;

		while (sib->sibling != NULL && sib->sibling->child==NULL) //Trazimo zadnjeg brata/sestru bez djece i do njega umećemo novoga (korisno ako je prethodno upotrebljen cd..))
			sib = sib->sibling; 

		dir->sibling = sib->sibling; //Novi pokazuje na sibling od prethodnika
		sib->sibling = dir;			//Prethodni pokazuje na novoga

	}


	return true;

}

bool CdDir(DirectoryStatus *current) {

	PopResult popResult = { NULL, 0 };
	StabloPtr p = current->currentDirectory->child;

	if (p == NULL) return false;


	while (p->sibling != NULL)		//Tražimo zadnjeg siblinga
		p = p->sibling;
	current->currentDirectory = p;	//Postavljamo current na zadnjeg siblinga (on postaje novi roditelj)

	popResult = push(current->parentDirectories, current->currentDirectory);	//Dodajemo zadnjeg siblinga na stog

	if (popResult.isSuccess == false) {
		return false;
	}

	return true;
}

bool Cd(DirectoryStatus* current)
{

	PopResult popResult = { NULL, 0 };
	StabloPtr newcurr = NULL;
	StogPtr stack = current->parentDirectories;	//Pokazivač na početak stoga

	popResult = pop(stack);	

	if (!popResult.isSuccess) return false;

	newcurr = stack->next->el;	//newcurr će pokazivati na direktorij čija je adresa iduća zapisana na stogu
	current->currentDirectory = newcurr;	//current smo premjestili u gornji red

	return true;
}

void print(StogPtr p)
{
	if (!p) return;

	print(p->next);
	printf("%s/", p->el->ime);

}
