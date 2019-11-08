#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct {
	char ime[20];
	char prez[20];
	int bod;
}student;

int prebroji(char *);
int unosStud(char * , int, student *);
int main()
{
	int i, br,provjera;
	student *s = NULL;
	char  imedat[30]="studenti.txt";

	br = prebroji(imedat);
	if (br == -1) {
		printf("Greska u otvaranju datoteke!");
		return -1;
	}

	s = (student *)malloc(br * sizeof(student));
	if (s == NULL)
	{
		printf("Greska u alociranju memorije!");
		return -1;
	}

	provjera = unosStud(imedat, br, s);
	if (provjera == -1) {
		printf("Greska u otvaranju datoteke!");
		return -1;
	}
	//max broj bodova je 50

	for (i = 0; i < br; i++)
		printf("\n%-15s %-15s  %2d  %2.2f%%", s[i].ime, s[i].prez, s[i].bod, (float)s[i].bod / 50 * 100);

	free(s);
	getchar();
	return 0;
}
int prebroji(char *imedat) {
	FILE *dat;
	int br = 0;
	char buffer[1024];

	dat = fopen(imedat, "r");
	if (dat == NULL)
		return -1;

	do {
		fgets(buffer, 1024, dat);
		br++;
	} while (!feof(dat));

	fclose(dat);
	return br;
}
int unosStud(char *imedat, int br, student *s) {
	FILE *dat;
	int i;

	dat = fopen(imedat, "r");
	if (dat == NULL)
		return -1;

	for (i = 0; i < br; i++) {
		fscanf(dat, "%d %s %s", &s[i].bod, s[i].ime, s[i].prez);
	}
	fclose(dat);
	return 1;
}