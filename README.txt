----- Fisier: functiipointer.c -----

	In acest fisier sunt implementate functiile la care se trimit pointeri.

	Functia elibcheies realizeaza eliberarea de memorie pentru o cheie de tip string.
	
	Functia elibcheiei realizeaza eliberarea de memorie pentru o cheie de tip int.
	
	Functia afischstr realizeaza afisarea unei chei de tip char.
	
	Functia afichval realizeaza afisarea unei chei de tip int.
	
	Functia elibmat realizeaza eliberarea de memorie pentru o valoare de tip materie. In primul rand se elibereaza memoria pentru numele materiei, iar apoi se elibereaza memoria pentru campul valoare din structura Info.

	Functia elibstud realizeaza eliberarea de memorie pentru o valoare de tip student. In primul rand se elibereaza memoria pentru numele studentului, iar apoi se elibereaza memoria pentru campul valoare din structura Info.

	Functia afimat realizeaza afisarea unui element de tip materie, camp cu camp.

	Functia afistud realizeaza afisarea unui element de tip student, camp cu camp.

	Functia compchstr realizeaza compararea a doua chei de tip string, utilizand functia strcmp, ce returneaza 0 daca cele doua siruri de caractere sunt identice.

	Functia compchval realizeaza compararea a doua chei de tip int, realizand diferenta celor doua valori, ce va fi 0 daca valorile sunt egale.

	Functia dimchar calculeaza dimensiunea unei chei de tip string, cu ajutorul functiei strlen, ce returneaza lungimea sirului de caractere.

	Functia dimint calculeaza dimensiunea unei chei de tip int, prin returnarea de sizeof(int).

----- Fisier: functiiLG.c -----

	In acest fisier sunt implementate functiile de inserare/eliberare celula si functiile de citire a unei valori de tip student sau de tip materie.

	Functia InsLG realizeaza alocarea de memorie pentru o celula, iar apoi in campul info este copiata informatia primita prin parametrul ae. Se parcurge lista pentru a retine care este ultima celula, in cazul in care exista una. Daca nu exista, atunci celula de inserat va fi prima si astfel se schimba adresa listei. In cazul in care mai exista elemente, se realizeaza inserarea la sfarsitul listei, ultima celula devine noua celula si se fac legaturile.

	Functia eliberareLG realizeaza eliberarea de memorie pentru un element de tip TLG, adica pentru o celula. Se elibereaza valoarea din informatie, cheia, apoi informatia. In final se elibereaza memoria pentru celula.

	Functia citiremat realizeaza citirea unui element de tip materie. Se aloca memorie un element de acest tip si pentru un sir de caractere in care se retine numele materiei, apoi sunt citite valorile din fiecare camp al elementului de tip materie.

	Functia citiremat realizeaza citirea unui element de tip student. Se aloca memorie un element de acest tip si pentru un sir de caractere in care se retine numele studentului, apoi sunt citite valorile din fiecare camp al elementului de tip materie.

----- Fisier: functiiTH.c -----

	In acest fisier sunt implementate functiile de distrugere si de initializare a unui tabel Hash.

	Functia DistrTH realizeaza distrugerea unui tabel Hash. Se parcurge vectorul de liste si apoi elementele din fiecare lista. Elementul este copiat intr-o variabila auxiliara, variabila de parcurs trece la urmatorul element si se apeleaza functia eliberareLG, pentru a elibera memoria unei celule. Se elibereaza memoria pentru vectorul de liste si apoi pentru tabelul Hash.

	Functia IniTH realizeaza initializarea unui tabel Hash. Se aloca memorie pentru tabel, iar apoi se atribuie fiecarui camp valorile primite ca parametru pentru numarul de liste, functia hash, functia de comparare, functia de afisare cheie, functia de eliberare cheie si pentru functia de aflare a dimensiunii unei chei. Se aloca memorie pentru vectorul de liste, in functie de numarul de liste primit ca parametru.

