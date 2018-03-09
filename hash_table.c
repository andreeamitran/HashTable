#include "lista.h"

int main ()
{
	TH *hash = NULL;
	Info *el = NULL;
	int nr = 0, nrpers = 0, elim = 0;

	FILE *fout = fopen ("output.out", "wt");
	if (fout == NULL)
	{
		printf("Nu s-a putut deschide fisierul!\n");
		return 0;
	}
	
	FILE *fin = fopen ("input.in", "r");
	if (fin == NULL)
	{
		printf("Nu s-a putut deschide fisierul!\n");
		fclose(fout);
		return 0;
	}

	char string[10], tip, oper[10], blank, elem[5], cheie[50];
	int nrbuc, i, nriter, cheieint = 0;

	fscanf(fin, "%s", string);
	fscanf(fin, "%c", &blank);
	fscanf(fin, "%c", &tip);
	fscanf(fin, "%d", &nrbuc);
	fscanf(fin, "%d", &nriter);

	/* in functie de tipul de cheie, se apeleaza functia
	de initializare tabel, cu parametri specifici cheii */
	if (tip == 's')
	{
		hash = (TH *) IniTH (nrbuc, hash_f,
			compchstr, afichstr, elibcheies, dimchar);
		
		if (!hash)
		{
			fclose(fin);
			fclose(fout);
			return 0;
		}
	}
	else
	{
		hash = (TH *) IniTH (nrbuc, hash_f,
			compchval, afichval, elibcheiei, dimint);
		
		if (!hash)
		{
			fclose(fin);
			fclose(fout);
			return 0;
		}
	}

	//nriter - numarul de operatii de efectuat
	for (i = 0; i < nriter; i++)
	{
		fscanf(fin, "%s", oper);
		//daca operatia este inserare
		if (strcmp(oper, "insert") == 0)
		{
			//aloca element de tip Info
			el = (Info *) malloc (sizeof(Info));

			if (!el)
			{
				printf ("Eroare la alocare!\n");
				fclose(fin);
				fclose(fout);
				return 0;
			}

			fscanf(fin, "%c", &blank);
			if (tip == 's')
			{
				//alocare cheie string
				el->cheie = (char *) malloc (50 * sizeof(char));
				
				if (!(el->cheie))
				{
					printf("Eroare la alocare!\n");
					free(el);
					fclose(fin);
					fclose(fout);
					return 0;
				}

				fscanf(fin, "%s", ((char *)(el->cheie)));
				fscanf(fin, "%c", &blank);
			}
			else
			{
				//alocare cheie int
				el->cheie = (int *) malloc (sizeof (int));

				if (!(el->cheie))
				{
					printf("Eroare la alocare!\n");
					free(el);
					fclose(fin);
					fclose(fout);
					return 0;
				}

				fscanf(fin, "%d", ((int *)(el->cheie)));
			}		
			fscanf(fin, "%s", elem);

			//citirea elementelor din valoare in functie
			// de tipul precizat, mat sau stud
			if (strcmp (elem, "mat") == 0)
			{
				el->valoare = (TMaterie *) citiremat(fin);

				if (!(el->valoare))
				{
					printf("Eroare la alocare!\n");
					free(el->cheie);
					free(el);
					fclose(fin);
					fclose(fout);
					return 0;
				}

				el->afisel = afimat;
				el->elibel = elibmat;
				nr = InsTH(hash, el);
			}
			else
			{
				el->valoare = (TMaterie *) citirestud(fin);

				if (!(el->valoare))
				{
					printf("Eroare la alocare!\n");
					free(el->cheie);
					free(el);
					fclose(fin);
					fclose(fout);
					return 0;
				}

				el->afisel = afistudent;
				el->elibel = elibstud;
				nr = InsTH(hash, el);
			}

			//daca rezultatul inserarii este 1,
			//s-a adaugat un nou element in tabel
			if (nr == 1)
				nrpers++;		//numar elemente in tabel
			else if (nr == 0)
			{
				printf ("Eroare inserare");
				DistrTH(&hash);
				fclose(fin);
				fclose(fout);
				return 0;
			}

			//verifica load factor
			if (((float)nrpers / (float)hash->nr) >= 0.75)
			{
				hash = redim (hash, tip);
				if (!hash)
				{
					printf("Eroare la redimensionare!\n");
					DistrTH(&hash);
					fclose(fin);
					fclose(fout);
				}
			}
		}
		else if (strcmp(oper, "print") == 0)
		{
			AfiTH(hash, fout);
		}
		//daca operatia este find, cauta dupa cheie
		else if (strcmp(oper, "find") == 0)
		{
			if (tip == 's')
			{
				fscanf(fin, "%s", cheie);
				Cauta(hash, (void*)cheie, fout);
			}
			else
			{
				fscanf(fin, "%d", (int*)&cheieint);
				Cauta(hash, (void*)(&cheieint), fout);
			}
		}
		//daca operatia este delete, sterge element
		else if (strcmp(oper, "delete") == 0)
		{
			if (tip == 's')
			{
				fscanf(fin, "%s", cheie);
				elim = Stergere(&hash, (void*)cheie);
			}
			else
			{
				fscanf(fin, "%d", (int *)&cheieint);
				elim = Stergere(&hash, (void*)(&cheieint));
			}
			//decrementare numar elemente tabel
			nrpers = nrpers - elim;
		}
	}

	//eliberare memorie si inchidere fisiere
	DistrTH(&hash);
	fclose(fin);
	fclose(fout);

	return 0;
}