all: queue.o main.o
	clang queue.o main.o -o simulation
queue.o: queue.c
main.o: main.c

clean:
	rm -rf *o simulation