----- Fisier: operatii.c -----

	In acest fisier sunt implementate functiile ce realizeaza operatiile din cerinte: Afisare tabel Hash, Inserare in tabel Hash, Cautare dupa cheie, Redimensionare tabel Hash, Stergere.

	Functia AfiTH realizeaza afisarea tabelului Hash. Se parcurge vectorul de liste, iar apoi pentru fiecare lista, se parcurg elementele corespunzatoare. Se afiseaza cheia si valoarea din campul info al unei celule.
 
	Functia InsTH realizeaza inserarea unui element intr-un tabel Hash. Se calculeaza cu ajutorul functiei Hash numarul bucket-ului in care trebuie inserata celula. Dupa aflarea lui, se parcurge lista in care elementul se poate gasi. Daca exista o celula ce are aceeasi valoare a cheii cu a elementului de inserat, se elibereaza informatia pentru campul info din celula si i se atribuie informatia noii celule, care este trimisa ca si parametru. Daca nu exista un element cu o astfel de cheie, se realizeaza inserarea unei celule in lista, utilizand functia InsLG. Daca s-a realizat inserarea unei noi celule, codul de return este 1, iar daca s-a realizat doar inlocuirea unei informatii, codul de return este 2, ceea ce ajuta mai apoi la calcularea numarului de elemente introduse in tabel.

	Functia Cauta realizeaza cautarea unui element dupa cheie in tabel. Se calculeaza cu ajutorul funtiei Hash numarul bucket-ului in care se poate afla celula. Daca bucket-ul este gol, sau in urma parcurgerii listei nu este gasita valoarea cheii, se afiseaza in fisier mesajul "Nu exista". In caz contrar, se afiseaza valoarea din campul info al acelei celule.

	Functia redim realizeaza redimensionarea tabelului Hash. Se initializeaza un nou tabel Hash prin apelarea functiei IniTH, cu parametri corespunzatori tipului de cheie si prin dublarea numarului de elemente posibile. Se parcurge tabelul vechi si apoi fiecare element din fiecare lista a sa. Se insereaza cu ajutorul functiei InsTH inserarea unei noi celule in noul tabel. (Acolo se recalculeaza numarul bucket-ului in care se adauga celula). Se elibereaza la final memoria pentru celulele din vechiul tabel, apoi pentru vectorul de liste si tabel.

	Functia Stergere realizeaza stergerea unei celule dintr-un tabel Hash. Se parcurge tabelul, apoi fiecare lista. Daca valoarea cheii unui element corespunde cu valoarea cheii date ca si parametru, se refac legaturile si se elibereaza memoria pentru celula respectiva, utilizand functia eliberareLG. Exista patru cazuri:
	-> daca celula este prima, dar nu si ultima din lista, se modifica adresa listei, ce va deveni adresa urmatorului element din lista
	-> daca celula este ultima, atunci legatura elementului anterior va fi NULL
	-> daca celula este atat prima cat si ultima in lista, se modifica adresa in vectorul de liste, ce va lua valoarea NULL
	-> daca celula are atat o celula anterioara, cat si una urmatoare, se va face legatura intre cele doua
	De fiecare data, se actualizeaza anteriorul prin variabila ant.

----- Fisier: hash_table.c -----

	In acest fisier este functia main, in care sunt apelate functiile din celelalte fisiere pentru realizarea operatiilor din cerinte.

	Se citeste cuvantul "inithash", apoi tipul cheii, numarul de liste si numarul de operatii de efectuat.
	Daca tipul cheii este string, atunci se initializeaza tabelul, apeland functia IniTH si avand ca parametri numarul maxim de buckets, functia hash, functia de comparare chei de tip string, functia de afisare chei de tip string, functia de eliberare chei de tip string si functia de calculare a dimensiunii unei elemente de tip string. In cazul in care tipul cheii este int, la apelul IniTH, parametri vor fi la fel pentru numarul de buckets si pentru functia hash, urmand ca functiile de comparare, afisare, eliberare si dimensiune sa fie specifice tipului int.
	Se realizeaza citirea de noi operatii de numarul de operatii de efectuat ori.
	Daca operatia este inserare, se aloca un element de tipul Info si apoi in functie de tipul de cheie, se aloca memorie si se citeste valoarea cheii. Daca elementul este de tip materie, se apeleaza functia citiremat, in caz contrar, se apeleaza functia citirestud. Dupa citirea valorii si a cheii din info, se apeleaza functia InsTH, caruia i se trimit ca parametri tabelul hash si elementul de tip Info. Daca s-a adaugat un nou element in tabel, se incrementeaza numarul de elemente din tabel. Se verifica in urma inserarii load factor-ul, iar in cazul in care acesta depaseste threshold-ul de 0.75, se redimensioneaza tabelul, utilizand functia redim.
	Daca operatia este print, atunci se afiseaza tabelul Hash, utilizand functia AfiTH.
	Daca operatia este find, atunci se citeste cheia dupa care se va cauta in tabel si se realizeaza operatia de cautare prin apelarea functiei Cauta.
	Daca operatia este delete, atunci se citeste cheie dupa care se va cauta elementul de eliminat si se apeleaza functia Stergere. Daca elementul a fost gasit si sters, se decrementeaza numarul de elemente din tabel.
	La final, se distruge tabelul utilizand functia DistrTH si se inchid fisierele.
