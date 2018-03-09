build:
	gcc -Wall -g hash.c hash_table.c operatii.c functiiLG.c functiipointer.c functiiTH.c -o hash_table
run:
	./hash_table
clean:
	rm -rf *.o
	rm -rf hash_table

