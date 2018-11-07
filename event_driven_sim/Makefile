all: queue.o proj2.o stats_structs.o
	clang queue.o proj2.o stats_structs.o -o simulation -lm
queue.o: queue.c
proj2.o: proj2.c
stats_structs.o: stats_structs.c

clean:
	rm -rf *o simulation
