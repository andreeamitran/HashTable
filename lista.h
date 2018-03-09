#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "materie.h"
#include "student.h"

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef int (*TFCmp)(void*, void*);		//functie comparare
typedef void (*TF)(void*, FILE*);		//functie afisare
typedef void (*TE)(void*); 				//functie eliberare
typedef unsigned int (*TFHash)(const void*, size_t, size_t);	//functie hash
typedef size_t (*TD)(void*);			//functie dimensiune

//structura Lista
typedef struct celulag
{
  void *info;
  struct celulag *urm;
} TCelulaG, *TLG, **ALG;

//structura Tabel Hash
typedef struct
{
	size_t nr;
	TFHash fh;
	TLG *v;
	TFCmp comp;
	TF afisch;
	TE elibch;
	TD dim;
} TH;

//structura Info 
typedef struct
{
	void* valoare;
	void* cheie;
	TF afisel;
	TE elibel;
} Info;

//declarare functii
void elibcheies (void *a);
void elibcheiei (void *a);
void afichstr (void *a, FILE *fp);
void afichval (void *a, FILE *fp);
void elibmat (void *a);
void elibstud (void *a);
void afimat (void *a, FILE *fp);
void afistudent (void *a, FILE *fp);
int compchstr (void *a1, void *a2);
int compchval (void *a1, void *a2);
size_t dimchar (void *a);
size_t dimint (void *a);
unsigned int hash_f(const void *data, size_t len, size_t range);
int InsLG(ALG aL, void* ae);
void eliberareLG (TH *h, TLG elem);
void DistrTH(TH** ah);
TH* IniTH(size_t nr, TFHash fh, TFCmp fc, TF faf, TE fel, TD dim);
void AfiTH (TH* ah, FILE *fout);
int InsTH (TH*a, void *ae);
TMaterie* citiremat (FILE *fin);
TStudent* citirestud (FILE *fin);
void Cauta (TH* hash, void *a, FILE* f);
TH* redim (TH* a, char tip);
int Stergere (TH **ah, void *cheie);


#endif
