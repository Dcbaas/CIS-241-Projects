all: queue.o proj2.o stats_structs.o
	clang queue.o proj2.o stats_structs.o -o simulation -lm
queue.o: queue.c
proj2.o: proj2.c
stats_structs.o: stats_structs.c

test:
	./simulation 4
	./simulation 5
	./simulation 6
	./simulation 7

clean:
	rm -rf *o simulation
