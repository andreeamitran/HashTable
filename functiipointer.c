#include "lista.h"

//eliberare cheie string
void elibcheies (void *a)
{
	char *p = (char *)a;
	free(p);
	p = NULL;
}

//eliberare cheie int
void elibcheiei (void *a)
{
	int *p = (int *)a;
	free(p);
	p = NULL;
}

//afisare cheie string
void afichstr (void *a, FILE *fp)
{
	char *p = (char *)a;
	fprintf (fp, "%s", p);
}

//afisare cheie int
void afichval (void *a, FILE *fp)
{
	int *p = (int *)a;
	fprintf (fp, "%d", *p);
}

//elibeare element de tip materie
void elibmat (void *a)
{
	Info *p = (Info *)a;
	free((char*)((TMaterie *)(p->valoare))->materie);
	free((TMaterie *)(p->valoare));
}

//eliberare element de tip student
void elibstud (void *a)
{
	Info *p = (Info *)a;
	free((char *)((TStudent *)(p->valoare))->nume);
	free((TStudent *)(p->valoare));
}

//afisar element de tip materie
void afimat (void *a, FILE *fp)
{
	TMaterie *mat = (TMaterie*) a;
	fprintf (fp, "[Materie: %s, ", mat->materie);
	fprintf (fp, "Ore_curs: %d, ", mat->ore_curs);
	fprintf (fp, "Ore_lab: %d, ", mat->ore_lab);
	fprintf (fp, "Credit: %d, ", mat->credit);
	fprintf (fp, "Teme: %d]", mat->teme);
}

//afisare element de tip student
void afistudent (void *a, FILE *fp)
{
	TStudent *stud = (TStudent*) a;
	fprintf (fp, "[Nume: %s, ", stud->nume);
	fprintf (fp, "Grupa: %s, ", stud->grupa);
	fprintf (fp, "Medie: %.2f, ", stud->medie);
	fprintf (fp, "Varsta: %d]", stud->varsta);
}

//compara chei string
int compchstr (void *a1, void *a2)
{
	return strcmp((char *)a1, (char *)a2);
}

//compara chei int
int compchval (void *a1, void *a2)
{
	return *(int *)a1 - *(int *)a2;
}

//dimensiune cheie string
size_t dimchar (void *a)
{
	return strlen((char *)a);
}

//dimensiune cheie int
size_t dimint (void *a)
{
	return sizeof(int);
}

