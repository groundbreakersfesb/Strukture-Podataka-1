#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define VEL 15

//10. Napisati program koji iz datoteke èita postfiks izraz i zatim stvara stablo proraèuna.Iz
//gotovog stabla proraèuna upisati u datoteku infiks izraz.//

struct stablo;
struct stog;

typedef struct stablo* StabloPtr;
typedef struct stog* StogPtr;

typedef struct stablo {

	char el[VEL];
	StabloPtr L;
	StabloPtr D;
}_stablo;

typedef struct stog {

	StabloPtr el;
	StogPtr next;

}_stog;

int push(StogPtr, StabloPtr);
StabloPtr pop(StogPtr);
StabloPtr citaj(StogPtr);
void inorder(StabloPtr);

int main(void) {

	StabloPtr Root = NULL;
	_stog Head;
	Head.next = NULL;

	Root = citaj(&Head);
	if (Root == NULL)
		printf("Greska!\n");

	else {
		printf("Infix izraz:\n");
		inorder(Root);
	}

	getchar();
	getchar();
	return 0;
}

int push(StogPtr stack, StabloPtr p) {

	StogPtr q;

	if (stack == NULL) return -1;

	q = (StogPtr)malloc(sizeof(_stog));

	if (q == NULL) return -1;

	q->el = p;

	q->next = stack->next;
	stack->next = q;

	return 0;
}

StabloPtr pop(StogPtr stack) {

	StabloPtr x;
	StogPtr temp;

	if (stack == NULL) return NULL;

	if (stack->next == NULL) return NULL;

	temp = stack->next;
	stack->next = temp->next;

	x = temp->el;

	free(temp);

	return x;
}

StabloPtr citaj(StogPtr stack) {

	FILE* ulz;
	char str[VEL];
	StabloPtr x, y, z;
	int provjera = 0;


	ulz = fopen("postfix.txt", "r");

	if (ulz == NULL) return NULL;

	while (!feof(ulz)) {

		fscanf(ulz, " %s", str);

		if (str[0] >= '0' && str[0] <= '9')
		{
			x = (StabloPtr)malloc(sizeof(_stablo));
			if (!x) return NULL;

			strcpy(x->el, str);
			x->D = NULL;
			x->L = NULL;

			provjera = push(stack, x);
			if (provjera != 0) return NULL;
		}

		else if (strcmp(str, "*") == 0 || strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "/") == 0)
		{
			x = pop(stack);
			y = pop(stack);

			z = (StabloPtr)malloc(sizeof(_stablo));
			if (!z) return NULL;

			strcpy(z->el, str);
			z->L = y;
			z->D = x;
			provjera = push(stack, z);
			if (provjera != 0) return NULL;
		}
		else
			return NULL;


	}

	z = pop(stack);
	if (stack->next != NULL) return NULL;

	fclose(ulz);
	return z;
}
void inorder(StabloPtr s) {

	if (s != NULL) {
		inorder(s->L);
		printf("%s ", s->el);
		inorder(s->D);
	}
}