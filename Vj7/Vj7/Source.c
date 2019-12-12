#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//7. Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
//rezultat.Stog je potrebno realizirati preko vezane liste.

//5 2 * 6 + 4 2 * +
struct broj;
typedef struct broj *Stog;

typedef struct broj {

	int el;
	Stog next;

}_broj;

int push(const Stog, int);
int pop(const Stog);
int citaj(const Stog, const char *);

int main(void) {

	_broj Head;
	Head.next == NULL;
	char ime[30] = "postfix.txt";
	int x = 0;

	x = citaj(&Head, ime);
	if (x != -1)
		printf("Rezultat je %d\n", x);
	else
		printf("Greska");

	getchar();
	return 0;
}

int push(const Stog s, int x)
{
	Stog q, p;
	p = s;

	q = (Stog)malloc(sizeof(_broj));

	if (q == NULL) return -1;

	q->el = x;

	q->next = p->next;
	p->next = q;

	return 0;
}

int pop(const Stog s)
{
	Stog p=NULL, temp=NULL;
	int x;

	p = s;
	temp = p->next;

	if (temp == NULL) return -1;

	x = temp->el;

	p->next = temp->next;

	free(temp);

	return x;
}

int citaj(const Stog s, const char * ime) {

	FILE *ulz;
	int x = 0, y = 0, rezultat = 0;
	char str[30];

	ulz = fopen(ime, "r");
	if (ulz == NULL) return -1;

	while (!feof(ulz)) {

		fscanf(ulz, " %s", str);

		if (str[0] >= '0' && str[0] <= '9') {
			sscanf(str, "%d", &x);
			rezultat = push(s, x);

			if (rezultat == -1)
				return -1;
		}

		else if (strcmp(str, "+") == 0) {
			x = pop(s);
			y = pop(s);

			push(s, y + x);
		}

		else if (strcmp(str, "-") == 0) {
			x = pop(s);
			y = pop(s);

			push(s, y - x);
		}
		else if (strcmp(str, "*") == 0) {
			x = pop(s);
			y = pop(s);

			push(s, y * x);
		}
		else if (strcmp(str, "/") == 0) {
			x = pop(s);
			y = pop(s);

			push(s, y / x);
		}
		else {
			return -1;
		}
	}

	x = pop(s);

	/*if (s->next != NULL)
		return -1;*/

	fclose(ulz);
	return x;
}