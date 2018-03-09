#include "lista.h"

//afisare tabel hash
void AfiTH (TH* ah, FILE *fout)
{
	TLG* p;
	TLG el = NULL;
	
	//parcurgere vector de liste
	for(p = ah->v; p < ah->v + ah->nr; p++)
	{
		fprintf(fout, "[%d] :", (int)(p - ah->v));
		if(*p)
		{
			//parcurgere lista
			el = *p;
			while (el != NULL)
			{
				Info *a = (Info *)(el->info);
				fprintf(fout, " (");
				//afisare cheie
				ah->afisch(a->cheie, fout);
				fprintf(fout, " -> ");
				//afisare valoare
				a->afisel(a->valoare, fout);
				fprintf(fout, ")");
				el = el->urm;
			}
		}
		fprintf(fout, "\n");
	}
}

//inserare in tabel
//returneaza 2 daca s-a inserat intr-o celula deja existenta
//returneaza 1 daca s-a inserat o noua celula
//returneaza 0 in caz contrar
int InsTH (TH*a, void *ae)
{
	TLG pa;
	Info *el = (Info *)(ae);
	int nr, rez;

	//bucket-ul in care se va adauga elementul
	nr = a->fh(el->cheie, a->dim(el->cheie), a->nr);

	if (nr < 0) 
		return 0;

	int ok = 0;

	//parcurgere vector de liste
    for(pa = a->v[nr]; pa != NULL; pa = pa->urm)
	{       
		//daca exista un element cu aceeasi cheie
		if (a->comp(((Info *)(pa->info))->cheie, el->cheie) == 0)
		{
			ok = 1;
			//elibereaza toata informatia
			a->elibch(((Info *)(pa->info))->cheie);
			((Info *)(pa->info))->elibel(pa->info);
			free(pa->info);
			//copiaza noua informatie
			pa->info = el;
			return 2;
		}
	}
	if (ok != 1)
	{
		rez = InsLG(a->v+nr, ae);
		if (rez != 1)
		{
			printf ("Eroare inserare celula\n");
			return 0;
		}
	}

	return 1;	
}
//cautare dupa cheie
void Cauta (TH* hash, void *a, FILE* f)
{
	int nr = 0, ok = 0;
	
	//numarul bucket-ului in care se afla
	nr = hash->fh(a, hash->dim(a), hash->nr);

	//daca numarul nu corespunde niciunui bucket
	if (nr < 0 || nr > hash->nr)
	{
		fprintf(f, "Nu exista\n");
		return;
	}

	TLG p = hash->v[nr];

	//daca bucket-ul e gol
	if (p == NULL)
	{
		fprintf(f, "Nu exista\n");
		return;
	}

	while (p != NULL)
	{
		//compara chei
		if (hash->comp(((Info *)(p->info))->cheie, a) == 0)
		{
			ok = 1;
			Info *a = (Info *)(p->info);
			//afiseaza valoarea de la cheia gasita
			(a)->afisel(a->valoare, f);
			fprintf(f, "\n");
			break;
		}
		p = p->urm;
	}

	//daca nu s-a gasit in bucket
	if (ok == 0)
	{
		fprintf(f, "Nu exista\n");
	}
}

//redimensionare tabel
//returneaza NULL daca nu s-a putut redimensiona
//returneaza noul tabel daca redimensioneaza cu succes
TH* redim (TH* a, char tip)
{
	TH *hashnou = NULL;
	TLG p = NULL;
	int rez = 0;

	//initializare tabel nou
	if (tip == 's')
		hashnou = IniTH ((a->nr) * 2, hash_f, 
			compchstr, afichstr, elibcheies, dimchar);
	else
		hashnou = IniTH ((a->nr) * 2, hash_f, 
			compchval, afichval, elibcheiei, dimint);

	if (!hashnou)
		return NULL;

	int i = 0;
	//parcurgere tabel vechi
	for (; i < a->nr; i++)
	{
		p = a->v[i];

		while (p != NULL)
		{   
			//inserarea informatiei in noul tabel
			rez = InsTH(hashnou, p->info);
			
			if (rez == 0)
			{
				DistrTH(&hashnou);
				return NULL;
			}

			p = p->urm;
		}
	}

	//eliberare informatii din tabel vechi
	TLG aux, *parc, el;
	for (parc = a->v; parc < a->v + a->nr; parc++)
	{
		el = *parc;
		while (el != NULL)
		{
			aux = el;
			el = el->urm;
			free(aux);
		} 			
	}

	free(a->v);
	free(a);

	return hashnou;
}

//stergere din tabel
int Stergere (TH **ah, void *cheie)
{
	TH *p;
	p = *ah;
	int nr = 0;
	
	//numarul bucket-ului
	nr = p->fh(cheie, p->dim(cheie), p->nr);
	TLG q = p->v[nr], ant = NULL, aux = NULL;

	//verificare daca bucket-ul este gol
	if (q == NULL)
		return 0;

	for (; q != NULL; q = q->urm)
	{
		//daca a gasit cheia
		if (p->comp(((Info *)(q->info))->cheie, cheie) == 0)
		{
			aux = q;
			
			//daca este primul element din lista
			if (ant == NULL && q->urm != NULL)
			{
				aux = p->v[nr];
				p->v[nr] = p->v[nr]->urm;
				eliberareLG(*ah, aux);
			}
			//daca este ultimul element din lista
			else if (ant != NULL && q->urm == NULL)
			{
				aux = q;
				eliberareLG(*ah, aux);
				q = ant;
				ant->urm = NULL;
			}
			//daca este singurul element din lista
			else if (ant == NULL && q->urm == NULL)
			{
				aux = p->v[nr];
				eliberareLG(*ah, aux);
				p->v[nr] = NULL;
			}
			else
			{
				aux = q;
				eliberareLG(*ah, aux);
				ant->urm = q->urm;
				q = ant->urm;
			}

			return 1;
		}
		//actualizeaza anteriorul
		ant = q;
	}

	return 0;
}