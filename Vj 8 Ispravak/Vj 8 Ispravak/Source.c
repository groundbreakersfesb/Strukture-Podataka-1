#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
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
}Stablo;

typedef struct stog {
	StabloPtr el;
	StogPtr next;
}Stog;

typedef struct directoryStatus {
	StabloPtr currentDirectory; // ante 
	StogPtr parentDirectories; // [ "Student", "Users", "C:" ] 
} DirectoryStatus;

typedef struct popResult {
	StabloPtr data;
	bool isSuccess;
} PopResult;

PopResult pop(StogPtr);
PopResult push(StogPtr, StabloPtr);
bool MD(const StabloPtr, char *);
bool CdBack(DirectoryStatus *);
void print(StogPtr);
StabloPtr CdDir(StogPtr, StabloPtr, StabloPtr, char *);
bool EmptyStog(const StogPtr);

int main() {

	Stog Head;
	Stablo Root;
	Head.next = NULL;
	Root.sibling = NULL;
	Root.child = NULL;
	Root.ime = "C:";
	char zn = ' ';
	char name[VEL];
	bool provjera = false;
	DirectoryStatus current = { &Root, &Head }; //current postavljamo na root stabla i head stoga
	push(&Head, &Root);   //Dodajemo root na stog (korisno ako ispisujemo prije pozivanja CdDir)

	while (zn != '5') {

		printf("Meni:\n1 - md\n2 - cd dir\n3 - cd..\n4 - dir\n5 -izlaz\n");
		scanf(" %c", &zn);
		switch (zn) {
		case '1':
			printf("Unesite ime novog direktorija: ");
			scanf(" %s", name);
			provjera = MD(current.currentDirectory, name);
			if (!provjera) {
				zn = '5';
				printf("Greska u unosu!\n");
			}
			break;

		case '2':
			printf("Unesite ime direktorija na koji se zelite prebaciti: ");
			scanf(" %s", name);
			provjera = EmptyStog(&Head);					//Prije prebacivanja praznimo stog
			if(provjera)									//Ako je uspjesno ispraznjen, pozivamo funkciju CdDir
				current.currentDirectory = CdDir(&Head, &Root, NULL, name);

			if (!provjera || !current.currentDirectory ) {
				zn = '5';
				printf("Greska!\n");
			}
			else printf("Prebacili smo se na zeljeni direktorij.\n");
			break;
			

		case '3':
			provjera = CdBack(&current);
			if (!provjera) {
				printf("Greska!\n");
				zn = '5';
			}
			else printf("Prebacili smo se na prethodni direktorij.\n");
			break;

		case '4':
			print(Head.next);
			printf("\n");
			break;

		case '5':
			break;

		default:
			printf("Pogresan unos!\n");
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

	return popResult; // good
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

	firstEl = (StogPtr)malloc(sizeof(Stog));
	firstEl->next = stack->next;
	stack->next = firstEl;
	firstEl->el = dir; //postavljena adresa direktorija na stog

	popResult.data = dir;
	popResult.isSuccess = true;

	return popResult; //good
}

bool MD( const StabloPtr Root, char* name) {
	StabloPtr directory = NULL;
	StabloPtr sib = NULL;
	StabloPtr parent = Root;

	directory = (StabloPtr)malloc(sizeof(Stablo));
	if (!directory) return false;

	directory->ime = (char *)calloc((strlen(name) + 1) ,sizeof(char));
	strcpy(directory->ime, name);
	directory->child = NULL;

	if (parent->child == NULL)		//Ako dodajemo prvo dijete
	{
		parent->child = directory;
		directory->sibling = NULL;
	}

	else {
		sib = parent->child;

		if (strcmp(sib->ime, name) > 0) {		//Ako je novi direktorij abecedno ispred prvoga
			parent->child = directory;
			directory->sibling = sib;
			return true;
		}
		
		while (sib->sibling!=NULL && strcmp(sib->sibling->ime, name) < 0)		//Djecu abecedno poredamo
			sib = sib->sibling;

		if (sib->sibling!=NULL && strcmp(sib->sibling->ime, name) == 0)		//Provjera ima li istih
			printf("Direktorij tog imena vec postoji!\n");
	
		else {
			directory->sibling = sib->sibling;//Novi pokazuje na sibling od prethodnika	
			sib->sibling = directory;	//Prethodni pokazuje na novoga
		}
	}

	return true;
}

void print(StogPtr p)
{
	if (!p) return;

	print(p->next);
	printf("%s/", p->el->ime);

}

StabloPtr CdDir(StogPtr stack, StabloPtr p, StabloPtr q, char * name) {		

	bool imaDijete = false;

	if (q==NULL && p->child != NULL)						//Provjera za djecu
	{
	    imaDijete = true;
		push(stack, p);
		q = CdDir(stack, p->child, q, name);
	}

	if (q==NULL && imaDijete)	//Ako ima dijete, postavljen je na stog, ako provjerava ovaj uvjet u njemu nije trazeni direktorij pa ga skidamo sa stoga
		pop(stack);

	if (q==NULL && p->sibling != NULL)						//Provjera za siblinge
	{
		q = CdDir(stack, p->sibling, q, name);
	}

	if (q == NULL && strcmp(p->ime, name) == 0)	//Ako q nije NULL, tj ako jos nismo nasli taj direktorij
	{
		q = p;
		push(stack, p);
	}

	return q;
}

bool EmptyStog(const StogPtr stack) {
	PopResult popResult = { NULL, 0 };

	while (stack->next != NULL)
	{
		popResult = pop(stack);
		if (popResult.isSuccess == false)
			return false;
	}

	return true;
}

bool CdBack(DirectoryStatus* current)
{

	PopResult popResult = { NULL, 0 };
	StabloPtr newcurr = NULL;
	StogPtr stack = current->parentDirectories;	//Pokazivač na početak stoga

	popResult = pop(stack);

	if (!popResult.isSuccess) return false;

	if (stack->next != NULL)
	{
		newcurr = stack->next->el;	//newcurr će pokazivati na direktorij čija je adresa iduća zapisana na stogu
		current->currentDirectory = newcurr;	//current smo premjestili u gornji red
		return true;
	}
	else return false;
}
