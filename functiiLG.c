#include "lista.h"

//inserarea unei celule intr-o lista
//returneaza 1 daca s-a inserat cu succes
int InsLG(ALG aL, void* ae)
{
	//aloca noua celula
	TLG aux = NULL;
	aux = malloc(sizeof(TCelulaG));

	//verificare alocare
	if (!aux)
	{
		printf ("Eroare la alocare celula");
		return 0;
	}

	//copiaza informatia in celula
	aux->info = (Info *)ae;
	aux->urm = NULL;
	TLG p = NULL, u = NULL;

	//parcurge pentru a afla ultimul element
	for(p = *aL; p != NULL; p = p->urm)
		u = p;
	/* daca nu exista elemente in lista
	se schimba adresa listei */
	if (u == NULL)
	{
		aux->urm = *aL;
		*aL = aux;
	}
	//altfel insereaza la sfarsitul listei
	else
	{
		u->urm = aux;
		u = aux;
	}

  	return 1;
}

//elibereaza celula
void eliberareLG (TH *h, TLG elem)
{
	Info *aux = (Info *)(elem->info);
	//eliberare valoare din informatie
	aux->elibel(aux);
	//eliberare cheie din informatie
	h->elibch(aux->cheie);
	//eliberare informatie
	free(aux);
	//eliberare celula
	free(elem);
}

//citirea unei informatii materie
//returneaza un pointer de tip TMaterie
//returneaza NULL daca nu s-a alocat cu succes
TMaterie* citiremat (FILE *fin)
{
	TMaterie *p = (TMaterie *) malloc (sizeof(TMaterie));

	if (!p)
		return NULL;

	//alocare memorie nume materie
	p->materie = (char *) malloc (sizeof(char) * 50);

	if (!(p->materie))
	{
		free(p);
		return NULL;
	}
	
	//citire elemente din valoare
	fscanf(fin, "%s", p->materie);
	fscanf(fin, "%d", &p->ore_curs);
	fscanf(fin, "%d", &p->ore_lab);
	fscanf(fin, "%d", &p->credit);
	fscanf(fin, "%d", &p->teme);

	return p;
}

//citirea unei informatii student
//returneaza un pointer de tip TMaterie
//returneaza NULL daca nu s-a alocat cu succes
TStudent* citirestud (FILE *fin)
{
	TStudent *p = (TStudent *) malloc (sizeof(TStudent));
	
	if (!p)
		return NULL;

	//alocare memorie nume student
	p->nume = (char *) malloc (sizeof(char) * 50);

	if (!(p->nume))
	{
		free(p);
		return NULL;
	}
	
	//citire elemente din valoare
	fscanf(fin, "%s", p->nume);
	fscanf(fin, "%f", &p->medie);
	fscanf(fin, "%s", p->grupa);
	fscanf(fin, "%d", &p->varsta);

	return p;
}