all: cipher decipher
	
cipher: cipher.o
	gcc cipher.o -o cipher
cipher.o: cipher.c

decipher: decipher.o main.o
	clang decipher.o main.o -o decipher -lm
decipher.o: decipher.c
main.o: main.c

test: test1 test2 
test1: 
	./cipher 1 20 single_paragraph.txt single_paragraph.out 
	./decipher single_paragraph.out single_paragraph.bak
	diff -s single_paragraph.txt single_paragraph.bak
test2:
	./cipher 1 13 multi_page.txt multi_page.out
	./decipher multi_page.out multi_page.bak
	diff -s multi_page.txt multi_page.bak
clean:
	rm -rf *.o decipher cipher *.out *.bak

