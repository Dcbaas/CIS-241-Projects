cipher: cipher.o
	gcc cipher.o -o cipher
cipher.o: cipher.c

decipher:
	clang decipher.c main.c -o decipher

test: test1 test2 
test1: 
	./cipher 1 5 data.txt data.out
test2:
	./cipher 2 5 data.out data.bak

mytest: tooshort short obscure long
tooshort:
	./cipher 1 13 tooshort.txt tooshort.out
	./decipher tooshort.out tooshort.bak
	diff tooshort.txt tooshort.bak
short:
	./cipher 1 4 short.txt short.out
	./decipher short.out short.bak
	diff short.txt short.bak
obscure:
	./cipher 1 19 obscure.txt obscure.out
	./decipher obscure.out obscure.bak
	diff obscure.txt obscure.bak
long:
	./cipher 1 22 long.txt long.out
	./decipher long.out long.bak
	diff long.txt long.bak
