#include "lista.h"

//distrugere tabel hash
void DistrTH(TH** ah)
{
	TLG* p, el, aux;

	//parcurgere tabel
	for (p = (*ah)->v; p < (*ah)->v + (*ah)->nr; p++)
	{
		el = *p;
		while (el != NULL)
		{
			aux = el;
			el = el->urm;
			eliberareLG(*ah, aux);
		} 			
	}

	//elibereaza vector de liste
	free((*ah)->v);
	//elibereaza tabel
	free(*ah);
	*ah = NULL;		
}

//initializare tabel hash
//returneaza tabel daca s-a initializat cu succes
//returneaza NULL in caz contrar
TH* IniTH(size_t nr, TFHash fh, TFCmp fc, TF faf, TE fel, TD dim)
{
	TH *h;
	//alocare memorie tabel
	h = (TH*) calloc(sizeof(TH),1);
	
	if (!h) 
	{	
		printf("Eroare alocare hash\n");
		return NULL;
	}

	h->nr = nr;			//numarul de liste
	h->fh = fh;			//functia hash
	h->comp = fc;		//functia de comparare
	h->afisch = faf;	//functia de afisare cheie
	h->elibch = fel;	//functia de eliberare cheie
	h->dim = dim;		//functia de aflare dimensiune cheie

	//alocare memorie vector de liste
	h->v = (TLG*) calloc(nr, sizeof(TLG));
	
	if(!h->v)
	{
		printf("Eroare alocare vector\n");
		free(h);
		return NULL;
	}

	return h;
}