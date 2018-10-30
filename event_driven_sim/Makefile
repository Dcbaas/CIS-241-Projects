all: queue.o proj2.o
	clang queue.o proj2.o -o simulation -lm
queue.o: queue.c
main.o: proj2.c

clean:
	rm -rf *o simulation
